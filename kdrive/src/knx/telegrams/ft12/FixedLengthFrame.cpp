//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/knx/telegrams/ft12/FixedLengthFrame.h"
#include "kdrive/knx/defines/FT12Constants.h"

using namespace kdrive::knx::ft12;

FixedLengthFrame::FixedLengthFrame(bool autoSetChecksum)

	: autoSetChecksum_(autoSetChecksum)
{
	addFormatter(&startByte_);
	addFormatter(&controlField_);
	addFormatter(&checksum_);
	addFormatter(&endByte_);
}

FixedLengthFrame::~FixedLengthFrame()
{
}

bool FixedLengthFrame::isValid() const
{
	return ((getStartByte() == FT12Constants::StartFixedLengthFrame) &&
	        isValidChecksum() && (getEndByte() == FT12Constants::EndFrame));
}

void FixedLengthFrame::setDefaults()
{
	startByte_.set(FT12Constants::StartFixedLengthFrame);
	controlField_.set(0x00);
	checksum_.set(0x00);
	endByte_.set(FT12Constants::EndFrame);
}

unsigned char FixedLengthFrame::getStartByte() const
{
	return startByte_.get();
}

void FixedLengthFrame::setControlField(unsigned char controlField)
{
	controlField_.set(controlField);

	if (autoSetChecksum_)
	{
		setChecksum(controlField);
	}
}

unsigned char FixedLengthFrame::getControlField() const
{
	return controlField_.get();
}

void FixedLengthFrame::setChecksum(unsigned char checksum)
{
	checksum_.set(checksum);
}

unsigned char FixedLengthFrame::getChecksum() const
{
	return checksum_.get();
}

bool FixedLengthFrame::isValidChecksum() const
{
	return (getControlField() == getChecksum());
}

unsigned char FixedLengthFrame::getEndByte() const
{
	return endByte_.get();
}
