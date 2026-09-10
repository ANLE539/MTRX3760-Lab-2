//-----------------------------------------------------------------------------
// CVecMath.h
//
// A small collection of vector operations on Vec2D (defined in CRender.h).
// Kept as static methods on a class, rather than loose free functions, so
// that every function lives inside something rather than floating at file
// scope. Nothing here holds state: the class is a named home for the maths,
// not something to create an object of.
//-----------------------------------------------------------------------------

#ifndef CVECMATH_H
#define CVECMATH_H

#include "CRender.h"   // for Vec2D

//-----------------------------------------------------------------------------
class CVecMath
{
    public:
        //---Arithmetic---
        static Vec2D Add( Vec2D aA, Vec2D aB );
        static Vec2D Subtract( Vec2D aA, Vec2D aB );
        static Vec2D Scale( Vec2D aV, float aScale );

        //---Products and lengths---
        static float Dot( Vec2D aA, Vec2D aB );
        static float Length( Vec2D aV );
        static float DistanceBetween( Vec2D aA, Vec2D aB );

        // A unit vector pointing along aAngleRadians, using the same
        // convention as CPose::mHeading: 0 is +x (right), and the angle grows
        // clockwise on screen (since y grows downward).
        static Vec2D FromAngle( float aAngleRadians );

        // The closest point to aPoint that lies on the segment aStart..aEnd,
        // measuring to an end point when the perpendicular foot falls outside
        // the segment. A zero-length segment reports its own position.
        static Vec2D ClosestPointOnSegment( Vec2D aPoint, Vec2D aStart, Vec2D aEnd );

    private:
        //---A segment shorter than this is treated as a single point, so
        //---dividing by its length can never produce a meaningless answer---
        static const float kMinLengthSquared;
};

#endif
