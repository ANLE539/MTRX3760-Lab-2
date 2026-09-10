//-----------------------------------------------------------------------------
// CRoom.h
//
// The walls of the room a robot drives around in. Wraps a CSegmentLoop (built
// from the vertices a CLoopReader read) and gives it wall-specific meaning:
// something a range sensor's ray can meet, and something a robot's body can
// collide with.
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
        // the wall instead of overlapping it. A disc sitting exactly on the
        // wall has no direction to be pushed in, and is left where it is.
        Vec2D ResolveCollision( Vec2D aCentre, float aRadius ) const;

        //---Drawing---
        void Draw( CRender& arRender ) const;

    private:
        //---Consts---

        // Below this there is no usable direction to push a disc away from
        // the wall it is touching.
        static const float kMinPushDistance;

        // How the walls are drawn.
        static const Color kWallColor;
        static const float kWallThickness;

        //---The wall geometry---
        CSegmentLoop mWalls;
};

#endif
