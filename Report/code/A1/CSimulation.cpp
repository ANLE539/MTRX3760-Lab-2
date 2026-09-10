//-----------------------------------------------------------------------------
// CSimulation.cpp
//-----------------------------------------------------------------------------

#include "CSimulation.h"

#include <cstddef>   // NULL

const float CSimulation::kFixedTimeStep = 0.02f;   // 50 simulated Hz, independent of render rate

//-----------------------------------------------------------------------------
// The room is built whether or not the file could be read: an unread file
// simply leaves it empty, so GetRoom() always has something real to hand out
// and no caller can be given a reference to nothing. IsReady() is what says
// whether the room is worth driving in.
//-----------------------------------------------------------------------------
CSimulation::CSimulation( const std::string& arMapFilename, int aUpdatesToRun )
    :
        mpRoom( NULL ),
        mUpdatesToRun( aUpdatesToRun ),
        mUpdatesCompleted( 0 ),
        mIsReady( false )
{
    mIsReady = mLoop.ReadFile( arMapFilename );
    mpRoom = new CRoom( mLoop );
}


//-----------------------------------------------------------------------------
CSimulation::~CSimulation()
{
    for( CRobot* pRobot : mpRobots )
    {
        delete pRobot;
    }

    delete mpRoom;
}


//-----------------------------------------------------------------------------
bool CSimulation::IsReady() const
{
    return mIsReady;
}


//-----------------------------------------------------------------------------
void CSimulation::AddRobot( CRobot* apRobot )
{
    if( apRobot != NULL )
    {
        mpRobots.push_back( apRobot );
    }
}


//-----------------------------------------------------------------------------
const CRoom& CSimulation::GetRoom() const
{
    return *mpRoom;
}


//-----------------------------------------------------------------------------
const CPose& CSimulation::GetStartPose() const
{
    return mLoop.GetStartPose();
}


//-----------------------------------------------------------------------------
void CSimulation::Run()
{
    while( mIsReady && !mRender.WindowShouldClose() )
    {
        // Advance every robot by one fixed simulated timestep, but only
        // until the run's target number of updates has been reached - after
        // that, the window stays open showing the finished trails until the
        // person closes it.
        if( mUpdatesCompleted < mUpdatesToRun )
        {
            for( CRobot* pRobot : mpRobots )
            {
                pRobot->Update( kFixedTimeStep );
            }
            ++mUpdatesCompleted;
        }

        DrawFrame();
    }

    mRender.CloseWindow();
}


//-----------------------------------------------------------------------------
int CSimulation::GetUpdatesCompleted() const
{
    return mUpdatesCompleted;
}


//-----------------------------------------------------------------------------
void CSimulation::DrawFrame()
{
    mRender.BeginDrawing();

    mpRoom->Draw( mRender );
    for( const CRobot* pRobot : mpRobots )
    {
        pRobot->Draw( mRender );
    }

    mRender.EndDrawing();
}
