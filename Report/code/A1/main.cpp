//-----------------------------------------------------------------------------
// main.cpp  -  A1: Wall Follower
//
// Loads the room from SimpleWalls.map, drives a robot around it keeping the
// wall on its right, and prints a collision-and-run summary at the end.
//
// BUILD (raylib installed via apt) - see the Makefile for the same command:
//     g++ -std=c++17 -Wall -Wextra main.cpp CRender.cpp CLoopReader.cpp
//     CSegmentLoop.cpp CRoom.cpp CTrail.cpp CDifferentialDrive.cpp CWheel.cpp
//     CRangeSensor.cpp CRobot.cpp CWallFollowerRobot.cpp CSimulation.cpp
//     -lraylib -o A1
//
// BUILD (raylib built from source into $HOME/raylib):
//     add -I$HOME/raylib/include -L$HOME/raylib/lib to the command above.
//
// RUN:
//     ./A1
//-----------------------------------------------------------------------------

#include "CSimulation.h"
#include "CWallFollowerRobot.h"

#include <iostream>

//-----------------------------------------------------------------------------
// The simulation owns the window, the room and the robot: main builds the one
// robot this assignment calls for, hands it over, and reads the results back
// once the run has finished.
//-----------------------------------------------------------------------------
int main()
{
    const char* WallsMapFile = "SimpleWalls.map";

    // One lap of SimpleWalls.map takes a little under 1800 updates, so this
    // is long enough to finish the circuit and stop, rather than driving a
    // second lap over the top of the first one's trail.
    const int UpdatesToRun = 2000;

    int Result = 0;

    CSimulation Simulation( WallsMapFile, UpdatesToRun );

    if( !Simulation.IsReady() )
    {
        std::cout << "Could not read '" << WallsMapFile << "', stopping." << std::endl;
        Result = 1;
    }
    else
    {
        CWallFollowerRobot* pWallFollower =
            new CWallFollowerRobot( Simulation.GetStartPose(), Simulation.GetRoom() );

        Simulation.AddRobot( pWallFollower );
        Simulation.Run();

        std::cout << std::endl;
        std::cout << "Run summary" << std::endl;
        std::cout << "Updates completed : " << Simulation.GetUpdatesCompleted() << std::endl;
        std::cout << "Total collisions  : " << pWallFollower->GetCollisionCount() << std::endl;
    }

    return Result;
}
