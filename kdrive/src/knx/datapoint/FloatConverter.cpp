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
#include "kdrive/knx/datapoint/FloatConverter.h"
#include <Poco/Exception.h>
#include <boost/assert.hpp>

using Poco::Exception;
using namespace kdrive::knx;

#ifndef LOBYTE
#define LOBYTE(w)           ((unsigned char)(w))
#endif

#ifndef HIBYTE
#define HIBYTE(w)           ((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))
#endif

/*********************************
** Anonymous Namespace
*********************************/

namespace
{

/*!
	The following function are adapted from the KNX-Stack
*/

enum
{
    BIT00 = (1 << 0),															// Bit 0
    BIT07 = (1 << 7)															// Bit 7
};

/*!
	Retrieves a 16 bit word
*/
inline unsigned short BUILD_WORD(unsigned char nHigh, unsigned char nLow)
{
	return (nHigh << 8) | nLow;
}

/*!
	Shift bits left
*/
inline unsigned int SHL(unsigned int nVal, unsigned int nShift)
{
	return (nVal << nShift);
}

/*!
	Shift bits right
*/
inline unsigned int SHR(unsigned int nVal, unsigned int nShift)
{
	return (nVal >> nShift);
}

/// This function converts a Knx-Float (DPT 9.xxx/EIS5)
/// to a long with scaling * 100
/// Return: true  if conversion was successful
/// 		false on error
bool KnxDpt_ConvKnxFlToSInt32(const unsigned char* pnKnxFloat, int* pnInt)
{
	unsigned short nRaw;														// KNX float raw data
	unsigned short nMultipli;													// Multiplicator
	int nMantissa;																// Mantissa

	if ((pnKnxFloat[0] == 0x7F) && (pnKnxFloat[1] == 0xFF))						// If Knx float error value
	{
		// invalid KNX value
		return false;															// Return error
	}

	nRaw = BUILD_WORD(pnKnxFloat[0], pnKnxFloat[1]);							// Build the raw word
	nMantissa = nRaw & 0x07FF;													// Extract pos. mantissa
	nMultipli = SHL(BIT00, (SHR(pnKnxFloat[0], 3) & 0x0F));						// Build 2^(exponent)

	if (pnKnxFloat[0] & 0x80)													// If value negative
	{
		// Mathematic for neg signment:
		//
		//	FloatValue = (nMantissa - 2048) * 2^nExponent / 100.0
		//
		//	Mantissa is ranged from -2048 to 2047 and 100 times of value.
		//	E.g. if you have only set the signed bit,
		//	the result is (0-2048)/100 = - 20.48 and not 0.0
		nMantissa -= 2048;														// Build complement
	}

	*pnInt = (int)nMantissa * nMultipli;										// Build signed int

	return true;																// Return success
}


/// This function converts a long with scaling * 100 to
/// a KNX-Float (DPT 9.xxx/EIS5)
/// Return: true  if conversion was successful
/// 		false on error
bool KnxDpt_ConvSInt32ToKnxFl(int nInt, unsigned char* pnKnxFloat)
{
	unsigned int nMantissa;														// Mantissa of Knx-Float
	unsigned short nMantissaMax;												// Maxima of mantissa
	unsigned char  nExponent;													// Exponent of Knx-Float
	unsigned char  nLostBit;													// Last shifted bit = lost bit

	if (nInt >= 0)																// If value positive
	{
		nMantissa = (unsigned int)nInt;											// Init mantissa
		nMantissaMax = 2047;													// Maxima of pos range
	}
	else																		// Else: Value negative
	{
		nMantissa = (unsigned int)-nInt;										// Init positive mantissa
		nMantissaMax = 2048;													// Maxima of neg range
	}

	// Note:
	//		If we shift nMantissa right, and nMantissa is odd we lost a bit!
	//		For the last lost bit, we increase nMantissa, this is an
	//		implizit binary rounding up of nMantissa.
	//		"(nMantissa + nLostBit)" in the while loop, make sure
	//		that we have no overflow in nMantissa.
	nLostBit  = 0;																// Set lost bit to 0
	nExponent = 0;																// Set exponent to 0
	while ((nMantissa + nLostBit) > nMantissaMax)								// Loop until (nInt / 2^nExponent) <= nMantissaMax
	{
		nLostBit = (unsigned char)(nMantissa & 0x01);							// Remember the lost bit in the next shift operation
		nMantissa >>= 1;														// Calc 2^nExponent
		nExponent++;															// Calc nExponent
	}

	nMantissa += nLostBit;														// Round up nMantissa

	if (nExponent > 15)															// If value is out of range
	{
		// Error: Value out of KNX float16 range
		pnKnxFloat[0] = 0x7F;													// Set Knx float to error value
		pnKnxFloat[1] = 0xFF;													// Set Knx float to error value
		return false;															// Return error
	}

	if (nInt >= 0)																// If value positive
	{
		pnKnxFloat[0] = 0x00;													// Set the sign to pos
	}
	else																		// Else: Value negative
	{
		nMantissa = 2048 - nMantissa;											// Calculate a signed mantissa
		pnKnxFloat[0] = BIT07;													// Set the sign to neg
	}

	// Set value to format SEEEEMMM MMMMMMMM
	// Sign already set before
	pnKnxFloat[0] |= (nExponent << 3) & 0x78;									// Set sEEEEmmm
	pnKnxFloat[0] |= HIBYTE(nMantissa);											// Set seeeMMM
	pnKnxFloat[1]  = LOBYTE(nMantissa);											// Set MMMMMMMM

	return true;																// Return success
}

/// This function converts a KNX-Float (DPT 9.xxx/EIS5) to a IEEE-Float
/// The format of the KNX-float is MEEEEMMM MMMMMMMM
/// Return: true  if conversion was successful
/// 		false on error
bool KnxDpt_ConvKnxFlToIeeeFl(const unsigned char* pnKnxFloat, float* pfValue)
{
	int nLongInt;																// Value*100 as int

	if (KnxDpt_ConvKnxFlToSInt32(pnKnxFloat, &nLongInt))							// If conversation was success
	{
		*pfValue = static_cast<float>(nLongInt / 100.0);						// Adapt value range
		return true;															// Return success
	}

	return false;																// Return error
}


/// This function converts a IEEE-Float to
/// a KNX-Float (DPT 9.xxx/EIS5)
/// Return: true  if conversion was successful
/// 		false on error
bool KnxDpt_ConvIeeeFlToKnxFl(float fIeeeFloat, unsigned char* pnKnxFloat)
{
	int nInt;																	// Value * 100

	fIeeeFloat *= 100.0;														// Map value to float*100
	if (fIeeeFloat > 0)															// If value positive
	{
		nInt = (int)(fIeeeFloat + 0.5);											// Map to signed int*100
	}
	else																		// Else: Value negative
	{
		nInt = (int)(fIeeeFloat - 0.5);											// Map to signed int*100
	}

	return KnxDpt_ConvSInt32ToKnxFl(nInt, pnKnxFloat);							// Do the conversion
}


} // end anonymous namespace

/*********************************
** FloatConverter
*********************************/

float FloatConverter::toFloat2(unsigned char msb, unsigned char lsb)
{
	return toFloat4FromFloat2(msb, lsb);
}

std::tuple<unsigned char, unsigned char> FloatConverter::toFloat2FromFloat4(float f)
{
	unsigned char knxFloat[2] = {0};

	if (!KnxDpt_ConvIeeeFlToKnxFl(f, knxFloat))
	{
		throw Exception("Value out of KNX float16 range");
	}

	return std::make_tuple(knxFloat[0], knxFloat[1]);
}

float FloatConverter::toFloat4FromFloat2(unsigned char msb, unsigned char lsb)
{
	const unsigned char knxFloat[2] = {msb, lsb};
	float ieeeFloat = 0;

	if (!KnxDpt_ConvKnxFlToIeeeFl(knxFloat, &ieeeFloat))
	{
		throw Exception("Invalid KNX float value");
	}

	return ieeeFloat;
}
