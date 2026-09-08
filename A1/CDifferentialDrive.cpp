//-----------------------------------------------------------------------------
// CDifferentialDrive.cpp
//-----------------------------------------------------------------------------

#include "CDifferentialDrive.h"

#include <cmath>

namespace
{
    const float kTwoPi = 2.0f * float( M_PI );

    // Keep a heading in the range [0, 2*PI) so it does not grow without
    // bound over a long run.
    float NormaliseAngle( float aAngle )
    {
        float Result = std::fmod( aAngle, kTwoPi );
        if( Result < 0.0f )
        {
            Result += kTwoPi;
        }
        return Result;
    }
}

//-----------------------------------------------------------------------------
CDifferentialDrive::CDifferentialDrive( float aTrackWidth )
    :
        mTrackWidth( aTrackWidth )
{
}


//-----------------------------------------------------------------------------
CPose CDifferentialDrive::Step( const CPose& arPose, float aLeftWheelSpeed,
                                 float aRightWheelSpeed, float aTimeStep ) const
{
    float LinearSpeed = 0.5f * (aLeftWheelSpeed + aRightWheelSpeed);
    float AngularSpeed = (aLeftWheelSpeed - aRightWheelSpeed) / mTrackWidth;

    CPose Result = arPose;
    Result.mPosition.x += LinearSpeed * std::cos( arPose.mHeading ) * aTimeStep;
    Result.mPosition.y += LinearSpeed * std::sin( arPose.mHeading ) * aTimeStep;
    Result.mHeading = NormaliseAngle( arPose.mHeading + AngularSpeed * aTimeStep );

    return Result;
}
