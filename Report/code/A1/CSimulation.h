//-----------------------------------------------------------------------------
// CSimulation.h
//
// Owns everything a run needs: the render window, the room read from a map
// file, and the robots driving around in it. Advances every robot through a
// fixed number of fixed-length simulated timesteps. Each call to Update()
// (whatever real time it takes to compute or draw) advances every robot's
// simulated clock by exactly the same fixed amount, so the simulation's
// behaviour does not depend on how fast it is able to render.
//
// CSimulation does not know anything about wall following or line following
// specifically - it only knows CRobot's interface, so the same class runs
// A1 (one robot) and A2 (two robots) alike. The caller builds whatever robots
// it wants and hands them over with AddRobot(); from that moment the
// simulation owns them and deletes them at the end of the run.
//-----------------------------------------------------------------------------

#ifndef CSIMULATION_H
#define CSIMULATION_H

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

        // Reads arMapFilename and builds the room described by it. Ask
        // IsReady() afterwards: a map that could not be read leaves the
        // simulation with nothing to run.
        CSimulation( const std::string& arMapFilename, int aUpdatesToRun );
        ~CSimulation();

        //---State---

        // True when the map file was read and there is a room to drive in.
        bool IsReady() const;

        //---Registration---

        // Takes ownership of apRobot: it will be deleted with the simulation.
        // Ignores a null pointer rather than storing one.
        void AddRobot( CRobot* apRobot );

        //---What a robot needs to be built against---
        const CRoom& GetRoom() const;
        const CPose& GetStartPose() const;

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

        //---The window---
        CRender mRender;

        //---The map file's contents, and the room built from them. The room
        //---is allocated once the file has been read, which is why it is a
        //---pointer: a member object would have to be built before the
        //---constructor body has had a chance to read anything.
        CLoopReader mLoop;
        CRoom* mpRoom;

        //---The robots being simulated, owned by this simulation---
        std::vector<CRobot*> mpRobots;

        //---How long to run for---
        const int mUpdatesToRun;
        int mUpdatesCompleted;

        //---Whether the map file was read successfully---
        bool mIsReady;
};

#endif
