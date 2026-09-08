//-----------------------------------------------------------------------------
// CRobot.cpp
//-----------------------------------------------------------------------------

#include "CRobot.h"
#include "CVecMath.h"

const float CRobot::kBodyRadius = 15.0f;
const float CRobot::kTrackWidth = 2.0f * CRobot::kBodyRadius;

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
void CRobot::Update( float aTimeStep )
{
    float LeftWheelSpeed = 0.0f;
    float RightWheelSpeed = 0.0f;
    ComputeWheelSpeeds( LeftWheelSpeed, RightWheelSpeed );

    mPose = mDrive.Step( mPose, LeftWheelSpeed, RightWheelSpeed, aTimeStep );
    mTrail.AddPoint( mPose.mPosition );
    ++mUpdateCount;

    OnAfterMove();
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
    const float HeadingLineLength = kBodyRadius * 1.4f;

    mTrail.Draw( arRender, mBodyColor );

    arRender.DrawCircle( mPose.mPosition, int( kBodyRadius ), mBodyColor );

    Vec2D FacingDirection = CVecMath::FromAngle( mPose.mHeading );
    Vec2D HeadingLineEnd = CVecMath::Add( mPose.mPosition,
                                           CVecMath::Scale( FacingDirection, HeadingLineLength ) );
    arRender.DrawLine( mPose.mPosition, HeadingLineEnd, 3.0f, BLACK );
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
