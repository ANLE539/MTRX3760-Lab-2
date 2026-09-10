//-----------------------------------------------------------------------------
// CLineSensor.h
//
// One floor sensor, bolted to the robot at a fixed forward/sideways offset
// from its centre. It reports only whether the floor under it is line or not:
// no distance, no angle, just true or false.
//-----------------------------------------------------------------------------

#ifndef CLINESENSOR_H
#define CLINESENSOR_H

#include "CFloorLine.h"
#include "CLoopReader.h"   // for CPose
#include "CRender.h"

//-----------------------------------------------------------------------------
class CLineSensor
{
    public:
        //---Ctor---

        // aForwardOffset: distance ahead of the robot's centre, along its
        // heading. aSidewaysOffset: distance to the right of that, negative
        // for left.
        CLineSensor( float aForwardOffset, float aSidewaysOffset );

        //---Sensing---
        bool Sense( const CPose& arRobotPose, const CFloorLine& arLine ) const;

        //---Where on the floor this sensor is looking, given a robot pose---
        Vec2D GetWorldPosition( const CPose& arRobotPose ) const;

        //---Drawing (a dot that turns green when the sensor sees line)---
        void Draw( CRender& arRender, const CPose& arRobotPose, bool aOnLine ) const;

    private:
        //---A quarter turn, in radians: "to the right" is the heading turned
        //---by this much, using the same clockwise convention as CPose---
        static const float kRightAngleRadians;

        //---How the sensor dot is drawn---
        static const int kDotRadius;
        static const Color kOnLineColor;
        static const Color kOffLineColor;

        //---Where the sensor sits, relative to the robot's centre---
        const float mForwardOffset;
        const float mSidewaysOffset;
};

#endif
