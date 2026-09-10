//-----------------------------------------------------------------------------
// CRoom.cpp
//-----------------------------------------------------------------------------

#include "CRoom.h"
#include "CVecMath.h"

const float CRoom::kMinPushDistance = 0.000001f;
const Color CRoom::kWallColor = RAYWHITE;
const float CRoom::kWallThickness = 2.0f;

//-----------------------------------------------------------------------------
CRoom::CRoom( const CLoopReader& arLoop )
    :
        mWalls( arLoop.GetVertices() )
{
}


//-----------------------------------------------------------------------------
float CRoom::SenseDistance( Vec2D aOrigin, float aAngleRadians, float aMaxRange ) const
{
    return mWalls.RayCast( aOrigin, aAngleRadians, aMaxRange );
}


//-----------------------------------------------------------------------------
bool CRoom::IsColliding( Vec2D aCentre, float aRadius ) const
{
    return mWalls.DistanceToLoop( aCentre ) < aRadius;
}


//-----------------------------------------------------------------------------
// Finds the wall point the disc is overlapping, then places the disc back
// along the line joining the two so that it just touches the wall.
//-----------------------------------------------------------------------------
Vec2D CRoom::ResolveCollision( Vec2D aCentre, float aRadius ) const
{
    Vec2D NearestWallPoint = mWalls.ClosestPointOnLoop( aCentre );
    Vec2D OutwardDirection = CVecMath::Subtract( aCentre, NearestWallPoint );

    float Distance = CVecMath::Length( OutwardDirection );
    Vec2D Result = aCentre;

    if( Distance > kMinPushDistance )
    {
        Vec2D UnitOutward = CVecMath::Scale( OutwardDirection, 1.0f / Distance );
        Result = CVecMath::Add( NearestWallPoint, CVecMath::Scale( UnitOutward, aRadius ) );
    }

    return Result;
}


//-----------------------------------------------------------------------------
void CRoom::Draw( CRender& arRender ) const
{
    mWalls.Draw( arRender, kWallColor, kWallThickness );
}
