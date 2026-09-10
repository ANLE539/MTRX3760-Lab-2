//-----------------------------------------------------------------------------
// CWheel.h
//
// One of the robot's two wheels. A wheel is commanded a speed and reports how
// far it rolls in a given slice of time; it knows nothing about the other
// wheel, about steering, or about where the robot is.
//
// The wheel, not its caller, is what keeps a commanded speed inside what the
// motor could actually deliver, so no controller can ask for a speed the
// hardware does not have.
//-----------------------------------------------------------------------------

#ifndef CWHEEL_H
#define CWHEEL_H

//-----------------------------------------------------------------------------
class CWheel
{
    public:
        //---Ctor---
        CWheel();

        //---Control---

        // Commands this wheel to turn at aSpeed units of ground per second,
        // forwards when positive and backwards when negative. A speed beyond
        // what the motor can deliver is reduced to the motor's limit rather
        // than refused.
        void SetSpeed( float aSpeed );

        //---Motion---

        // How far this wheel rolls in aTimeStep seconds at its current
        // commanded speed. Negative when the wheel is running backwards.
        float DistanceIn( float aTimeStep ) const;

    private:
        //---The fastest this motor can turn the wheel, in units per second---
        static const float kMaxSpeed;

        //---Currently commanded speed, in units of ground per second---
        float mSpeed;
};

#endif
