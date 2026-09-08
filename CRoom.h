//-----------------------------------------------------------------------------
// CRoom.h
//
// The walls of the room a robot drives around in. Wraps a CSegmentLoop (built
// from the vertices a CLoopReader read) and gives it wall-specific meaning:
// something a range sensor can be reflected off, and something a robot's body
// can collide with.
//-----------------------------------------------------------------------------

#ifndef CROOM_H
#define CROOM_H

#include "CLoopReader.h"
#include "CRender.h"
#include "CSegmentLoop.h"

//-----------------------------------------------------------------------------
class CRoom
{
    public:
        //---Ctor---
        explicit CRoom( const CLoopReader& arLoop );

        //---Sensing---

        // Distance from aOrigin to the nearest wall along aAngleRadians, or
        // aMaxRange if no wall is within range.
        float SenseDistance( Vec2D aOrigin, float aAngleRadians, float aMaxRange ) const;

        //---Collision---

        // True if a disc of radius aRadius centred on aCentre overlaps a wall.
        bool IsColliding( Vec2D aCentre, float aRadius ) const;

        // A position for a colliding disc to be moved to so it just touches
        // the wall instead of overlapping it.
        Vec2D ResolveCollision( Vec2D aCentre, float aRadius ) const;

        //---Drawing---
        void Draw( CRender& arRender ) const;

    private:
        //---The wall geometry---
        CSegmentLoop mWalls;
};

#endif
