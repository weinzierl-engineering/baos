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
#include "kdrive/knx/telegrams/ft12/ControlField.h"
#include "kdrive/knx/defines/FT12Constants.h"
#include <boost/assert.hpp>

using namespace kdrive::knx::ft12;

ControlField::ControlField()
{
}

ControlField::ControlField(unsigned char data)
{
	set(data);
}

ControlField::~ControlField()
{
}

void ControlField::setDirection(unsigned char direction)
{
	BOOST_ASSERT((direction & ~DirectionMask) == 0);

	unsigned char data = get();
	data &= ~DirectionMask;
	data |= direction & 0x80;

	set(data);
}

unsigned char ControlField::getDirection() const
{
	return get() & DirectionMask;
}

void ControlField::setPrimaryMessage(unsigned char primaryMessage)
{
	BOOST_ASSERT((primaryMessage & ~PrimaryMessageMask) == 0);

	unsigned char data = get();
	data &= ~PrimaryMessageMask;
	data |= primaryMessage & PrimaryMessageMask;

	set(data);
}

unsigned char ControlField::getPrimaryMessage() const
{
	return get() & PrimaryMessageMask;
}

void ControlField::setFrameCountBit(unsigned char frameCountBit)
{
	BOOST_ASSERT((frameCountBit & ~FrameCountBitMask) == 0);

	unsigned char data = get();
	data &= ~FrameCountBitMask;
	data |= frameCountBit & FrameCountBitMask;

	set(data);
}

unsigned char ControlField::getFrameCountBit() const
{
	return get() & FrameCountBitMask;
}

void ControlField::setFrameCountBitValid(unsigned char frameCountBitValid)
{
	BOOST_ASSERT((frameCountBitValid & ~FrameCountBitValidMask) == 0);

	unsigned char data = get();
	data &= ~FrameCountBitValidMask;
	data |= frameCountBitValid & FrameCountBitValidMask;

	set(data);
}

unsigned char ControlField::getFrameCountBitValid() const
{
	return get() & 0x10;
}

void ControlField::setFunctionCode(unsigned char functionCode)
{
	BOOST_ASSERT((functionCode & ~FunctionCodeMask) == 0);

	unsigned char data = get();
	data &= ~FunctionCodeMask;
	data |= functionCode & FunctionCodeMask;

	set(data);
}

unsigned char ControlField::getFunctionCode() const
{
	return get() & FunctionCodeMask;
}
