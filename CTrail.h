//-----------------------------------------------------------------------------
// CTrail.h
//
// Records the sequence of positions a robot has visited, and draws it as a
// connected line so the whole run's path stays on screen.
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
        void AddPoint( Vec2D aPoint );

        //---Drawing---
        void Draw( CRender& arRender, Color aColor ) const;

    private:
        //---Consts---
        static const float kMinSpacing;   // skip points closer than this together

        //---The recorded path---
        std::vector<Vec2D> mPoints;
};

#endif
