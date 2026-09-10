//-----------------------------------------------------------------------------
// main.cpp  -  A2: Line Follower (built on top of A1)
//
// The same room as A1, but now with a second robot doing its own thing on the
// floor line from SimpleLine.map. The two robots do not know about each other
// - they just both get updated and drawn every frame.
//
// BUILD (raylib installed via apt) - see build.sh for the same command:
//     g++ -std=c++17 -Wall -Wextra main.cpp CRender.cpp CLoopReader.cpp
//     CSegmentLoop.cpp CVecMath.cpp CRoom.cpp CFloorLine.cpp CTrail.cpp
//     CDifferentialDrive.cpp CWheel.cpp CRangeSensor.cpp CLineSensor.cpp
//     CRobot.cpp CWallFollowerRobot.cpp CLineFollowerRobot.cpp CSimulation.cpp
//     -lraylib -o A2
//
// BUILD (raylib built from source into $HOME/raylib):
//     add -I$HOME/raylib/include -L$HOME/raylib/lib to the command above.
//
// RUN:
//     ./A2
//-----------------------------------------------------------------------------

#include "CLineFollowerRobot.h"
#include "CSimulation.h"
#include "CWallFollowerRobot.h"

#include <iostream>

//-----------------------------------------------------------------------------
// The simulation owns the window, the room, the floor line and both robots:
// main builds the two robots this assignment calls for, hands them over, and
// reads the results back once the run has finished.
//-----------------------------------------------------------------------------
int main()
{
    const char* WallsMapFile = "SimpleWalls.map";
    const char* LineMapFile = "SimpleLine.map";

    // The line follower is the slower of the two: it needs a little over 3300
    // updates to get all the way round its loop, by which time the wall
    // follower has long since finished its own.
    const int UpdatesToRun = 3500;

    int Result = 0;

    CSimulation Simulation( WallsMapFile, LineMapFile, UpdatesToRun );

    if( !Simulation.IsReady() )
    {
        std::cout << "Could not read the map files, stopping." << std::endl;
        Result = 1;
    }
    else
    {
        CWallFollowerRobot* pWallFollower =
            new CWallFollowerRobot( Simulation.GetWallStartPose(), Simulation.GetRoom() );

        CLineFollowerRobot* pLineFollower =
            new CLineFollowerRobot( Simulation.GetLineStartPose(), Simulation.GetFloorLine() );

        Simulation.AddRobot( pWallFollower );
        Simulation.AddRobot( pLineFollower );
        Simulation.Run();

        std::cout << std::endl;
        std::cout << "Run summary" << std::endl;
        std::cout << "Updates completed        : " << Simulation.GetUpdatesCompleted() << std::endl;
        std::cout << "Wall follower collisions : " << pWallFollower->GetCollisionCount() << std::endl;
    }

    return Result;
}
