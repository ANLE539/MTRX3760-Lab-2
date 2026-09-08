//-----------------------------------------------------------------------------
// CSegmentLoop.h
//
// A closed loop of straight segments, built from the vertex list a
// CLoopReader supplies (the last vertex is understood to join back to the
// first). This class knows nothing about robots, rooms, walls or lines: it
// answers two purely geometric questions -
//
//   RayCast          - how far along a ray is the first segment it meets?
//   DistanceToLoop    - how far is a point from the nearest segment?
//
// CRoom and CFloorLine each wrap one of these to give the segments their
// domain meaning (a wall to bump into, a line to sense).
//-----------------------------------------------------------------------------

#ifndef CSEGMENTLOOP_H
#define CSEGMENTLOOP_H

#include "CRender.h"

#include <vector>

//-----------------------------------------------------------------------------
class CSegmentLoop
{
    public:
        //---Ctor---
        explicit CSegmentLoop( const std::vector<Vec2D>& arVertices );

        //---Queries---

        // Casts a ray from aOrigin along aAngleRadians (same convention as
        // CPose::mHeading) and returns the distance to the nearest segment it
        // crosses, or aMaxRange if it meets nothing within that range.
        float RayCast( Vec2D aOrigin, float aAngleRadians, float aMaxRange ) const;

        // The distance from aPoint to the nearest point on any segment of the
        // loop.
        float DistanceToLoop( Vec2D aPoint ) const;

        // The point on the loop closest to aPoint (the point DistanceToLoop
        // measures to). Used to work out which way to push a robot back out
        // after a collision.
        Vec2D ClosestPointOnLoop( Vec2D aPoint ) const;

        //---Drawing---
        void Draw( CRender& arRender, Color aColor ) const;

    private:
        //---One wall/line segment---
        struct CSegment
        {
            Vec2D mStart;
            Vec2D mEnd;
        };

        //---The loop, as a set of segments---
        std::vector<CSegment> mSegments;
};

#endif
