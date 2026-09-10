//-----------------------------------------------------------------------------
// CDifferentialDrive.cpp
//-----------------------------------------------------------------------------

#include "CDifferentialDrive.h"

#include <cmath>

const float CDifferentialDrive::kTwoPi = 2.0f * float( M_PI );

//-----------------------------------------------------------------------------
CDifferentialDrive::CDifferentialDrive( float aTrackWidth )
    :
        mTrackWidth( aTrackWidth )
{
}


//-----------------------------------------------------------------------------
void CDifferentialDrive::SetWheelSpeeds( const CWheelSpeeds& arSpeeds )
{
    mLeftWheel.SetSpeed( arSpeeds.mLeft );
    mRightWheel.SetSpeed( arSpeeds.mRight );
}


//-----------------------------------------------------------------------------
// Working in distances rolled rather than speeds keeps the kinematics in one
// place: the centre of the robot advances by the average of the two, and the
// robot turns by their difference spread over the track width.
//-----------------------------------------------------------------------------
CPose CDifferentialDrive::Step( const CPose& arPose, float aTimeStep ) const
{
    float LeftDistance = mLeftWheel.DistanceIn( aTimeStep );
    float RightDistance = mRightWheel.DistanceIn( aTimeStep );

    float ForwardDistance = 0.5f * ( LeftDistance + RightDistance );
    float HeadingChange = ( LeftDistance - RightDistance ) / mTrackWidth;

    CPose Result = arPose;
    Result.mPosition.x += ForwardDistance * std::cos( arPose.mHeading );
    Result.mPosition.y += ForwardDistance * std::sin( arPose.mHeading );
    Result.mHeading = NormaliseAngle( arPose.mHeading + HeadingChange );

    return Result;
}


//-----------------------------------------------------------------------------
float CDifferentialDrive::NormaliseAngle( float aAngle )
{
    float Result = std::fmod( aAngle, kTwoPi );

    if( Result < 0.0f )
    {
        Result += kTwoPi;
    }

    return Result;
}
