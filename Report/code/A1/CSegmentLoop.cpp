//-----------------------------------------------------------------------------
// CSegmentLoop.cpp
//-----------------------------------------------------------------------------

#include "CSegmentLoop.h"
#include "CVecMath.h"

#include <cmath>

const float CSegmentLoop::kParallelTolerance = 0.000001f;
const float CSegmentLoop::kVeryLargeDistanceSquared = 1000000000000.0f;

//-----------------------------------------------------------------------------
// Builds one segment between every consecutive pair of vertices, with the last
// vertex joining back to the first to close the loop.
//-----------------------------------------------------------------------------
CSegmentLoop::CSegmentLoop( const std::vector<Vec2D>& arVertices )
{
    std::size_t Count = arVertices.size();

    for( std::size_t i = 0; i < Count; ++i )
    {
        Vec2D Start = arVertices[i];
        Vec2D End = arVertices[ ( i + 1 ) % Count ];

        mSegments.push_back( CSegment{ Start, End } );
    }
}


//-----------------------------------------------------------------------------
// Intersects the ray (aOrigin + t*Direction, t >= 0) with each segment
// (mStart + u*Edge, 0 <= u <= 1) by solving the resulting 2x2 linear system
// for t and u, and keeps the nearest crossing found.
//-----------------------------------------------------------------------------
float CSegmentLoop::RayCast( Vec2D aOrigin, float aAngleRadians, float aMaxRange ) const
{
    Vec2D Direction = CVecMath::FromAngle( aAngleRadians );
    float NearestDistance = aMaxRange;

    for( const CSegment& arSeg : mSegments )
    {
        Vec2D Edge = CVecMath::Subtract( arSeg.mEnd, arSeg.mStart );
        float Denominator = ( Direction.x * Edge.y ) - ( Direction.y * Edge.x );

        if( std::fabs( Denominator ) > kParallelTolerance )
        {
            Vec2D OriginToStart = CVecMath::Subtract( arSeg.mStart, aOrigin );
            float DistanceAlongRay = ( ( OriginToStart.x * Edge.y ) - ( OriginToStart.y * Edge.x ) ) / Denominator;
            float FractionAlongEdge = ( ( OriginToStart.x * Direction.y ) - ( OriginToStart.y * Direction.x ) ) / Denominator;

            bool IsNearestSoFar = ( DistanceAlongRay >= 0.0f ) && ( DistanceAlongRay <= NearestDistance );
            bool IsBetweenTheEnds = ( FractionAlongEdge >= 0.0f ) && ( FractionAlongEdge <= 1.0f );

            if( IsNearestSoFar && IsBetweenTheEnds )
            {
                NearestDistance = DistanceAlongRay;
            }
        }
    }

    return NearestDistance;
}


//-----------------------------------------------------------------------------
float CSegmentLoop::DistanceToLoop( Vec2D aPoint ) const
{
    return CVecMath::DistanceBetween( aPoint, ClosestPointOnLoop( aPoint ) );
}


//-----------------------------------------------------------------------------
Vec2D CSegmentLoop::ClosestPointOnLoop( Vec2D aPoint ) const
{
    Vec2D Best = aPoint;
    float BestDistanceSquared = kVeryLargeDistanceSquared;

    for( const CSegment& arSeg : mSegments )
    {
        Vec2D Candidate = CVecMath::ClosestPointOnSegment( aPoint, arSeg.mStart, arSeg.mEnd );
        Vec2D Delta = CVecMath::Subtract( Candidate, aPoint );
        float DistanceSquared = CVecMath::Dot( Delta, Delta );

        if( DistanceSquared < BestDistanceSquared )
        {
            BestDistanceSquared = DistanceSquared;
            Best = Candidate;
        }
    }

    return Best;
}


//-----------------------------------------------------------------------------
void CSegmentLoop::Draw( CRender& arRender, Color aColor, float aThickness ) const
{
    for( const CSegment& arSeg : mSegments )
    {
        arRender.DrawLine( arSeg.mStart, arSeg.mEnd, aThickness, aColor );
    }
}
