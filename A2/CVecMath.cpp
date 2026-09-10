//-----------------------------------------------------------------------------
// CVecMath.cpp
//-----------------------------------------------------------------------------

#include "CVecMath.h"

#include <cmath>

const float CVecMath::kMinLengthSquared = 0.000000001f;

//-----------------------------------------------------------------------------
Vec2D CVecMath::Add( Vec2D aA, Vec2D aB )
{
    Vec2D Result = { aA.x + aB.x, aA.y + aB.y };

    return Result;
}


//-----------------------------------------------------------------------------
Vec2D CVecMath::Subtract( Vec2D aA, Vec2D aB )
{
    Vec2D Result = { aA.x - aB.x, aA.y - aB.y };

    return Result;
}


//-----------------------------------------------------------------------------
Vec2D CVecMath::Scale( Vec2D aV, float aScale )
{
    Vec2D Result = { aV.x * aScale, aV.y * aScale };

    return Result;
}


//-----------------------------------------------------------------------------
float CVecMath::Dot( Vec2D aA, Vec2D aB )
{
    return ( aA.x * aB.x ) + ( aA.y * aB.y );
}


//-----------------------------------------------------------------------------
float CVecMath::Length( Vec2D aV )
{
    return std::sqrt( Dot( aV, aV ) );
}


//-----------------------------------------------------------------------------
float CVecMath::DistanceBetween( Vec2D aA, Vec2D aB )
{
    return Length( Subtract( aB, aA ) );
}


//-----------------------------------------------------------------------------
Vec2D CVecMath::FromAngle( float aAngleRadians )
{
    Vec2D Result = { std::cos( aAngleRadians ), std::sin( aAngleRadians ) };

    return Result;
}


//-----------------------------------------------------------------------------
// Projects aPoint onto the infinite line through the two ends, then pulls the
// projection back onto the segment itself. That last step is what makes a
// corner behave like a corner: a point beyond an end measures to the end, not
// to empty space past it.
//-----------------------------------------------------------------------------
Vec2D CVecMath::ClosestPointOnSegment( Vec2D aPoint, Vec2D aStart, Vec2D aEnd )
{
    Vec2D Edge = Subtract( aEnd, aStart );
    float EdgeLengthSquared = Dot( Edge, Edge );

    Vec2D Result = aStart;

    if( EdgeLengthSquared > kMinLengthSquared )
    {
        float FractionAlongEdge = Dot( Subtract( aPoint, aStart ), Edge ) / EdgeLengthSquared;

        if( FractionAlongEdge < 0.0f )
        {
            FractionAlongEdge = 0.0f;
        }
        else if( FractionAlongEdge > 1.0f )
        {
            FractionAlongEdge = 1.0f;
        }

        Result = Add( aStart, Scale( Edge, FractionAlongEdge ) );
    }

    return Result;
}
