//-----------------------------------------------------------------------------
// CFloorLine.h
//
// The line marked on the floor. Same idea as CRoom but for a line instead of
// a wall - wraps a CSegmentLoop and adds the one thing a line sensor cares
// about: is this point on the line or not.
//-----------------------------------------------------------------------------

#ifndef CFLOORLINE_H
#define CFLOORLINE_H

#include "CLoopReader.h"
#include "CRender.h"
#include "CSegmentLoop.h"

//-----------------------------------------------------------------------------
class CFloorLine
{
    public:
        CFloorLine( const CLoopReader& arLoop, float aWidth );

        bool IsPointOnLine( Vec2D aPoint ) const;

        void Draw( CRender& arRender ) const;

    private:
        CSegmentLoop mLine;
        const float mHalfWidth;
};

#endif
