// CDriveMotor.cpp
//
// Implements the drive motor subsystem.
//
// MTRX3760 Lab 1, A5.

//--Includes-------------------------------------------------------------------
#include <iostream>
#include "CDriveMotor.h"

//---CDriveMotor Implementation------------------------------------------------
CDriveMotor::CDriveMotor( const std::string& aName )
  : CSubsystem( aName ),
    mSpeed( 0 ),
    mPosition( 0 )
{
}
//---
void CDriveMotor::SetSpeed( int aSpeed )
{
  int ClampedSpeed = aSpeed;

  if( aSpeed < MinMotorSpeed )
  {
    ClampedSpeed = MinMotorSpeed;
  }
  else if( aSpeed > MaxMotorSpeed )
  {
    ClampedSpeed = MaxMotorSpeed;
  }

  mSpeed = ClampedSpeed;
}
//---
void CDriveMotor::Update()
{
  mPosition += mSpeed;
}
//---
void CDriveMotor::Report()
{
  std::cout << "speed " << mSpeed << ", position " << mPosition;
}
