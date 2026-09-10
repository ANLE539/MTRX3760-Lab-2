//-----------------------------------------------------------------------------
// CRobot.h
//
// Abstract base for a simulated robot: a disc of a fixed radius, carried on
// two independently-driven wheels, that leaves a trail behind it as it goes.
//
// A concrete robot supplies ComputeWheelSpeeds() (read its own sensors,
// decide how fast each wheel should turn) and may extend Draw() to show its
// sensors. Everything about moving, trailing and drawing the body is common
// and lives here.
//-----------------------------------------------------------------------------

#ifndef CROBOT_H
#define CROBOT_H

#include "CDifferentialDrive.h"   // for CWheelSpeeds
#include "CLoopReader.h"          // for CPose
#include "CRender.h"
#include "CTrail.h"

//-----------------------------------------------------------------------------
class CRobot
{
    public:
        //---Ctor/Dtor---
        CRobot( const CPose& arStartPose, Color aBodyColor );
        virtual ~CRobot();

        //---Simulation---

        // Advances the robot by one fixed timestep: asks the concrete robot
        // for wheel speeds, drives the wheels, records the trail. Not
        // virtual - subclasses customise behaviour via ComputeWheelSpeeds()
        // and OnAfterMove(), not by overriding the update sequence itself.
        void Update( float aTimeStep );

        //---Drawing---
        virtual void Draw( CRender& arRender ) const;

        //---Access---
        const CPose& GetPose() const;
        int GetUpdateCount() const;

    protected:
        //---For subclasses to decide how fast each wheel should turn---
        virtual CWheelSpeeds ComputeWheelSpeeds() const = 0;

        //---An optional hook run after the robot has moved (e.g. collision checks)---
        virtual void OnAfterMove();

        //---Lets a subclass correct the position after the fact, e.g. to push
        //---the robot back out of a wall it has just collided with---
        void SetPosition( Vec2D aPosition );

        //---Consts every robot shares, visible to subclasses that need them---
        static const float kBodyRadius;
        static const float kTrackWidth;

    private:
        //---Consts governing how the body is drawn---
        static const float kHeadingLineFactor;
        static const float kHeadingLineThickness;

        //---Pose and motion---
        CPose mPose;
        CDifferentialDrive mDrive;

        //---History---
        CTrail mTrail;
        int mUpdateCount;

        //---Appearance---
        Color mBodyColor;
};

#endif
