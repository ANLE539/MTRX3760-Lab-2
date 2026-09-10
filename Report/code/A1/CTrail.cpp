//-----------------------------------------------------------------------------
// CTrail.cpp
//-----------------------------------------------------------------------------

#include "CTrail.h"
#include "CVecMath.h"

const float CTrail::kMinSpacing = 1.0f;
const float CTrail::kThickness = 1.5f;

//-----------------------------------------------------------------------------
CTrail::CTrail()
{
}


//-----------------------------------------------------------------------------
// Skips points that are barely different from the last one recorded, so a
// slow-moving or stationary robot does not fill the trail with thousands of
// overlapping points.
//-----------------------------------------------------------------------------
void CTrail::AddPoint( Vec2D aPoint )
{
    bool ShouldAdd = mPoints.empty()
        || ( CVecMath::DistanceBetween( mPoints.back(), aPoint ) >= kMinSpacing );

    if( ShouldAdd )
    {
        mPoints.push_back( aPoint );
    }
}


//-----------------------------------------------------------------------------
void CTrail::Draw( CRender& arRender, Color aColor ) const
{
    for( std::size_t i = 1; i < mPoints.size(); ++i )
    {
        arRender.DrawLine( mPoints[i - 1], mPoints[i], kThickness, aColor );
    }
}
