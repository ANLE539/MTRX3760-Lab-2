//-----------------------------------------------------------------------------
// main.cpp  -  A1: Wall Follower
//
// Loads the room from SimpleWalls.map, drives a robot around it keeping the
// wall on its right, and prints a collision-and-run summary at the end.
//
// BUILD (raylib installed via apt) - see build.sh for the same command:
//     g++ -std=c++17 -Wall -Wextra main.cpp CRender.cpp CLoopReader.cpp
//     CSegmentLoop.cpp CRoom.cpp CTrail.cpp CDifferentialDrive.cpp
//     CRangeSensor.cpp CRobot.cpp CWallFollowerRobot.cpp CSimulation.cpp
//     -lraylib -o A1
//
// BUILD (raylib built from source into $HOME/raylib):
//     add -I$HOME/raylib/include -L$HOME/raylib/lib to the command above.
//
// RUN:
//     ./A1
//-----------------------------------------------------------------------------

#include "CLoopReader.h"
#include "CRender.h"
#include "CRoom.h"
#include "CSimulation.h"
#include "CWallFollowerRobot.h"

#include <iostream>

namespace
{
    const char* kWallsMapFile = "SimpleWalls.map";
    const int kUpdatesToRun = 4000;   // 4000 * 0.02s = 80 simulated seconds
}

//-----------------------------------------------------------------------------
int main()
{
    CLoopReader WallsLoop;
    if( !WallsLoop.ReadFile( kWallsMapFile ) )
    {
        std::cout << "Could not read '" << kWallsMapFile << "', stopping." << std::endl;
        return 1;
    }

    CRoom Room( WallsLoop );
    CWallFollowerRobot WallFollower( WallsLoop.GetStartPose(), Room );

    CRender Render;
    CSimulation Simulation( Render, Room, kUpdatesToRun );
    Simulation.AddRobot( WallFollower );
    Simulation.Run();

    std::cout << std::endl;
    std::cout << "Run summary" << std::endl;
    std::cout << "Updates completed : " << Simulation.GetUpdatesCompleted() << std::endl;
    std::cout << "Total collisions  : " << WallFollower.GetCollisionCount() << std::endl;

    return 0;
}
