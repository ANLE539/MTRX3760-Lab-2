//-----------------------------------------------------------------------------
// CFloorLine.cpp
//-----------------------------------------------------------------------------

#include "CFloorLine.h"

namespace
{
    const Color kLineColor = YELLOW;
}

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
void CFloorLine::Draw( CRender& arRender ) const
{
    // Draw it at its real width (not the thin 2px default) so it actually
    // looks like a line on the floor rather than a wire outline.
    mLine.Draw( arRender, kLineColor, mHalfWidth * 2.0f );
}
