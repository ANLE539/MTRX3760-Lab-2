// A device power budget v2
//
// This program reports how much power each device on a robot is drawing, and
// the total. Each device is turned on or off and set up, then its power draw is
// reported and added to the total.
//
// Copyright (c) Donald Dansereau, 2026
// Modified for MTRX3760 Lab 1, A4.

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//--Consts---------------------------------------------------------------------
// Range of heat settings a heater accepts, and the power one unit of heat draws.
const int MinHeatLevel            = 0;
const int MaxHeatLevel            = 100;
const int HeaterWattsPerHeatLevel = 5;

//---CDevice-------------------------------------------------------------------
// A CDevice is a piece of equipment with a name that can be switched on or off.
// PowerDraw() reports the device's current power draw, in watts.
class CDevice
{
  public:
    CDevice( const std::string& aName );

    // Virtual so that deleting through a CDevice pointer also runs the
    // derived class destructor.
    virtual ~CDevice();

    void TurnOn();                            // switch the device on
    void TurnOff();                           // switch the device off
    bool IsOn();                              // whether the device is on
    const std::string& GetName();             // the device's label

    virtual int PowerDraw() = 0;              // power drawn, in watts

  private:
    std::string mName;
    bool mIsOn;
};

//---CMotor--------------------------------------------------------------------
// A CMotor is a device whose power draw grows with its speed setting.
class CMotor : public CDevice
{
  public:
    CMotor( const std::string& aName );

    void SetSpeed( int aSpeed );              // set the motor's speed
    int PowerDraw();                          // power drawn, in watts

  private:
    int mSpeed;
};

//---CLed----------------------------------------------------------------------
// A CLed is a device whose power draw grows with its brightness setting.
class CLed : public CDevice
{
  public:
    CLed( const std::string& aName );

    void SetBrightness( int aBrightness );    // set the LED's brightness
    int PowerDraw();                          // power drawn, in watts

  private:
    int mBrightness;
};

//---CHeater-------------------------------------------------------------------
// A CHeater is a device whose power draw grows with its heat setting. Heat
// settings outside the accepted range are clamped, so the heater never reports
// a negative or implausible power draw.
class CHeater : public CDevice
{
  public:
    CHeater( const std::string& aName );

    void SetHeatLevel( int aHeatLevel );      // set the heater's heat level
    int PowerDraw();                          // power drawn, in watts

  private:
    int mHeatLevel;
};

//---main----------------------------------------------------------------------
// Sets up a motor, an LED and a heater, then prints each device's power draw
// and the running total.
int main()
{
  CMotor driveMotor( "DriveMotor" );
  driveMotor.TurnOn();
  driveMotor.SetSpeed( 30 );

  CLed statusLed( "StatusLed" );
  statusLed.SetBrightness( 50 );

  CHeater cabinHeater( "CabinHeater" );
  cabinHeater.TurnOn();
  cabinHeater.SetHeatLevel( 40 );

  const int NumDevices = 3;
  CDevice* devices[NumDevices] = { &driveMotor, &statusLed, &cabinHeater };

  int total = 0;
  for( int i = 0; i < NumDevices; ++i )
  {
    int draw = devices[i]->PowerDraw();
    std::cout << devices[i]->GetName() << ": " << draw << " W" << std::endl;
    total += draw;
  }
  std::cout << "Total: " << total << " W" << std::endl;

  return 0;
}

//---CDevice Implementation----------------------------------------------------
CDevice::CDevice( const std::string& aName )
  : mName( aName ),
    mIsOn( false )
{
}
//---
CDevice::~CDevice()
{
}
//---
void CDevice::TurnOn()
{
  mIsOn = true;
}
//---
void CDevice::TurnOff()
{
  mIsOn = false;
}
//---
bool CDevice::IsOn()
{
  return mIsOn;
}
//---
const std::string& CDevice::GetName()
{
  return mName;
}

//---CMotor Implementation-----------------------------------------------------
CMotor::CMotor( const std::string& aName )
  : CDevice( aName ),
    mSpeed( 0 )
{
}
//---
void CMotor::SetSpeed( int aSpeed )
{
  mSpeed = aSpeed;
}
//---
int CMotor::PowerDraw()
{
  return IsOn() ? mSpeed * 2 : 0;
}

//---CLed Implementation-------------------------------------------------------
CLed::CLed( const std::string& aName )
  : CDevice( aName ),
    mBrightness( 0 )
{
}
//---
void CLed::SetBrightness( int aBrightness )
{
  mBrightness = aBrightness;
}
//---
int CLed::PowerDraw()
{
  return IsOn() ? mBrightness / 10 : 0;
}

//---CHeater Implementation----------------------------------------------------
CHeater::CHeater( const std::string& aName )
  : CDevice( aName ),
    mHeatLevel( 0 )
{
}
//---
void CHeater::SetHeatLevel( int aHeatLevel )
{
  int ClampedHeatLevel = aHeatLevel;

  if( aHeatLevel < MinHeatLevel )
  {
    ClampedHeatLevel = MinHeatLevel;
  }
  else if( aHeatLevel > MaxHeatLevel )
  {
    ClampedHeatLevel = MaxHeatLevel;
  }

  mHeatLevel = ClampedHeatLevel;
}
//---
int CHeater::PowerDraw()
{
  return IsOn() ? mHeatLevel * HeaterWattsPerHeatLevel : 0;
}
