//-----------------------------------------------------------------------------
// CRangeSensor.cpp
//-----------------------------------------------------------------------------

#include "CRangeSensor.h"
#include "CVecMath.h"

// Translucent amber, so the two rays read as measurements laid over the scene
// rather than as part of the room.
const Color CRangeSensor::kRayColor = Color{ 255, 200, 0, 120 };
const float CRangeSensor::kRayThickness = 1.0f;

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

    arRender.DrawLine( arRobotPose.mPosition, RayEnd, kRayThickness, kRayColor );
}
