//-----------------------------------------------------------------------------
// CLineSensor.cpp
//-----------------------------------------------------------------------------

#include "CLineSensor.h"
#include "CVecMath.h"

//-----------------------------------------------------------------------------
CLineSensor::CLineSensor( float aForwardOffset, float aSidewaysOffset )
    :
        mForwardOffset( aForwardOffset ),
        mSidewaysOffset( aSidewaysOffset )
{
}


//-----------------------------------------------------------------------------
Vec2D CLineSensor::GetWorldPosition( const CPose& arRobotPose ) const
{
    // "Forward" is just the heading direction, "sideways" is 90 degrees off
    // it (same +90 = right convention used everywhere else in the sim).
    Vec2D Forward = CVecMath::FromAngle( arRobotPose.mHeading );
    Vec2D Right = CVecMath::FromAngle( arRobotPose.mHeading + 1.5707963f );

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
    Color DotColor = aOnLine ? GREEN : RED;
    arRender.DrawCircle( GetWorldPosition( arRobotPose ), 3, DotColor );
}
