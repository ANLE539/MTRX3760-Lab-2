//-----------------------------------------------------------------------------
// CWheel.cpp
//-----------------------------------------------------------------------------

#include "CWheel.h"

// Comfortably above anything either controller commands, so it never shapes
// normal driving - it is here so that a wheel can never be asked for a speed
// the motor could not physically reach.
const float CWheel::kMaxSpeed = 120.0f;

//-----------------------------------------------------------------------------
CWheel::CWheel()
    :
        mSpeed( 0.0f )
{
}


//-----------------------------------------------------------------------------
void CWheel::SetSpeed( float aSpeed )
{
    float ClampedSpeed = aSpeed;

    if( ClampedSpeed > kMaxSpeed )
    {
        ClampedSpeed = kMaxSpeed;
    }
    else if( ClampedSpeed < -kMaxSpeed )
    {
        ClampedSpeed = -kMaxSpeed;
    }

    mSpeed = ClampedSpeed;
}


//-----------------------------------------------------------------------------
float CWheel::DistanceIn( float aTimeStep ) const
{
    return mSpeed * aTimeStep;
}
