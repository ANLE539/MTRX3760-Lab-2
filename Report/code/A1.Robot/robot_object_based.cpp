// A line-following robot (object-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// Each part of the robot is a class, and a CRobot holds those parts and puts
// them to work.
//
// The robot runs on a battery that loses charge each cycle. Once the charge
// falls below its low-charge threshold the robot drives forward more slowly.
// Steering is unaffected.
//
// Copyright (c) Donald Dansereau, 2026
// Modified for MTRX3760 Lab 1, A1.

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//--Consts---------------------------------------------------------------------
const int NumCycles = 4;              // how many cycles the robot runs for
const double BaseSpeed = 0.5;         // forward speed before steering is added
const double LowBaseSpeed = 0.25;     // forward speed once the battery is low

// Battery levels, in percent of a full charge.
const double FullChargeLevel    = 100.0;
const double DrainPerCycle      = 10.0;
const double LowChargeThreshold = 80.0;

//---CLineSensor---------------------------------------------------------------
// A CLineSensor reports how far the robot is off the line. It remembers which
// cycle it is up to so that successive reads walk along the track.
class CLineSensor
{
  public:
    // Creates a sensor at the beginning of the track.
    CLineSensor();

    // Read returns how far the robot is off the line this cycle. Positive
    // means the line is off to one side, negative the other.
    int Read();

  private:
    int mCycle;             // how many readings have been taken so far
};

//---CController---------------------------------------------------------------
// A CController turns an off-line reading into a steering amount. It remembers
// the previous reading so it can respond to how fast the error is changing.
class CController
{
  public:
    // Creates a controller with no previous reading.
    CController();

    // ComputeSteering works out how hard to steer, from how far off the line
    // the robot is and how quickly that is changing.
    double ComputeSteering( int aError );

  private:
    double mLastError;      // the reading from the previous cycle
};

//---CMotor--------------------------------------------------------------------
// A CMotor is a single drive motor with a label and a current speed.
class CMotor
{
  public:
    // Creates a motor with the given label, stopped.
    CMotor( const std::string& aName );

    // SetSpeed sets the motor's speed.
    void SetSpeed( double aSpeed );

    // Report prints the motor's label and current speed.
    void Report();

  private:
    std::string mName;      // the motor's label, e.g. "Left"
    double mSpeed;          // current speed, -1.0 to 1.0
};

//---CBattery------------------------------------------------------------------
// A CBattery holds how much charge the robot has left, in percent. It loses
// charge one cycle at a time, and reports when it has run low.
class CBattery
{
  public:
    // Creates a fully charged battery.
    CBattery();

    // Drain takes one cycle's worth of charge out of the battery.
    void Drain();

    // IsLow reports whether the charge has fallen below the level at which the
    // robot drives forward more slowly.
    bool IsLow();

  private:
    double mChargeLevel;    // remaining charge, counting down from full
};

//---CRobot--------------------------------------------------------------------
// A CRobot has a line sensor, a controller, two drive motors and a battery. It
// offers operations described in terms of the whole robot rather than its
// parts.
class CRobot
{
  public:
    // Creates a robot with all of its parts ready to run.
    CRobot();

    // Update runs one cycle of the robot.
    void Update();

    // Report prints the state of the robot.
    void Report();

  private:
    CLineSensor mSensor;
    CController mController;
    CMotor mLeftMotor;
    CMotor mRightMotor;
    CBattery mBattery;
};

//---main----------------------------------------------------------------------
// Creates a robot, then runs it for a number of cycles, reporting it after
// each one.
int main()
{
  CRobot robot;

  for( int i = 0; i < NumCycles; ++i )
  {
    robot.Update();
    robot.Report();
  }

  return 0;
}

//---CLineSensor Implementation------------------------------------------------
CLineSensor::CLineSensor()
  : mCycle( 0 )
{
}
//---
int CLineSensor::Read()
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ mCycle ];
  ++mCycle;

  return reading;
}

//---CController Implementation------------------------------------------------
CController::CController()
  : mLastError( 0.0 )
{
}
//---
double CController::ComputeSteering( int aError )
{
  double steering = 0.1 * aError + 0.05 * ( aError - mLastError );
  mLastError = aError;

  return steering;
}

//---CMotor Implementation-----------------------------------------------------
CMotor::CMotor( const std::string& aName )
  : mName( aName ),
    mSpeed( 0.0 )
{
}
//---
void CMotor::SetSpeed( double aSpeed )
{
  mSpeed = aSpeed;
}
//---
void CMotor::Report()
{
  std::cout << mName << " motor " << mSpeed;
}

//---CBattery Implementation---------------------------------------------------
CBattery::CBattery()
  : mChargeLevel( FullChargeLevel )
{
}
//---
void CBattery::Drain()
{
  mChargeLevel -= DrainPerCycle;
}
//---
bool CBattery::IsLow()
{
  return mChargeLevel < LowChargeThreshold;
}

//---CRobot Implementation-----------------------------------------------------
CRobot::CRobot()
  : mLeftMotor( "Left" ),
    mRightMotor( "Right" )
{
}
//---
void CRobot::Update()
{
  int error = mSensor.Read();
  double steering = mController.ComputeSteering( error );

  mBattery.Drain();

  double activeBaseSpeed = BaseSpeed;
  if( mBattery.IsLow() )
  {
    activeBaseSpeed = LowBaseSpeed;
  }

  mLeftMotor.SetSpeed( activeBaseSpeed + steering );
  mRightMotor.SetSpeed( activeBaseSpeed - steering );
}
//---
void CRobot::Report()
{
  mLeftMotor.Report();
  std::cout << ", ";
  mRightMotor.Report();
  std::cout << std::endl;
}
