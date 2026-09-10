//-----------------------------------------------------------------------------
// CLineSensor.cpp
//-----------------------------------------------------------------------------

#include "CLineSensor.h"
#include "CVecMath.h"

#include <cmath>

const float CLineSensor::kRightAngleRadians = 0.5f * float( M_PI );

const int CLineSensor::kDotRadius = 3;
const Color CLineSensor::kOnLineColor = GREEN;
const Color CLineSensor::kOffLineColor = RED;

//-----------------------------------------------------------------------------
CLineSensor::CLineSensor( float aForwardOffset, float aSidewaysOffset )
    :
        mForwardOffset( aForwardOffset ),
        mSidewaysOffset( aSidewaysOffset )
{
}


//-----------------------------------------------------------------------------
// "Forward" is the heading direction; "sideways" is a quarter turn from it,
// the same +90 degrees = right convention used everywhere else in the sim.
//-----------------------------------------------------------------------------
Vec2D CLineSensor::GetWorldPosition( const CPose& arRobotPose ) const
{
    Vec2D Forward = CVecMath::FromAngle( arRobotPose.mHeading );
    Vec2D Right = CVecMath::FromAngle( arRobotPose.mHeading + kRightAngleRadians );

    Vec2D Offset = CVecMath::Add( CVecMath::Scale( Forward, mForwardOffset ),
                                   CVecMath::Scale( Right, mSidewaysOffset ) );

    return CVecMath::Add( arRobotPose.mPosition, Offset );
}


//-----------------------------------------------------------------------------
bool CLineSensor::Sense( const CPose& arRobotPose, const CFloorLine& arLine ) const
{
    return arLine.IsPointOnLine( GetWorldPosition( arRobotPose ) );
}


//-----------------------------------------------------------------------------
void CLineSensor::Draw( CRender& arRender, const CPose& arRobotPose, bool aOnLine ) const
{
    Color DotColor = aOnLine ? kOnLineColor : kOffLineColor;

    arRender.DrawCircle( GetWorldPosition( arRobotPose ), kDotRadius, DotColor );
}
