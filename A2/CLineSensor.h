//-----------------------------------------------------------------------------
// CLineSensor.h
//
// One floor sensor, bolted to the robot at a fixed forward/sideways offset
// from its centre. Just reports whether the floor under it is line or not -
// no distance, no angle, just true/false.
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
        // aForwardOffset: distance ahead of the robot's centre, along its
        // heading. aSidewaysOffset: distance to the right of that (negative
        // for left).
        CLineSensor( float aForwardOffset, float aSidewaysOffset );

        bool Sense( const CPose& arRobotPose, const CFloorLine& arLine ) const;

        Vec2D GetWorldPosition( const CPose& arRobotPose ) const;

        void Draw( CRender& arRender, const CPose& arRobotPose, bool aOnLine ) const;

    private:
        const float mForwardOffset;
        const float mSidewaysOffset;
};

#endif
