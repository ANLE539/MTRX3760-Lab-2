//-----------------------------------------------------------------------------
// CSimulation.h
//
// Owns the render window and the room, and drives every robot registered
// with it through a fixed number of fixed-length simulated timesteps. Each
// call to Update() (whatever real time it takes to compute or draw) advances
// every robot's simulated clock by exactly the same fixed amount, so the
// simulation's behaviour does not depend on how fast it is able to render.
//
// CSimulation does not know anything about wall following or line following
// specifically - it only knows CRobot's interface, so the same class runs
// A1 (one robot) and A2 (two robots) alike.
//-----------------------------------------------------------------------------

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CFloorLine.h"
#include "CRender.h"
#include "CRobot.h"
#include "CRoom.h"

#include <vector>

//-----------------------------------------------------------------------------
class CSimulation
{
    public:
        //---Ctor---
        CSimulation( CRender& arRender, const CRoom& arRoom, int aUpdatesToRun );

        //---Registration---
        void AddRobot( CRobot& arRobot );

        // Optional - only used in A2, where there's a floor line to draw
        // alongside the walls. Left unset, nothing extra gets drawn.
        void SetFloorLine( const CFloorLine* apLine );

        //---Runs every update, then keeps the window open (showing the
        //---finished trails) until the person closes it---
        void Run();

        //---Access---
        int GetUpdatesCompleted() const;

        //---Consts---
        static const float kFixedTimeStep;

    private:
        //---Drawing one frame---
        void DrawFrame() const;

        //---The window---
        CRender& mrRender;

        //---The room every robot shares---
        const CRoom& mrRoom;

        //---The floor line, if this run has one---
        const CFloorLine* mpFloorLine;

        //---The robots being simulated. Not owned - the caller constructs
        //---and destroys them---
        std::vector<CRobot*> mpRobots;

        //---How long to run for---
        const int mUpdatesToRun;
        int mUpdatesCompleted;
};

#endif
