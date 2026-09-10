//-----------------------------------------------------------------------------
// CDifferentialDrive.h
//
// The two wheels a robot stands on, and the kinematics that follow from them:
// given how fast each wheel has been commanded to turn, works out where the
// robot ends up one fixed timestep later. Knows nothing about sensors,
// control, walls or lines - purely "if the wheels turn like this, where does
// the robot end up".
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
#include "CWheel.h"

//-----------------------------------------------------------------------------
// A speed for each of the two wheels, in units of ground per second. Returned
// by a robot's controller and handed straight to the drive; it carries no
// behaviour of its own, only the pair of numbers that belong together.
//-----------------------------------------------------------------------------
struct CWheelSpeeds
{
    float mLeft;
    float mRight;
};

//-----------------------------------------------------------------------------
class CDifferentialDrive
{
    public:
        //---Ctor---
        explicit CDifferentialDrive( float aTrackWidth );

        //---Control---

        // Commands both wheels at once. Each wheel enforces its own speed
        // limit, so the pair asked for is not necessarily the pair delivered.
        void SetWheelSpeeds( const CWheelSpeeds& arSpeeds );

        //---Motion---

        // The pose aTimeStep seconds after arPose, given how far each wheel
        // rolls in that time at its currently commanded speed.
        CPose Step( const CPose& arPose, float aTimeStep ) const;

    private:
        //---Keeps a heading in [0, 2*PI) so it cannot grow without bound---
        static float NormaliseAngle( float aAngle );

        //---Consts---
        static const float kTwoPi;

        //---The distance between the two wheels---
        const float mTrackWidth;

        //---One wheel either side---
        CWheel mLeftWheel;
        CWheel mRightWheel;
};

#endif
