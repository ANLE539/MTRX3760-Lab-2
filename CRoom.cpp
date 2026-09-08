//-----------------------------------------------------------------------------
// CRoom.cpp
//-----------------------------------------------------------------------------

#include "CRoom.h"
#include "CVecMath.h"

namespace
{
    const Color kWallColor = RAYWHITE;
}

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
Vec2D CRoom::ResolveCollision( Vec2D aCentre, float aRadius ) const
{
    Vec2D NearestWallPoint = mWalls.ClosestPointOnLoop( aCentre );
    Vec2D OutwardDirection = CVecMath::Subtract( aCentre, NearestWallPoint );

    float Distance = CVecMath::Length( OutwardDirection );
    Vec2D Result = aCentre;
    if( Distance > 1.0e-6f )
    {
        Vec2D UnitOutward = CVecMath::Scale( OutwardDirection, 1.0f / Distance );
        Result = CVecMath::Add( NearestWallPoint, CVecMath::Scale( UnitOutward, aRadius ) );
    }

    return Result;
}


//-----------------------------------------------------------------------------
void CRoom::Draw( CRender& arRender ) const
{
    mWalls.Draw( arRender, kWallColor );
}
