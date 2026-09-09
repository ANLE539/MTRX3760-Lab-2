//-----------------------------------------------------------------------------
// main.cpp  -  A2: Line Follower (built on top of A1)
//
// Same room as A1, but now with a second robot doing its own thing on the
// floor line from SimpleLine.map. The two robots don't know about each
// other - they just both get updated and drawn every frame.
//
// BUILD (raylib installed via apt) - add -I/-L for a from-source install:
//     g++ -std=c++17 -Wall -Wextra main.cpp CRender.cpp CLoopReader.cpp
//     CSegmentLoop.cpp CRoom.cpp CFloorLine.cpp CTrail.cpp
//     CDifferentialDrive.cpp CRangeSensor.cpp CLineSensor.cpp CRobot.cpp
//     CWallFollowerRobot.cpp CLineFollowerRobot.cpp CSimulation.cpp
//     -lraylib -o A2
//
// RUN:
//     ./A2
//-----------------------------------------------------------------------------

#include "CFloorLine.h"
#include "CLineFollowerRobot.h"
#include "CLoopReader.h"
#include "CRender.h"
#include "CRoom.h"
#include "CSimulation.h"
#include "CWallFollowerRobot.h"

#include <iostream>

namespace
{
    const char* kWallsMapFile = "SimpleWalls.map";
    const char* kLineMapFile = "SimpleLine.map";
    const float kLineWidth = 5.0f;
    const int kUpdatesToRun = 6000;
}

//-----------------------------------------------------------------------------
int main()
{
    CLoopReader WallsLoop;
    CLoopReader LineLoop;
    if( !WallsLoop.ReadFile( kWallsMapFile ) || !LineLoop.ReadFile( kLineMapFile ) )
    {
        std::cout << "Couldn't read the map files, stopping." << std::endl;
        return 1;
    }

    CRoom Room( WallsLoop );
    CFloorLine Line( LineLoop, kLineWidth );

    CWallFollowerRobot WallFollower( WallsLoop.GetStartPose(), Room );
    CLineFollowerRobot LineFollower( LineLoop.GetStartPose(), Line );

    CRender Render;
    CSimulation Simulation( Render, Room, kUpdatesToRun );
    Simulation.AddRobot( WallFollower );
    Simulation.AddRobot( LineFollower );
    Simulation.SetFloorLine( &Line );
    Simulation.Run();

    std::cout << std::endl;
    std::cout << "Run summary " << std::endl;
    std::cout << "Updates completed        : " << Simulation.GetUpdatesCompleted() << std::endl;
    std::cout << "Wall follower collisions : " << WallFollower.GetCollisionCount() << std::endl;

    return 0;
}
