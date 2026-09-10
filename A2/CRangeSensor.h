//-----------------------------------------------------------------------------
// CRangeSensor.h
//
// A single range sensor, rigidly mounted on a robot at a fixed angle offset
// from the robot's own heading. Reports the distance to the first wall its
// ray meets, in a given CRoom.
//-----------------------------------------------------------------------------

#ifndef CRANGESENSOR_H
#define CRANGESENSOR_H

#include "CLoopReader.h"   // for CPose
#include "CRender.h"
#include "CRoom.h"

//-----------------------------------------------------------------------------
class CRangeSensor
{
    public:
        //---Ctor---
        CRangeSensor( float aMountAngleRadians, float aMaxRange );

        //---Sensing---

        // Distance from the robot's centre to the first wall the ray meets,
        // or the sensor's maximum range when it meets none.
        float Sense( const CPose& arRobotPose, const CRoom& arRoom ) const;

        //---Drawing (shows the ray, for visual debugging)---
        void Draw( CRender& arRender, const CPose& arRobotPose, float aMeasuredDistance ) const;

    private:
        //---Consts governing how the ray is drawn---
        static const Color kRayColor;
        static const float kRayThickness;

        //---Where the sensor points, relative to the robot's own heading---
        const float mMountAngleRadians;
        const float mMaxRange;
};

#endif
