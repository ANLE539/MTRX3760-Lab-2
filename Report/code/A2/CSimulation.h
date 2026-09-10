//-----------------------------------------------------------------------------
// CSimulation.h
//
// Owns everything a run needs: the render window, the room and the floor line
// read from their map files, and the robots driving around in them. Advances
// every robot through a fixed number of fixed-length simulated timesteps.
// Each call to Update() (whatever real time it takes to compute or draw)
// advances every robot's simulated clock by exactly the same fixed amount, so
// the simulation's behaviour does not depend on how fast it is able to render.
//
// CSimulation knows what the world is made of - walls and a line - but not
// what any robot does with it. It only ever calls CRobot's interface, so one
// wall follower, one line follower, or both together run through exactly the
// same loop.
//-----------------------------------------------------------------------------

#ifndef CSIMULATION_H
#define CSIMULATION_H

#include "CFloorLine.h"
#include "CLoopReader.h"
#include "CRender.h"
#include "CRobot.h"
#include "CRoom.h"

#include <string>
#include <vector>

//-----------------------------------------------------------------------------
class CSimulation
{
    public:
        //---Ctor/Dtor---

        // Reads both map files and builds the world they describe. Ask
        // IsReady() afterwards: a map that could not be read leaves the
        // simulation with nothing worth running.
        CSimulation( const std::string& arWallsMapFilename,
                     const std::string& arLineMapFilename,
                     int aUpdatesToRun );
        ~CSimulation();

        //---State---

        // True when both map files were read and there is a world to drive in.
        bool IsReady() const;

        //---Registration---

        // Takes ownership of apRobot: it will be deleted with the simulation.
        // Ignores a null pointer rather than storing one.
        void AddRobot( CRobot* apRobot );

        //---What a robot needs to be built against---
        const CRoom& GetRoom() const;
        const CFloorLine& GetFloorLine() const;
        const CPose& GetWallStartPose() const;
        const CPose& GetLineStartPose() const;

        //---Runs every update, then keeps the window open (showing the
        //---finished trails) until the person closes it---
        void Run();

        //---Access---
        int GetUpdatesCompleted() const;

        //---Consts---
        static const float kFixedTimeStep;

    private:
        //---Drawing one frame. Not const: it drives the render window, which
        //---is an owned member here rather than a reference to someone
        //---else's, so drawing does change this object's state.
        void DrawFrame();

        //---Consts---

        // The assignment specifies the floor line is five units wide.
        static const float kLineWidth;

        //---The window---
        CRender mRender;

        //---The map files' contents, and the world built from them. Room and
        //---line are allocated once the files have been read, which is why
        //---they are pointers: member objects would have to be built before
        //---the constructor body has had a chance to read anything.
        CLoopReader mWallsLoop;
        CLoopReader mLineLoop;
        CRoom* mpRoom;
        CFloorLine* mpFloorLine;

        //---The robots being simulated, owned by this simulation---
        std::vector<CRobot*> mpRobots;

        //---How long to run for---
        const int mUpdatesToRun;
        int mUpdatesCompleted;

        //---Whether both map files were read successfully---
        bool mIsReady;
};

#endif
