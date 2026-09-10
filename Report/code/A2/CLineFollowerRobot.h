//-----------------------------------------------------------------------------
// CLineFollowerRobot.h
//
// Follows the floor line with two on/off sensors: one sitting on the robot's
// centreline, one out to the right of it. Same idea as the wall follower
// really - hug an edge on your right - just here the "edge" is the right-
// hand side of the line rather than a wall, and the readings are boolean
// instead of distances.
//
// Normal running: centre sensor on the line, edge sensor just off it. Drift
// right and both go on (pull back left). Drift left and the centre sensor
// comes off first (steer right, toward the edge sensor). Lose both entirely
// and it's swung a corner - turn hard right until the line turns up again.
//-----------------------------------------------------------------------------

#ifndef CLINEFOLLOWERROBOT_H
#define CLINEFOLLOWERROBOT_H

#include "CDifferentialDrive.h"   // for CWheelSpeeds
#include "CFloorLine.h"
#include "CLineSensor.h"
#include "CRender.h"
#include "CRobot.h"

//-----------------------------------------------------------------------------
class CLineFollowerRobot : public CRobot
{
    public:
        //---Ctor---
        CLineFollowerRobot( const CPose& arStartPose, const CFloorLine& arLine );

        //---Drawing (adds the two sensor dots to the base body/trail drawing)---
        void Draw( CRender& arRender ) const override;

    protected:
        //---CRobot interface---
        CWheelSpeeds ComputeWheelSpeeds() const override;

    private:
        //---Consts governing the control law---
        static const float kBaseWheelSpeed;
        static const float kSteer;
        static const float kSearchSteer;

        //---Where the two floor sensors sit relative to the robot's centre---
        static const float kSensorForwardOffset;
        static const float kSensorSidewaysOffset;

        //---Appearance---
        static const Color kBodyColor;

        //---The line this robot follows---
        const CFloorLine& mrLine;

        //---One sensor on the centreline, one just to its right---
        CLineSensor mCentreSensor;
        CLineSensor mEdgeSensor;
};

#endif
