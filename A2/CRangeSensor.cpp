//-----------------------------------------------------------------------------
// CRangeSensor.cpp
//-----------------------------------------------------------------------------

#include "CRangeSensor.h"
#include "CVecMath.h"

namespace
{
    const Color kRayColor = Color{ 255, 200, 0, 120 };   // translucent amber
}

//-----------------------------------------------------------------------------
CRangeSensor::CRangeSensor( float aMountAngleRadians, float aMaxRange )
    :
        mMountAngleRadians( aMountAngleRadians ),
        mMaxRange( aMaxRange )
{
}


//-----------------------------------------------------------------------------
float CRangeSensor::Sense( const CPose& arRobotPose, const CRoom& arRoom ) const
{
    float WorldAngle = arRobotPose.mHeading + mMountAngleRadians;
    return arRoom.SenseDistance( arRobotPose.mPosition, WorldAngle, mMaxRange );
}


//-----------------------------------------------------------------------------
void CRangeSensor::Draw( CRender& arRender, const CPose& arRobotPose,
                          float aMeasuredDistance ) const
{
    float WorldAngle = arRobotPose.mHeading + mMountAngleRadians;
    Vec2D Direction = CVecMath::FromAngle( WorldAngle );
    Vec2D RayEnd = CVecMath::Add( arRobotPose.mPosition,
                                   CVecMath::Scale( Direction, aMeasuredDistance ) );

    arRender.DrawLine( arRobotPose.mPosition, RayEnd, 1.0f, kRayColor );
}
