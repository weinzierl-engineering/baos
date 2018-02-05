//
// Copyright (c) 2002-2018 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#include "pch/kdrive_pch.h"
#include "kdrive/ft12/FT12.h"
#include "kdrive/knx/defines/FT12Constants.h"
#include "kdrive/knx/telegrams/ft12/FT12.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <Poco/Logger.h>
#include <Poco/Thread.h>
#include <boost/assert.hpp>

using namespace kdrive::ft12;
using namespace kdrive::knx;
using namespace kdrive::knx::ft12;
using Poco::Exception;
using Poco::Thread;

/**************************************
** Init Logger
***************************************/

CLASS_LOGGER("kdrive.ft12.FT12")

/**************************************
** FT12
***************************************/

const long FT12::exchangeTimeoutBps_ = 510 * 1000;
const int FT12::repeatLimit_ = 3;

FT12::FT12()

	: exchangeTimeout_(300),
	  fcbRx_(0),
	  fcbTx_(0)
{
}

FT12::~FT12()
{
}

void FT12::init()
{
	resetFCBs();
	sendFixedLengthFrame(FT12Constants::SendReset);
}

void FT12::setSender(Sender sender)
{
	sender_ = sender;
}

void FT12::setUserDataCallback(UserDataCallback userDataCallback)
{
	userDataCallback_ = userDataCallback;
}

void FT12::onReceive(const unsigned char* buffer, std::size_t bufferSize)
{
	BOOST_ASSERT(buffer && "Invalid buffer");
	BOOST_ASSERT(bufferSize && "Invalid buffer size");

	try
	{
		if (isAck(buffer, bufferSize))
		{
			onAckRx();
		}
		else if (isFixedFrame(buffer, bufferSize))
		{
			onFixedFrameRx(buffer, bufferSize);
		}
		else if (isVariableFrame(buffer, bufferSize))
		{
			onVariableFrameRx(buffer, bufferSize);
		}
	}
	catch (Exception& e)
	{
		poco_debug_f1(LOGGER(), "Ingnore error in Rx FT1.2 frame, %s", e.displayText());
	}
}

bool FT12::sendFixedLengthFrame(unsigned char functionCode)
{
	ControlField controlField;
	controlField.setDirection(FT12Constants::ExternalToBauDirection);
	controlField.setPrimaryMessage(FT12Constants::PrimaryMessage);
	controlField.setFrameCountBit(0x00);
	controlField.setFrameCountBitValid(FT12Constants::InvalidFCB);
	controlField.setFunctionCode(functionCode);

	FixedLengthFrame fixedLengthFrame;
	fixedLengthFrame.setDefaults();
	fixedLengthFrame.setControlField(controlField.get());
	std::vector<unsigned char> frame(FixedLengthFrame::Length, 0x00);
	BufferDecorator<Buffer> buffer(frame);
	fixedLengthFrame.write(buffer);

	return send(&frame.at(0), frame.size());
}

bool FT12::sendVariableLengthFrame(const unsigned char* buffer, std::size_t bufferLength)
{
	toggleTxFCB();

	ControlField controlField;
	controlField.setDirection(FT12Constants::ExternalToBauDirection);
	controlField.setPrimaryMessage(FT12Constants::PrimaryMessage);
	controlField.setFrameCountBit(fcbTx_);
	controlField.setFrameCountBitValid(FT12Constants::ValidFCB);
	controlField.setFunctionCode(FT12Constants::SendUdat);

	VariableLengthFrame variableLengthFrame;
	variableLengthFrame.setDefaults();
	variableLengthFrame.setUserData(buffer, bufferLength);
	variableLengthFrame.setControlField(controlField.get());
	variableLengthFrame.setVariableAttributes();
	std::vector<unsigned char> frame(VariableLengthFrame::HeaderLength + bufferLength + 1, 0x00);
	BufferDecorator<Buffer> b(frame);
	variableLengthFrame.write(b);

	return send(&frame.at(0), frame.size());
}

void FT12::setBitsPerSecond(long bitsPerSecond)
{
	BOOST_ASSERT(bitsPerSecond > 0 && "Invalid Bit Rate");
	exchangeTimeout_ = exchangeTimeoutBps_ / bitsPerSecond;
	if (exchangeTimeout_ < 10)
	{
		exchangeTimeout_ = 10;
	}
}

bool FT12::isAck(const unsigned char* buffer, std::size_t bufferLength) const
{
	return *buffer == FT12Constants::AckFrame;
}

bool FT12::isFixedFrame(const unsigned char* buffer, std::size_t bufferLength) const
{
	return *buffer == FT12Constants::StartFixedLengthFrame;
}

bool FT12::isVariableFrame(const unsigned char* buffer, std::size_t bufferLength) const
{
	return *buffer == FT12Constants::StartVarLengthFrame;
}

void FT12::onAckRx()
{
	ackEvent_.set();
}

void FT12::onFixedFrameRx(const unsigned char* buffer, std::size_t bufferLength)
{
	const FormatterReader<FixedLengthFrame> fixedLengthFrame(buffer, bufferLength);
	const ControlField controlField(fixedLengthFrame.getControlField());

	if (controlField.getFunctionCode() == FT12Constants::SendReset)
	{
		resetFCBs();
	}
}

/*
	If this is a valid variable length frame
	we get the control field and check the fcb valid and fcb.
	Note, we have to toggle the fcb, but we don't do this till we are
	sure the fcb is correct, which is why we check for the opposite of fcb
	i.e. we toggle the valud in the compare with controlField.getFrameCountBit()
	and if this matches we toggle the actual value
	If the user callback function is set, we call it with the data buffer
*/
void FT12::onVariableFrameRx(const unsigned char* buffer, std::size_t bufferLength)
{
	const FormatterReader<VariableLengthFrame> variableLengthFrame(buffer, bufferLength);
	const ControlField controlField(variableLengthFrame.getControlField());

	if (controlField.getFrameCountBitValid() &&
	    (controlField.getFrameCountBit() ? FT12Constants::FCB_SET : 0x00) ==
	    (fcbRx_ ? 0x00 : FT12Constants::FCB_SET))
	{
		toggleRxFCB();

		if (userDataCallback_)
		{
			userDataCallback_(variableLengthFrame.getUserData());
		}
	}
	else
	{
		poco_debug(LOGGER(), "Rx invalid FT1.2 variable frame");
	}
}

bool FT12::waitAck()
{
	return ackEvent_.tryWait(exchangeTimeout_);
}

void FT12::resetFCBs()
{
	fcbRx_ = 0;
	fcbTx_ = 0;
}

void FT12::toggleRxFCB()
{
	fcbRx_ = fcbRx_ ? 0x00 : FT12Constants::FCB_SET;
}

void FT12::toggleTxFCB()
{
	fcbTx_ = fcbTx_ ? 0x00 : FT12Constants::FCB_SET;
}

bool FT12::send(const unsigned char* buffer, std::size_t bufferLength)
{
	BOOST_ASSERT(repeatLimit_ > 0 && "Repeat Limit must be greater than 0");
	BOOST_ASSERT(sender_ && "Sender not set");

	int repeatLimit = repeatLimit_;
	ackEvent_.reset();

	do
	{
		sender_(buffer, bufferLength);

	}
	while (!waitAck() && repeatLimit--);

	return repeatLimit < 0 ? false : true;
}
