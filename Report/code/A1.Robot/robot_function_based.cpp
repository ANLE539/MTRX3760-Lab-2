// A line-following robot (function-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// Each part of the robot is a struct, and free functions operate on those
// structs by taking them as arguments.
//
// The robot runs on a battery that loses charge each cycle. Once the charge
// falls below its low-charge threshold the robot drives forward more slowly.
// Steering is unaffected.
//
// Copyright (c) Donald Dansereau, 2026
// Modified for MTRX3760 Lab 1, A1.

//--Includes-------------------------------------------------------------------
#include <stdio.h>

//--Consts---------------------------------------------------------------------
const int NumCycles = 4;              // how many cycles the robot runs for
const double BaseSpeed = 0.5;         // forward speed before steering is added
const double LowBaseSpeed = 0.25;     // forward speed once the battery is low

// Battery levels, in percent of a full charge.
const double FullChargeLevel    = 100.0;
const double DrainPerCycle      = 10.0;
const double LowChargeThreshold = 80.0;

//---SLineSensor---------------------------------------------------------------
// SLineSensor reports how far the robot is off the line. It remembers which
// cycle it is up to so that successive reads walk along the track.
struct SLineSensor
{
  int cycle;              // how many readings have been taken so far
};

//---SController---------------------------------------------------------------
// SController turns an off-line reading into a steering amount. It remembers
// the previous reading so it can respond to how fast the error is changing.
struct SController
{
  double lastError;       // the reading from the previous cycle
};

//---SMotor--------------------------------------------------------------------
// SMotor holds one drive motor's label and its current speed.
struct SMotor
{
  const char* pName;      // the motor's label, e.g. "Left"
  double speed;           // current speed, -1.0 to 1.0
};

//---SBattery------------------------------------------------------------------
// SBattery holds how much charge the robot has left, in percent.
struct SBattery
{
  double charge;          // remaining charge, counting down from full
};

//---Function declarations-----------------------------------------------------
void InitLineSensor( SLineSensor* apSensor );
void InitController( SController* apController );
void InitMotor( SMotor* apMotor, const char* aName );
void InitBattery( SBattery* apBattery );

int ReadLineSensor( SLineSensor* apSensor );
double ComputeSteering( SController* apController, int aError );
void SetMotorSpeed( SMotor* apMotor, double aSpeed );
void DrainBattery( SBattery* apBattery );
bool IsBatteryLow( const SBattery* apBattery );

void UpdateRobot( SLineSensor* apSensor, SController* apController,
                  SMotor* apLeftMotor, SMotor* apRightMotor,
                  SBattery* apBattery );
void ReportRobot( SMotor* apLeftMotor, SMotor* apRightMotor );

//---main----------------------------------------------------------------------
// Sets up each part of the robot, then runs it for a number of cycles,
// reporting the motors after each one.
int main()
{
  SLineSensor sensor;
  SController controller;
  SMotor leftMotor;
  SMotor rightMotor;
  SBattery battery;

  InitLineSensor( &sensor );
  InitController( &controller );
  InitMotor( &leftMotor, "Left" );
  InitMotor( &rightMotor, "Right" );
  InitBattery( &battery );

  for( int i = 0; i < NumCycles; ++i )
  {
    UpdateRobot( &sensor, &controller, &leftMotor, &rightMotor, &battery );
    ReportRobot( &leftMotor, &rightMotor );
  }

  return 0;
}

//---InitLineSensor------------------------------------------------------------
// Starts the sensor at the beginning of the track.
void InitLineSensor( SLineSensor* apSensor )
{
  apSensor->cycle = 0;
}

//---InitController------------------------------------------------------------
// Starts the controller with no previous reading.
void InitController( SController* apController )
{
  apController->lastError = 0.0;
}

//---InitMotor-----------------------------------------------------------------
// Gives a motor its label and sets it stopped.
void InitMotor( SMotor* apMotor, const char* aName )
{
  apMotor->pName = aName;
  apMotor->speed = 0.0;
}

//---InitBattery---------------------------------------------------------------
// Starts the battery fully charged.
void InitBattery( SBattery* apBattery )
{
  apBattery->charge = FullChargeLevel;
}

//---ReadLineSensor------------------------------------------------------------
// Returns how far the robot is off the line this cycle. Positive means the
// line is off to one side, negative the other.
int ReadLineSensor( SLineSensor* apSensor )
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ apSensor->cycle ];
  ++apSensor->cycle;

  return reading;
}

//---ComputeSteering-----------------------------------------------------------
// Works out how hard to steer, from how far off the line the robot is and how
// quickly that is changing.
double ComputeSteering( SController* apController, int aError )
{
  double steering = 0.1 * aError + 0.05 * ( aError - apController->lastError );
  apController->lastError = aError;

  return steering;
}

//---SetMotorSpeed-------------------------------------------------------------
// Sets one motor's speed.
void SetMotorSpeed( SMotor* apMotor, double aSpeed )
{
  apMotor->speed = aSpeed;
}

//---DrainBattery--------------------------------------------------------------
// Takes one cycle's worth of charge out of the battery.
void DrainBattery( SBattery* apBattery )
{
  apBattery->charge -= DrainPerCycle;
}

//---IsBatteryLow--------------------------------------------------------------
// Reports whether the charge has fallen below the level at which the robot
// drives forward more slowly. Reads the battery without changing it.
bool IsBatteryLow( const SBattery* apBattery )
{
  return apBattery->charge < LowChargeThreshold;
}

//---UpdateRobot---------------------------------------------------------------
// Runs one cycle: read the sensor, work out the steering, take a cycle's
// charge out of the battery, and set both motors. A low battery reduces the
// forward speed but leaves the steering alone.
void UpdateRobot( SLineSensor* apSensor, SController* apController,
                  SMotor* apLeftMotor, SMotor* apRightMotor,
                  SBattery* apBattery )
{
  int error = ReadLineSensor( apSensor );
  double steering = ComputeSteering( apController, error );

  DrainBattery( apBattery );

  double activeBaseSpeed = BaseSpeed;
  if( IsBatteryLow( apBattery ) )
  {
    activeBaseSpeed = LowBaseSpeed;
  }

  SetMotorSpeed( apLeftMotor, activeBaseSpeed + steering );
  SetMotorSpeed( apRightMotor, activeBaseSpeed - steering );
}

//---ReportRobot---------------------------------------------------------------
// Prints the state of both of the robot's motors.
void ReportRobot( SMotor* apLeftMotor, SMotor* apRightMotor )
{
  printf( "%s motor %g, %s motor %g\n",
          apLeftMotor->pName, apLeftMotor->speed,
          apRightMotor->pName, apRightMotor->speed );
}
