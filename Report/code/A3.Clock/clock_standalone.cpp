// A clock model
//
// This program models a simple clock that keeps a time in minutes and can
// advance, report, and reset it. main() creates one plain clock and steps it
// forward by a minute.
//
// It also creates an alarm clock, which keeps a time in the same way and in
// addition holds an alarm time and reports when the alarm is ringing. In this
// version the alarm clock is a brand-new, separate class: inheritance is not
// used, so everything a CClock does is written out a second time.
//
// Copyright (c) Donald Dansereau, 2026
// Modified for MTRX3760 Lab 1, A3.

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//--Consts---------------------------------------------------------------------
const int MinutesPerDay = 1440;   // a clock wraps back to zero after this many
const int StartMinutes  = 419;    // 06:59, the time both clocks start at
const int AlarmMinutes  = 413;    // 06:53, earlier in the day than the start

//---CClock--------------------------------------------------------------------
// A CClock keeps a time, measured in whole minutes, and can advance it one
// minute at a time, report it, and reset it to where it started.
class CClock
{
  public:
    // Creates a clock with the given name and starting time, in minutes
    // since midnight.
    CClock( const std::string& aName, int aStartMinutes );

    // Tick advances the clock by one minute.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time.
    void Reset();

    // Report prints the clock's name and current time as HH:MM.
    void Report();

  private:
    std::string mName;          // the clock's label, e.g. "Kitchen"
    int mStartMinutes;          // the time the clock was initialised to
    int mCurrentMinutes;        // current time, in minutes since midnight
};

//---CAlarmClock---------------------------------------------------------------
// A CAlarmClock keeps a time just as a CClock does, and also holds an alarm
// time. It starts ringing on the first tick that reaches that time, and can be
// run forward until it does. This version may not use inheritance, so the
// name, the times, and every operation a CClock offers are repeated here.
class CAlarmClock
{
  public:
    // Creates an alarm clock with the given name and starting time, in minutes
    // since midnight, with its alarm set to midnight and not ringing.
    CAlarmClock( const std::string& aName, int aStartMinutes );

    // Tick advances the clock by one minute and starts the alarm ringing if it
    // reaches the alarm time. The time counts up without limit, so it is
    // folded into a single day before it is compared.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time and stops the alarm.
    void Reset();

    // Report prints the clock's name and current time as HH:MM, followed by a
    // line saying so if the alarm is ringing.
    void Report();

    // SetAlarm sets the time the alarm goes off, in minutes since midnight.
    // Times outside a single day are clamped into range, so that a time the
    // clock can actually reach is always stored.
    void SetAlarm( int aMinutes );

    // IsRinging reports whether the alarm is currently going off.
    bool IsRinging();

    // AdvanceToAlarm ticks the clock forward until the alarm rings.
    void AdvanceToAlarm();

  private:
    std::string mName;          // the clock's label, e.g. "Kitchen"
    int mStartMinutes;          // the time the clock was initialised to
    int mCurrentMinutes;        // current time, in minutes since midnight
    int mAlarmTime;             // the time the alarm goes off
    bool mIsRinging;            // whether the alarm is currently going off
};

//---main----------------------------------------------------------------------
// Creates one plain clock, starts it at 06:59, advances it one minute, and
// reports it. Then creates an alarm clock at the same time, sets its alarm,
// runs it forward until the alarm rings, and reports it.
int main()
{
  CClock clock( "Kitchen", StartMinutes );
  clock.Tick();
  clock.Report();

  CAlarmClock alarmClock( "Kitchen", StartMinutes );
  alarmClock.SetAlarm( AlarmMinutes );
  alarmClock.AdvanceToAlarm();
  alarmClock.Report();

  return 0;
}

//---CClock Implementation-----------------------------------------------------
CClock::CClock( const std::string& aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes )
{
}
//---
void CClock::Tick()
{
  ++mCurrentMinutes;
}
//---
int CClock::GetTime()
{
  return mCurrentMinutes;
}
//---
void CClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
void CClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;
}

//---CAlarmClock Implementation------------------------------------------------
CAlarmClock::CAlarmClock( const std::string& aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes ),
    mAlarmTime( 0 ),
    mIsRinging( false )
{
}
//---
void CAlarmClock::Tick()
{
  ++mCurrentMinutes;

  if( mCurrentMinutes % MinutesPerDay == mAlarmTime )
  {
    mIsRinging = true;
  }
}
//---
int CAlarmClock::GetTime()
{
  return mCurrentMinutes;
}
//---
void CAlarmClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
  mIsRinging = false;
}
//---
void CAlarmClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;

  if( mIsRinging )
  {
    std::cout << "The alarm is ringing" << std::endl;
  }
}
//---
void CAlarmClock::SetAlarm( int aMinutes )
{
  int ClampedMinutes = aMinutes;

  if( aMinutes < 0 )
  {
    ClampedMinutes = 0;
  }
  else if( aMinutes >= MinutesPerDay )
  {
    ClampedMinutes = MinutesPerDay - 1;
  }

  mAlarmTime = ClampedMinutes;
}
//---
bool CAlarmClock::IsRinging()
{
  return mIsRinging;
}
//---
void CAlarmClock::AdvanceToAlarm()
{
  while( !IsRinging() )
  {
    Tick();
  }
}
