//-----------------------------------------------------------------------------
// CSimulation.cpp
//-----------------------------------------------------------------------------

#include "CSimulation.h"

const float CSimulation::kFixedTimeStep = 0.02f;   // 50 simulated Hz, independent of render rate

//-----------------------------------------------------------------------------
CSimulation::CSimulation( CRender& arRender, const CRoom& arRoom, int aUpdatesToRun )
    :
        mrRender( arRender ),
        mrRoom( arRoom ),
        mpFloorLine( nullptr ),
        mUpdatesToRun( aUpdatesToRun ),
        mUpdatesCompleted( 0 )
{
}


//-----------------------------------------------------------------------------
void CSimulation::AddRobot( CRobot& arRobot )
{
    mpRobots.push_back( &arRobot );
}


//-----------------------------------------------------------------------------
void CSimulation::SetFloorLine( const CFloorLine* apLine )
{
    mpFloorLine = apLine;
}


//-----------------------------------------------------------------------------
void CSimulation::Run()
{
    while( !mrRender.WindowShouldClose() )
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

    mrRender.CloseWindow();
}


//-----------------------------------------------------------------------------
void CSimulation::DrawFrame() const
{
    mrRender.BeginDrawing();

    mrRoom.Draw( mrRender );
    if( mpFloorLine != nullptr )
    {
        mpFloorLine->Draw( mrRender );
    }
    for( const CRobot* pRobot : mpRobots )
    {
        pRobot->Draw( mrRender );
    }

    mrRender.EndDrawing();
}


//-----------------------------------------------------------------------------
int CSimulation::GetUpdatesCompleted() const
{
    return mUpdatesCompleted;
}
