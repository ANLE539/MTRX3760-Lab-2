//-----------------------------------------------------------------------------
// CFloorLine.h
//
// The line marked on the floor. Same idea as CRoom but for a line instead of
// a wall: wraps a CSegmentLoop and adds the one thing a line sensor cares
// about - is this point on the line or not.
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
        //---Ctor---

        // aWidth is the painted width of the line, so a point counts as being
        // on it while it lies within half that distance of the centreline.
        CFloorLine( const CLoopReader& arLoop, float aWidth );

        //---Sensing---
        bool IsPointOnLine( Vec2D aPoint ) const;

        //---Drawing---
        void Draw( CRender& arRender ) const;

    private:
        //---The colour the line is painted in---
        static const Color kLineColor;

        //---The line geometry---
        CSegmentLoop mLine;

        //---Half the painted width: the distance a sensor can sit from the
        //---centreline and still report line---
        const float mHalfWidth;
};

#endif
