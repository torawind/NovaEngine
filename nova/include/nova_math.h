﻿/***************************************************************************
 *   Copyright (C) 2009 by Sirius										   *
 *	 Vdov Nikita Sergeevich	(c)											   *
 *	 siriusnick@gmail.com												   *
 *																		   *
 *	 This source file is part of NovaEngine								   *
 *	 (Object-oriented Game Development Engine)							   *
 *																		   *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program;					                           *
 ***************************************************************************/
// Wild Magic Source Code
// David Eberly
// http://www.geometrictools.com
// Copyright (c) 1998-2008
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.  The license is available for reading at
// either of the locations:
//     http://www.gnu.org/copyleft/lgpl.html
//     http://www.geometrictools.com/License/WildMagicLicense.pdf
#pragma once

#include "nova_error.h"

namespace nova
{

template <class Real> class CMath
{
public:
    // Wrappers to hide implementations of functions.  The ACos and ASin
    // functions clamp the input argument to [-1,1] to avoid NaN issues
    // when the input is slightly larger than 1 or slightly smaller than -1.
    // Other functions have the potential for using a fast and approximate
    // algorithm rather than calling the standard CMath library functions.
    static Real ACos (Real fValue);
    static Real ASin (Real fValue);
    static Real ATan (Real fValue);
    static Real ATan2 (Real fY, Real fX);
    static Real Ceil (Real fValue);
    static Real Cos (Real fValue);
    static Real Exp (Real fValue);
    static Real FAbs (Real fValue);
    static Real Floor (Real fValue);
    static Real FMod (Real fX, Real fY);
    static Real InvSqrt (Real fValue);
    static Real Log (Real fValue);
    static Real Log2 (Real fValue);
    static Real Log10 (Real fValue);
    static Real Pow (Real fBase, Real fExponent);
    static Real Sin (Real fValue);
    static Real Sqr (Real fValue);
    static Real Sqrt (Real fValue);
    static Real Tan (Real fValue);

    // Return -1 if the input is negative, 0 if the input is zero, and +1
    // if the input is positive.
    static int Sign (int iValue);
    static Real Sign (Real fValue);

    // Generate a random number in [0,1).  The random number generator may
    // be seeded by a first call to UnitRandom with a positive seed.
    static Real UnitRandom (unsigned int uiSeed = 0);

    // Generate a random number in [-1,1).  The random number generator may
    // be seeded by a first call to SymmetricRandom with a positive seed.
    static Real SymmetricRandom (unsigned int uiSeed = 0);

    // Generate a random number in [min,max).  The random number generator may
    // be seeded by a first call to IntervalRandom with a positive seed.
    static Real IntervalRandom (Real fMin, Real fMax,
        unsigned int uiSeed = 0);

	static int Rand();
	static void RandSeed(unsigned int uiSeed = 0);

    // Fast evaluation of trigonometric and inverse trigonometric functions
    // using polynomial approximations.  The speed ups were measured on an
    // AMD 2800 (2.08 GHz) processor using Visual Studion .NET 2003 with a
    // release build.

    // The input must be in [0,pi/2].
    // max error sin0 = 1.7e-04, speed up = 4.0
    // max error sin1 = 1.9e-08, speed up = 2.8
    static Real FastSin0 (Real fAngle);
    static Real FastSin1 (Real fAngle);

    // The input must be in [0,pi/2]
    // max error cos0 = 1.2e-03, speed up = 4.5
    // max error cos1 = 6.5e-09, speed up = 2.8
    static Real FastCos0 (Real fAngle);
    static Real FastCos1 (Real fAngle);

    // The input must be in [0,pi/4].
    // max error tan0 = 8.1e-04, speed up = 5.6
    // max error tan1 = 1.9e-08, speed up = 3.4
    static Real FastTan0 (Real fAngle);
    static Real FastTan1 (Real fAngle);

    // The input must be in [0,1].
    // max error invsin0 = 6.8e-05, speed up = 7.5
    // max error invsin1 = 1.4e-07, speed up = 5.5
    static Real FastInvSin0 (Real fValue);
    static Real FastInvSin1 (Real fValue);

    // The input must be in [0,1].
    // max error invcos0 = 6.8e-05, speed up = 7.5
    // max error invcos1 = 1.4e-07, speed up = 5.7
    static Real FastInvCos0 (Real fValue);
    static Real FastInvCos1 (Real fValue);

    // The input must be in [-1,1].
    // max error invtan0 = 1.2e-05, speed up = 2.8
    // max error invtan1 = 2.3e-08, speed up = 1.8
    static Real FastInvTan0 (Real fValue);
    static Real FastInvTan1 (Real fValue);

    // A fast approximation to 1/sqrt.
    static Real FastInvSqrt (Real fValue);

    // Fast approximations to exp(-x).  The input x must be in [0,infinity).
    // max error negexp0 = 0.00024, speed up = 25.4
    // max error negexp1 = 0.000024, speed up = 25.4
    // max error negexp2 = 0.0000024, speed up = 20.5
    // max error negexp3 = 0.00000025, speed up = 17.3
    static Real FastNegExp0 (Real fValue);
    static Real FastNegExp1 (Real fValue);
    static Real FastNegExp2 (Real fValue);
    static Real FastNegExp3 (Real fValue);

    // common constants
    NOVA_EXPORT static const Real EPSILON;
    NOVA_EXPORT static const Real ZERO_TOLERANCE;
    NOVA_EXPORT static const Real MAX_REAL;
    NOVA_EXPORT static const Real PI;
    NOVA_EXPORT static const Real TWO_PI;
    NOVA_EXPORT static const Real HALF_PI;
    NOVA_EXPORT static const Real INV_PI;
    NOVA_EXPORT static const Real INV_TWO_PI;
    NOVA_EXPORT static const Real DEG_TO_RAD;
    NOVA_EXPORT static const Real RAD_TO_DEG;
    NOVA_EXPORT static const Real LN_2;
    NOVA_EXPORT static const Real LN_10;
    NOVA_EXPORT static const Real INV_LN_2;
    NOVA_EXPORT static const Real INV_LN_10;
};

template <class Real>
Real CMath<Real>::ACos (Real fValue)
{
    if (-(Real)1.0 < fValue)
    {
        if (fValue < (Real)1.0)
        {
            return (Real)acos((double)fValue);
        }
        else
        {
            return (Real)0.0;
        }
    }
    else
    {
        return PI;
    }
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::ASin (Real fValue)
{
    if (-(Real)1.0 < fValue)
    {
        if (fValue < (Real)1.0)
        {
            return (Real)asin((double)fValue);
        }
        else
        {
            return HALF_PI;
        }
    }
    else
    {
        return -HALF_PI;
    }
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::ATan (Real fValue)
{
    return (Real)atan((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::ATan2 (Real fY, Real fX)
{
    return (Real)atan2((double)fY,(double)fX);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Ceil (Real fValue)
{
    return (Real)ceil((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Cos (Real fValue)
{
    return (Real)cos((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Exp (Real fValue)
{
    return (Real)exp((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FAbs (Real fValue)
{
    return (Real)fabs((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Floor (Real fValue)
{
    return (Real)floor((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FMod (Real fX, Real fY)
{
    return (Real)fmod((double)fX,(double)fY);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::InvSqrt (Real fValue)
{
    return (Real)(1.0/sqrt((double)fValue));
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Log (Real fValue)
{
    return (Real)log((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Log2 (Real fValue)
{
    return CMath<Real>::INV_LN_2 * (Real)log((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Log10 (Real fValue)
{
    return CMath<Real>::INV_LN_10 * (Real)log((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Pow (Real fBase, Real fExponent)
{
    return (Real)pow((double)fBase,(double)fExponent);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Sin (Real fValue)
{
    return (Real)sin((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Sqr (Real fValue)
{
    return fValue*fValue;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Sqrt (Real fValue)
{
    return (Real)sqrt((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Tan (Real fValue)
{
    return (Real)tan((double)fValue);
}
//----------------------------------------------------------------------------
template <class Real>
int CMath<Real>::Sign (int iValue)
{
    if (iValue > 0)
    {
        return 1;
    }

    if (iValue < 0)
    {
        return -1;
    }

    return 0;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::Sign (Real fValue)
{
    if (fValue > (Real)0.0)
    {
        return (Real)1.0;
    }

    if (fValue < (Real)0.0)
    {
        return -(Real)1.0;
    }

    return (Real)0.0;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::UnitRandom (unsigned int uiSeed )
{
    if (uiSeed > 0)
    {
        srand(uiSeed);
    }

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return (Real)dRatio;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::SymmetricRandom (unsigned int uiSeed)
{
    if (uiSeed > 0.0)
    {
        srand(uiSeed);
    }

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return (Real)(2.0*dRatio - 1.0);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::IntervalRandom (Real fMin, Real fMax, unsigned int uiSeed)
{
    if (uiSeed > 0)
    {
        srand(uiSeed);
    }

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return fMin+(fMax-fMin)*((Real)dRatio);
}
//----------------------------------------------------------------------------
template <class Real>
int CMath<Real>::Rand()
{
	return rand();
}

template <class Real>
void CMath<Real>::RandSeed(unsigned int uiSeed)
{
	srand(uiSeed);
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastSin0 (Real fAngle)
{
    Real fASqr = fAngle*fAngle;
    Real fResult = (Real)7.61e-03;
    fResult *= fASqr;
    fResult -= (Real)1.6605e-01;
    fResult *= fASqr;
    fResult += (Real)1.0;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastSin1 (Real fAngle)
{
    Real fASqr = fAngle*fAngle;
    Real fResult = -(Real)2.39e-08;
    fResult *= fASqr;
    fResult += (Real)2.7526e-06;
    fResult *= fASqr;
    fResult -= (Real)1.98409e-04;
    fResult *= fASqr;
    fResult += (Real)8.3333315e-03;
    fResult *= fASqr;
    fResult -= (Real)1.666666664e-01;
    fResult *= fASqr;
    fResult += (Real)1.0;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastCos0 (Real fAngle)
{
    Real fASqr = fAngle*fAngle;
    Real fResult = (Real)3.705e-02;
    fResult *= fASqr;
    fResult -= (Real)4.967e-01;
    fResult *= fASqr;
    fResult += (Real)1.0;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastCos1 (Real fAngle)
{
    Real fASqr = fAngle*fAngle;
    Real fResult = -(Real)2.605e-07;
    fResult *= fASqr;
    fResult += (Real)2.47609e-05;
    fResult *= fASqr;
    fResult -= (Real)1.3888397e-03;
    fResult *= fASqr;
    fResult += (Real)4.16666418e-02;
    fResult *= fASqr;
    fResult -= (Real)4.999999963e-01;
    fResult *= fASqr;
    fResult += (Real)1.0;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastTan0 (Real fAngle)
{
    Real fASqr = fAngle*fAngle;
    Real fResult = (Real)2.033e-01;
    fResult *= fASqr;
    fResult += (Real)3.1755e-01;
    fResult *= fASqr;
    fResult += (Real)1.0;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastTan1 (Real fAngle)
{
    Real fASqr = fAngle*fAngle;
    Real fResult = (Real)9.5168091e-03;
    fResult *= fASqr;
    fResult += (Real)2.900525e-03;
    fResult *= fASqr;
    fResult += (Real)2.45650893e-02;
    fResult *= fASqr;
    fResult += (Real)5.33740603e-02;
    fResult *= fASqr;
    fResult += (Real)1.333923995e-01;
    fResult *= fASqr;
    fResult += (Real)3.333314036e-01;
    fResult *= fASqr;
    fResult += (Real)1.0;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastInvSin0 (Real fValue)
{
    Real fRoot = CMath<Real>::Sqrt(((Real)1.0)-fValue);
    Real fResult = -(Real)0.0187293;
    fResult *= fValue;
    fResult += (Real)0.0742610;
    fResult *= fValue;
    fResult -= (Real)0.2121144;
    fResult *= fValue;
    fResult += (Real)1.5707288;
    fResult = HALF_PI - fRoot*fResult;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastInvSin1 (Real fValue)
{
    Real fRoot = CMath<Real>::Sqrt(FAbs(((Real)1.0)-fValue));
    Real fResult = -(Real)0.0012624911;
    fResult *= fValue;
    fResult += (Real)0.0066700901;
    fResult *= fValue;
    fResult -= (Real)0.0170881256;
    fResult *= fValue;
    fResult += (Real)0.0308918810;
    fResult *= fValue;
    fResult -= (Real)0.0501743046;
    fResult *= fValue;
    fResult += (Real)0.0889789874;
    fResult *= fValue;
    fResult -= (Real)0.2145988016;
    fResult *= fValue;
    fResult += (Real)1.5707963050;
    fResult = HALF_PI - fRoot*fResult;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastInvCos0 (Real fValue)
{
    Real fRoot = CMath<Real>::Sqrt(((Real)1.0)-fValue);
    Real fResult = -(Real)0.0187293;
    fResult *= fValue;
    fResult += (Real)0.0742610;
    fResult *= fValue;
    fResult -= (Real)0.2121144;
    fResult *= fValue;
    fResult += (Real)1.5707288;
    fResult *= fRoot;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastInvCos1 (Real fValue)
{
    Real fRoot = CMath<Real>::Sqrt(FAbs(((Real)1.0)-fValue));
    Real fResult = -(Real)0.0012624911;
    fResult *= fValue;
    fResult += (Real)0.0066700901;
    fResult *= fValue;
    fResult -= (Real)0.0170881256;
    fResult *= fValue;
    fResult += (Real)0.0308918810;
    fResult *= fValue;
    fResult -= (Real)0.0501743046;
    fResult *= fValue;
    fResult += (Real)0.0889789874;
    fResult *= fValue;
    fResult -= (Real)0.2145988016;
    fResult *= fValue;
    fResult += (Real)1.5707963050;
    fResult *= fRoot;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastInvTan0 (Real fValue)
{
    Real fVSqr = fValue*fValue;
    Real fResult = (Real)0.0208351;
    fResult *= fVSqr;
    fResult -= (Real)0.085133;
    fResult *= fVSqr;
    fResult += (Real)0.180141;
    fResult *= fVSqr;
    fResult -= (Real)0.3302995;
    fResult *= fVSqr;
    fResult += (Real)0.999866;
    fResult *= fValue;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastInvTan1 (Real fValue)
{
    Real fVSqr = fValue*fValue;
    Real fResult = (Real)0.0028662257;
    fResult *= fVSqr;
    fResult -= (Real)0.0161657367;
    fResult *= fVSqr;
    fResult += (Real)0.0429096138;
    fResult *= fVSqr;
    fResult -= (Real)0.0752896400;
    fResult *= fVSqr;
    fResult += (Real)0.1065626393;
    fResult *= fVSqr;
    fResult -= (Real)0.1420889944;
    fResult *= fVSqr;
    fResult += (Real)0.1999355085;
    fResult *= fVSqr;
    fResult -= (Real)0.3333314528;
    fResult *= fVSqr;
    fResult += (Real)1.0;
    fResult *= fValue;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastNegExp0 (Real fValue)
{
    Real fResult = (Real)0.0038278;
    fResult *= fValue;
    fResult += (Real)0.0292732;
    fResult *= fValue;
    fResult += (Real)0.2507213;
    fResult *= fValue;
    fResult += (Real)1.0;
    fResult *= fResult;
    fResult *= fResult;
    fResult = ((Real)1.0)/fResult;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastNegExp1 (Real fValue)
{
    Real fResult = (Real)0.00026695;
    fResult *= fValue;
    fResult += (Real)0.00227723;
    fResult *= fValue;
    fResult += (Real)0.03158565;
    fResult *= fValue;
    fResult += (Real)0.24991035;
    fResult *= fValue;
    fResult += (Real)1.0;
    fResult *= fResult;
    fResult *= fResult;
    fResult = ((Real)1.0)/fResult;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastNegExp2 (Real fValue)
{
    Real fResult = (Real)0.000014876;
    fResult *= fValue;
    fResult += (Real)0.000127992;
    fResult *= fValue;
    fResult += (Real)0.002673255;
    fResult *= fValue;
    fResult += (Real)0.031198056;
    fResult *= fValue;
    fResult += (Real)0.250010936;
    fResult *= fValue;
    fResult += (Real)1.0;
    fResult *= fResult;
    fResult *= fResult;
    fResult = ((Real)1.0)/fResult;
    return fResult;
}
//----------------------------------------------------------------------------
template <class Real>
Real CMath<Real>::FastNegExp3 (Real fValue)
{
    Real fResult = (Real)0.0000006906;
    fResult *= fValue;
    fResult += (Real)0.0000054302;
    fResult *= fValue;
    fResult += (Real)0.0001715620;
    fResult *= fValue;
    fResult += (Real)0.0025913712;
    fResult *= fValue;
    fResult += (Real)0.0312575832;
    fResult *= fValue;
    fResult += (Real)0.2499986842;
    fResult *= fValue;
    fResult += (Real)1.0;
    fResult *= fResult;
    fResult *= fResult;
    fResult = ((Real)1.0)/fResult;
    return fResult;
}

typedef CMath<real> CMathf;


}
