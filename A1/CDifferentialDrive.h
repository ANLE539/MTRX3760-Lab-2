//-----------------------------------------------------------------------------
// CDifferentialDrive.h
//
// The kinematics of a two-wheeled robot: given a pose and a speed for each
// wheel, works out the pose one fixed timestep later. Knows nothing about
// sensors, control, walls or lines - purely "if the wheels turn like this,
// where does the robot end up".
//
// Heading follows CPose's convention: 0 radians faces +x (screen right), and
// the angle increases clockwise on screen (because screen y increases
// downward). With that convention, driving the right wheel faster than the
// left turns the robot to its left (heading decreases) exactly as it would
// on a real differential-drive robot.
//-----------------------------------------------------------------------------

#ifndef CDIFFERENTIALDRIVE_H
#define CDIFFERENTIALDRIVE_H

#include "CLoopReader.h"   // for CPose

//-----------------------------------------------------------------------------
class CDifferentialDrive
{
    public:
        //---Ctor---
        explicit CDifferentialDrive( float aTrackWidth );

        // The pose aTimeStep seconds after arPose, if the left wheel runs at
        // aLeftWheelSpeed and the right at aRightWheelSpeed (units per
        // second).
        CPose Step( const CPose& arPose, float aLeftWheelSpeed, float aRightWheelSpeed,
                    float aTimeStep ) const;

    private:
        //---The distance between the two wheels---
        const float mTrackWidth;
};

#endif
