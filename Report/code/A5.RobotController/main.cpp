// main.cpp
//
// Builds a robot out of subsystems and runs it. Everything the robot does
// happens inside the controller and the subsystems; this file only decides
// which subsystems the robot has and how long it runs for.
//
// MTRX3760 Lab 1, A5.

//--Includes-------------------------------------------------------------------
#include "CRobotController.h"
#include "CDriveMotor.h"
#include "CLineDetector.h"

//--Consts---------------------------------------------------------------------
const int NumCycles  = 4;   // how many cycles the robot runs for
const int DriveSpeed = 3;   // travel per cycle asked of the drive motor

//---main----------------------------------------------------------------------
// Assembles the robot, hands its subsystems to the controller, and runs it for
// a number of cycles.
int main()
{
  CRobotController Controller;

  // The drive motor needs a speed before it is handed over, so it is created
  // by its own type first. Once the controller has it, it is only ever a
  // CSubsystem.
  CDriveMotor* pDriveMotor = new CDriveMotor( "DriveMotor" );
  pDriveMotor->SetSpeed( DriveSpeed );
  Controller.AddSubsystem( pDriveMotor );

  Controller.AddSubsystem( new CLineDetector( "LineDetector" ) );

  for( int i = 0; i < NumCycles; ++i )
  {
    Controller.RunCycle();
  }

  return 0;
}
