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
#include "kdrive/knx/telegrams/ft12/AckFrame.h"
#include "kdrive/knx/defines/FT12Constants.h"

using namespace kdrive::knx::ft12;

AckFrame::AckFrame()
{
	setDefaults();
}

AckFrame::~AckFrame()
{
}

bool AckFrame::isValid() const
{
	return get() == FT12Constants::AckFrame ? true : false;
}

void AckFrame::setDefaults()
{
	set(FT12Constants::AckFrame);
}
