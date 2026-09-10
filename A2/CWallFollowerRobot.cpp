//-----------------------------------------------------------------------------
// CWallFollowerRobot.cpp
//-----------------------------------------------------------------------------

#include "CWallFollowerRobot.h"

#include <cmath>
#include <iostream>

//---Sensor mounting angles, as fractions of a half turn from the heading-----
const float CWallFollowerRobot::kRightSensorAngle = 0.5f * float( M_PI );     // 90 degrees
const float CWallFollowerRobot::kFrontRightSensorAngle = 0.25f * float( M_PI ); // 45 degrees

const float CWallFollowerRobot::kMaxSensorRange = 300.0f;
const float CWallFollowerRobot::kTargetWallDistance = 55.0f;
const float CWallFollowerRobot::kBaseWheelSpeed = 45.0f;
const float CWallFollowerRobot::kDistanceGain = 0.9f;
const float CWallFollowerRobot::kCornerGain = 0.6f;
const float CWallFollowerRobot::kMaxSteer = 60.0f;
const float CWallFollowerRobot::kSqrt2 = 1.41421356f;

const Color CWallFollowerRobot::kBodyColor = SKYBLUE;

//-----------------------------------------------------------------------------
CWallFollowerRobot::CWallFollowerRobot( const CPose& arStartPose, const CRoom& arRoom )
    :
        CRobot( arStartPose, kBodyColor ),
        mrRoom( arRoom ),
        mRightSensor( kRightSensorAngle, kMaxSensorRange ),
        mFrontRightSensor( kFrontRightSensorAngle, kMaxSensorRange ),
        mWasColliding( false ),
        mCollisionCount( 0 )
{
}


//-----------------------------------------------------------------------------
CWheelSpeeds CWallFollowerRobot::ComputeWheelSpeeds() const
{
    float RightDistance = mRightSensor.Sense( GetPose(), mrRoom );
    float FrontRightDistance = mFrontRightSensor.Sense( GetPose(), mrRoom );

    float Steer = 0.0f;

    if( RightDistance >= kMaxSensorRange && FrontRightDistance >= kMaxSensorRange )
    {
        // Lost the wall entirely (just rounded an outside corner): turn hard
        // toward where it should be until a sensor finds it again.
        Steer = kMaxSteer;
    }
    else
    {
        // Hold the target distance off the wall.
        float DistanceError = RightDistance - kTargetWallDistance;

        // Anticipate corners: compare what the 45-degree sensor sees to what
        // it would see if the wall were straight and parallel to the robot.
        float ExpectedFrontRightDistance = RightDistance * kSqrt2;
        float CornerError = FrontRightDistance - ExpectedFrontRightDistance;

        Steer = kDistanceGain * DistanceError + kCornerGain * CornerError;

        if( Steer > kMaxSteer )
        {
            Steer = kMaxSteer;
        }
        else if( Steer < -kMaxSteer )
        {
            Steer = -kMaxSteer;
        }
    }

    // Positive Steer turns the robot toward the wall (right); negative turns
    // it away (left) - see CDifferentialDrive.h for the heading convention.
    CWheelSpeeds Result = { kBaseWheelSpeed + Steer, kBaseWheelSpeed - Steer };

    return Result;
}


//-----------------------------------------------------------------------------
void CWallFollowerRobot::OnAfterMove()
{
    bool IsCollidingNow = mrRoom.IsColliding( GetPose().mPosition, kBodyRadius );

    // Count and report a collision only on the moment it starts, not on
    // every update the robot happens to still be touching the wall.
    if( IsCollidingNow && !mWasColliding )
    {
        ++mCollisionCount;
        std::cout << "[Collision] Wall follower hit a wall at update "
                  << GetUpdateCount() << " (collision #" << mCollisionCount << ")"
                  << std::endl;
    }
    mWasColliding = IsCollidingNow;

    if( IsCollidingNow )
    {
        // Push the robot back out so it does not sink into or slide along
        // inside the wall geometry.
        SetPosition( mrRoom.ResolveCollision( GetPose().mPosition, kBodyRadius ) );
    }
}


//-----------------------------------------------------------------------------
void CWallFollowerRobot::Draw( CRender& arRender ) const
{
    CRobot::Draw( arRender );

    float RightDistance = mRightSensor.Sense( GetPose(), mrRoom );
    float FrontRightDistance = mFrontRightSensor.Sense( GetPose(), mrRoom );
    mRightSensor.Draw( arRender, GetPose(), RightDistance );
    mFrontRightSensor.Draw( arRender, GetPose(), FrontRightDistance );
}


//-----------------------------------------------------------------------------
int CWallFollowerRobot::GetCollisionCount() const
{
    return mCollisionCount;
}
