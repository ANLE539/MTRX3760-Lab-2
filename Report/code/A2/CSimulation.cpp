//-----------------------------------------------------------------------------
// CSimulation.cpp
//-----------------------------------------------------------------------------

#include "CSimulation.h"

#include <cstddef>   // NULL

const float CSimulation::kFixedTimeStep = 0.02f;   // 50 simulated Hz, independent of render rate
const float CSimulation::kLineWidth = 5.0f;

//-----------------------------------------------------------------------------
// Room and line are built whether or not their files could be read: an unread
// file simply leaves one empty, so GetRoom() and GetFloorLine() always have
// something real to hand out and no caller can be given a reference to
// nothing. IsReady() is what says whether the world is worth driving in.
//-----------------------------------------------------------------------------
CSimulation::CSimulation( const std::string& arWallsMapFilename,
                          const std::string& arLineMapFilename,
                          int aUpdatesToRun )
    :
        mpRoom( NULL ),
        mpFloorLine( NULL ),
        mUpdatesToRun( aUpdatesToRun ),
        mUpdatesCompleted( 0 ),
        mIsReady( false )
{
    bool WallsRead = mWallsLoop.ReadFile( arWallsMapFilename );
    bool LineRead = mLineLoop.ReadFile( arLineMapFilename );

    mIsReady = WallsRead && LineRead;

    mpRoom = new CRoom( mWallsLoop );
    mpFloorLine = new CFloorLine( mLineLoop, kLineWidth );
}


//-----------------------------------------------------------------------------
CSimulation::~CSimulation()
{
    for( CRobot* pRobot : mpRobots )
    {
        delete pRobot;
    }

    delete mpFloorLine;
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
const CFloorLine& CSimulation::GetFloorLine() const
{
    return *mpFloorLine;
}


//-----------------------------------------------------------------------------
const CPose& CSimulation::GetWallStartPose() const
{
    return mWallsLoop.GetStartPose();
}


//-----------------------------------------------------------------------------
const CPose& CSimulation::GetLineStartPose() const
{
    return mLineLoop.GetStartPose();
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
// The floor line is drawn before the robots so their bodies and trails sit on
// top of it, the way they would if they were really driving over paint.
//-----------------------------------------------------------------------------
void CSimulation::DrawFrame()
{
    mRender.BeginDrawing();

    mpRoom->Draw( mRender );
    mpFloorLine->Draw( mRender );

    for( const CRobot* pRobot : mpRobots )
    {
        pRobot->Draw( mRender );
    }

    mRender.EndDrawing();
}
