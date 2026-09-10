// CDriveMotor.h
//
// Declares the subsystem that drives the robot forward. It holds a speed and
// keeps a running total of how far it has travelled.
//
// MTRX3760 Lab 1, A5.

#ifndef CDRIVEMOTOR_H
#define CDRIVEMOTOR_H

#include <string>
#include "CSubsystem.h"

//--Consts---------------------------------------------------------------------
// Speeds the motor accepts, in units of travel per cycle. Negative runs the
// motor in reverse.
const int MinMotorSpeed = -10;
const int MaxMotorSpeed = 10;

//---CDriveMotor---------------------------------------------------------------
// A CDriveMotor is the subsystem that moves the robot. Each cycle it travels a
// distance equal to its current speed, and it remembers how far it has gone
// altogether.
class CDriveMotor : public CSubsystem
{
  public:
    // Creates a drive motor with the given label, stopped at the origin.
    CDriveMotor( const std::string& aName );

    // SetSpeed sets how far the motor travels each cycle. Speeds outside the
    // range the motor supports are clamped into it, so the motor is never left
    // holding a setting it cannot drive at.
    void SetSpeed( int aSpeed );

    // Update moves the robot one cycle's worth of travel at the current speed.
    void Update();

    // Report prints the speed and the distance travelled so far.
    void Report();

  private:
    int mSpeed;         // travel per cycle, MinMotorSpeed to MaxMotorSpeed
    int mPosition;      // total distance travelled since the motor was created
};

#endif
