//-----------------------------------------------------------------------------
// CRobot.cpp
//-----------------------------------------------------------------------------

#include "CRobot.h"
#include "CVecMath.h"

const float CRobot::kBodyRadius = 15.0f;
const float CRobot::kTrackWidth = 2.0f * CRobot::kBodyRadius;

// The heading indicator is drawn a little longer than the body radius so its
// tip clears the edge of the disc and the facing direction is unmistakable.
const float CRobot::kHeadingLineFactor = 1.4f;
const float CRobot::kHeadingLineThickness = 3.0f;

//-----------------------------------------------------------------------------
CRobot::CRobot( const CPose& arStartPose, Color aBodyColor )
    :
        mPose( arStartPose ),
        mDrive( kTrackWidth ),
        mUpdateCount( 0 ),
        mBodyColor( aBodyColor )
{
    mTrail.AddPoint( mPose.mPosition );
}


//-----------------------------------------------------------------------------
CRobot::~CRobot()
{
}


//-----------------------------------------------------------------------------
// The trail point is recorded last, after OnAfterMove() has had its chance to
// correct the position, so the trail always shows where the robot really
// ended the step rather than where it was before being pushed out of a wall.
//-----------------------------------------------------------------------------
void CRobot::Update( float aTimeStep )
{
    mDrive.SetWheelSpeeds( ComputeWheelSpeeds() );

    mPose = mDrive.Step( mPose, aTimeStep );
    ++mUpdateCount;

    OnAfterMove();

    mTrail.AddPoint( mPose.mPosition );
}


//-----------------------------------------------------------------------------
void CRobot::OnAfterMove()
{
    // Default: nothing extra to do after moving. Overridden by robots that
    // need to react to their new position, e.g. the wall follower checking
    // for a collision.
}


//-----------------------------------------------------------------------------
void CRobot::Draw( CRender& arRender ) const
{
    const float HeadingLineLength = kBodyRadius * kHeadingLineFactor;

    mTrail.Draw( arRender, mBodyColor );

    arRender.DrawCircle( mPose.mPosition, int( kBodyRadius ), mBodyColor );

    Vec2D FacingDirection = CVecMath::FromAngle( mPose.mHeading );
    Vec2D HeadingLineEnd = CVecMath::Add( mPose.mPosition,
                                           CVecMath::Scale( FacingDirection, HeadingLineLength ) );
    arRender.DrawLine( mPose.mPosition, HeadingLineEnd, kHeadingLineThickness, BLACK );
}


//-----------------------------------------------------------------------------
void CRobot::SetPosition( Vec2D aPosition )
{
    mPose.mPosition = aPosition;
}


//-----------------------------------------------------------------------------
const CPose& CRobot::GetPose() const
{
    return mPose;
}


//-----------------------------------------------------------------------------
int CRobot::GetUpdateCount() const
{
    return mUpdateCount;
}
