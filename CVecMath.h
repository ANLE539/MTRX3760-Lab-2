//-----------------------------------------------------------------------------
// CVecMath.h
//
// A small collection of vector operations on Vec2D (defined in CRender.h).
// Kept as static methods on a class, rather than loose free functions, to
// keep every function embedded somewhere rather than floating at file scope.
//-----------------------------------------------------------------------------

#ifndef CVECMATH_H
#define CVECMATH_H

#include "CRender.h"

#include <cmath>

//-----------------------------------------------------------------------------
class CVecMath
{
    public:
        static Vec2D Add( Vec2D aA, Vec2D aB )
        {
            return Vec2D{ aA.x + aB.x, aA.y + aB.y };
        }

        static Vec2D Subtract( Vec2D aA, Vec2D aB )
        {
            return Vec2D{ aA.x - aB.x, aA.y - aB.y };
        }

        static Vec2D Scale( Vec2D aV, float aScale )
        {
            return Vec2D{ aV.x * aScale, aV.y * aScale };
        }

        static float Dot( Vec2D aA, Vec2D aB )
        {
            return aA.x * aB.x + aA.y * aB.y;
        }

        static float Length( Vec2D aV )
        {
            return std::sqrt( aV.x * aV.x + aV.y * aV.y );
        }

        static float DistanceBetween( Vec2D aA, Vec2D aB )
        {
            return Length( Subtract( aB, aA ) );
        }

        // A unit vector pointing along aAngleRadians, using the same
        // convention as CPose::mHeading: 0 is +x (right), the angle grows
        // clockwise on screen (since y grows downward).
        static Vec2D FromAngle( float aAngleRadians )
        {
            return Vec2D{ std::cos( aAngleRadians ), std::sin( aAngleRadians ) };
        }

        // The closest point to aPoint that lies on the segment aStart..aEnd.
        static Vec2D ClosestPointOnSegment( Vec2D aPoint, Vec2D aStart, Vec2D aEnd )
        {
            Vec2D Edge = Subtract( aEnd, aStart );
            float EdgeLengthSquared = Dot( Edge, Edge );

            Vec2D Result;
            if( EdgeLengthSquared < 1.0e-9f )
            {
                // Degenerate (zero-length) segment: both ends are the same point.
                Result = aStart;
            }
            else
            {
                float T = Dot( Subtract( aPoint, aStart ), Edge ) / EdgeLengthSquared;
                if( T < 0.0f )
                {
                    T = 0.0f;
                }
                else if( T > 1.0f )
                {
                    T = 1.0f;
                }
                Result = Add( aStart, Scale( Edge, T ) );
            }
            return Result;
        }
};

#endif
