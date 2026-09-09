//-----------------------------------------------------------------------------
// CLineFollowerRobot.cpp
//-----------------------------------------------------------------------------

#include "CLineFollowerRobot.h"

namespace
{
    const Color kBodyColor = ORANGE;
}

const float CLineFollowerRobot::kBaseWheelSpeed = 30.0f;
const float CLineFollowerRobot::kSteer = 10.0f;

// The turn used when the line is lost completely needs to be tight - tight
// enough that circling on it brings the robot back round to wherever the
// line picks up again on the far side of a corner. Too gentle a turn here
// and the robot just loops forever a bit further out, never crossing the
// line again.
const float CLineFollowerRobot::kSearchSteer = 35.0f;

const float CLineFollowerRobot::kSensorForwardOffset = 4.0f;
const float CLineFollowerRobot::kSensorSidewaysOffset = 3.0f;

//-----------------------------------------------------------------------------
CLineFollowerRobot::CLineFollowerRobot( const CPose& arStartPose, const CFloorLine& arLine )
    :
        CRobot( arStartPose, kBodyColor ),
        mrLine( arLine ),
        mCentreSensor( kSensorForwardOffset, 0.0f ),
        mEdgeSensor( kSensorForwardOffset, kSensorSidewaysOffset )
{
}


//-----------------------------------------------------------------------------
void CLineFollowerRobot::ComputeWheelSpeeds( float& arLeftWheelSpeed,
                                              float& arRightWheelSpeed ) const
{
    bool CentreOnLine = mCentreSensor.Sense( GetPose(), mrLine );
    bool EdgeOnLine = mEdgeSensor.Sense( GetPose(), mrLine );

    // Same wheel convention as the wall follower - positive steer swings the
    // robot right, negative swings it left.
    float Steer = 0.0f;

    if( CentreOnLine && EdgeOnLine )
    {
        Steer = -kSteer;   // both sensors are on the line - too far right, pull back
    }
    else if( !CentreOnLine && EdgeOnLine )
    {
        Steer = kSteer;   // only the edge sensor sees it - drifted left, steer back in
    }
    else if( !CentreOnLine && !EdgeOnLine )
    {
        Steer = kSearchSteer;   // lost it - probably just went round a corner, turn and look
    }
    // else centre on, edge off: right where it should be, drive straight.

    arLeftWheelSpeed = kBaseWheelSpeed + Steer;
    arRightWheelSpeed = kBaseWheelSpeed - Steer;
}


//-----------------------------------------------------------------------------
void CLineFollowerRobot::Draw( CRender& arRender ) const
{
    CRobot::Draw( arRender );

    mCentreSensor.Draw( arRender, GetPose(), mCentreSensor.Sense( GetPose(), mrLine ) );
    mEdgeSensor.Draw( arRender, GetPose(), mEdgeSensor.Sense( GetPose(), mrLine ) );
}
