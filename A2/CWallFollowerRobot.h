//-----------------------------------------------------------------------------
// CWallFollowerRobot.h
//
// A robot that follows the wall on its right using two range sensors: one
// aimed directly right (90 degrees from its heading) and one aimed forward
// and to the right (45 degrees from its heading).
//
// CONTROL STRATEGY
//
// The right sensor gives a distance-to-wall error: too far, steer toward the
// wall; too close, steer away. The forward-right sensor anticipates corners:
// on a straight wall it should read root-2 times the right sensor's
// distance (simple trigonometry, since it looks at the same wall at 45
// degrees instead of 90). When it reads less than that, the wall is curving
// in ahead (an inside corner) and the robot steers away pre-emptively; when
// it reads more, the wall is falling away (an outside corner) and the robot
// steers in to hug it. If both sensors read the sensor's maximum range, the
// wall has been lost (just around an outside corner) and the robot turns
// hard toward where the wall should be until it is reacquired.
//-----------------------------------------------------------------------------

#ifndef CWALLFOLLOWERROBOT_H
#define CWALLFOLLOWERROBOT_H

#include "CDifferentialDrive.h"   // for CWheelSpeeds
#include "CRangeSensor.h"
#include "CRender.h"
#include "CRobot.h"
#include "CRoom.h"

//-----------------------------------------------------------------------------
class CWallFollowerRobot : public CRobot
{
    public:
        //---Ctor---
        CWallFollowerRobot( const CPose& arStartPose, const CRoom& arRoom );

        //---Drawing (adds the sensor rays to the base body/trail drawing)---
        void Draw( CRender& arRender ) const override;

        //---Access---
        int GetCollisionCount() const;

    protected:
        //---CRobot interface---
        CWheelSpeeds ComputeWheelSpeeds() const override;
        void OnAfterMove() override;

    private:
        //---Where the two sensors point, relative to the robot's heading---
        static const float kRightSensorAngle;
        static const float kFrontRightSensorAngle;

        //---Consts governing the control law---
        static const float kMaxSensorRange;
        static const float kTargetWallDistance;
        static const float kBaseWheelSpeed;
        static const float kDistanceGain;
        static const float kCornerGain;
        static const float kMaxSteer;
        static const float kSqrt2;

        //---Appearance---
        static const Color kBodyColor;

        //---The room this robot senses and can collide with---
        const CRoom& mrRoom;

        //---Sensors, mounted at 90 (right) and 45 (forward-right) degrees---
        CRangeSensor mRightSensor;
        CRangeSensor mFrontRightSensor;

        //---Collision tracking---
        bool mWasColliding;
        int mCollisionCount;
};

#endif
