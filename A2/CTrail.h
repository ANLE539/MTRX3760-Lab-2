//-----------------------------------------------------------------------------
// CTrail.h
//
// Records the sequence of positions a robot has visited, and draws it as a
// connected line so the whole run's path stays on screen. The renderer clears
// the window every frame, so the trail has to be stored and redrawn rather
// than left behind on the screen.
//-----------------------------------------------------------------------------

#ifndef CTRAIL_H
#define CTRAIL_H

#include "CRender.h"

#include <vector>

//-----------------------------------------------------------------------------
class CTrail
{
    public:
        //---Ctor---
        CTrail();

        //---Recording---

        // Records aPoint, unless it sits almost on top of the last point
        // recorded.
        void AddPoint( Vec2D aPoint );

        //---Drawing---
        void Draw( CRender& arRender, Color aColor ) const;

    private:
        //---Consts---
        static const float kMinSpacing;    // skip points closer than this together
        static const float kThickness;     // how thick the trail is drawn

        //---The recorded path---
        std::vector<Vec2D> mPoints;
};

#endif
