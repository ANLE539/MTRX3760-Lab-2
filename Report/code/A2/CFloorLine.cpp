//-----------------------------------------------------------------------------
// CFloorLine.cpp
//-----------------------------------------------------------------------------

#include "CFloorLine.h"

const Color CFloorLine::kLineColor = YELLOW;

//-----------------------------------------------------------------------------
CFloorLine::CFloorLine( const CLoopReader& arLoop, float aWidth )
    :
        mLine( arLoop.GetVertices() ),
        mHalfWidth( aWidth * 0.5f )
{
}


//-----------------------------------------------------------------------------
bool CFloorLine::IsPointOnLine( Vec2D aPoint ) const
{
    return mLine.DistanceToLoop( aPoint ) <= mHalfWidth;
}


//-----------------------------------------------------------------------------
// Drawn at its real painted width rather than as a thin outline, so what is
// on screen matches what the sensors are testing against.
//-----------------------------------------------------------------------------
void CFloorLine::Draw( CRender& arRender ) const
{
    mLine.Draw( arRender, kLineColor, mHalfWidth * 2.0f );
}
