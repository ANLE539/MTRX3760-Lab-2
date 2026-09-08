//
// CSegmentLoop.cpp
//

#include "CSegmentLoop.h"
#include "CVecMath.h"

#include <cmath>
#include <limits>

//
CSegmentLoop::CSegmentLoop( const std::vector<Vec2D>& arVertices )
{
    // Build one segment between every consecutive pair of vertices, with the
    // last vertex joining back to the first to close the loop.
    std::size_t Count = arVertices.size();
    for( std::size_t i = 0; i < Count; ++i )
    {
        Vec2D Start = arVertices[i];
        Vec2D End = arVertices[ (i + 1) % Count ];
        mSegments.push_back( CSegment{ Start, End } );
    }
}


//-----------------------------------------------------------------------------
float CSegmentLoop::RayCast( Vec2D aOrigin, float aAngleRadians, float aMaxRange ) const
{
    Vec2D Direction = CVecMath::FromAngle( aAngleRadians );
    float NearestDistance = aMaxRange;

    for( const CSegment& arSeg : mSegments )
    {
        // Intersect the ray (aOrigin + t*Direction, t >= 0) with the segment
        // (mStart + u*Edge, 0 <= u <= 1) by solving the resulting 2x2 linear
        // system for t and u.
        Vec2D Edge = CVecMath::Subtract( arSeg.mEnd, arSeg.mStart );
        float Denominator = Direction.x * Edge.y - Direction.y * Edge.x;

        if( std::fabs( Denominator ) > 1.0e-6f )
        {
            Vec2D OriginToStart = CVecMath::Subtract( arSeg.mStart, aOrigin );
            float T = (OriginToStart.x * Edge.y - OriginToStart.y * Edge.x) / Denominator;
            float U = (OriginToStart.x * Direction.y - OriginToStart.y * Direction.x) / Denominator;

            bool OnRay = (T >= 0.0f) && (T <= NearestDistance);
            bool OnSegment = (U >= 0.0f) && (U <= 1.0f);
            if( OnRay && OnSegment )
            {
                NearestDistance = T;
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
    Vec2D Best = mSegments.empty() ? aPoint : mSegments[0].mStart;
    float BestDistanceSquared = std::numeric_limits<float>::max();

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
void CSegmentLoop::Draw( CRender& arRender, Color aColor ) const
{
    const float Thickness = 2.0f;
    for( const CSegment& arSeg : mSegments )
    {
        arRender.DrawLine( arSeg.mStart, arSeg.mEnd, Thickness, aColor );
    }
}
