// An oven temperature model (encapsulated version)
//
// This program models two ovens that warm up in steps and warn if they
// overheat. Each oven's data is private, and main() works through meaningful
// functions rather than touching the temperatures directly.
//
// Temperature is held internally in tenths of a degree Celsius, so that finer
// resolution can be represented. The printed output is unchanged: whole
// degrees.
//
// Copyright (c) Donald Dansereau, 2026
// Modified for MTRX3760 Lab 1, A2.

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//--Consts---------------------------------------------------------------------
// Temperatures are counted in tenths of a degree Celsius. Whole tenths are used
// rather than a fractional degree so that the overheating test stays an exact
// integer comparison.
const int TenthsPerDegreeC       = 10;
const int RoomTemperatureTenthsC = 20 * TenthsPerDegreeC;
const int WarmUpStepTenthsC      = 1 * TenthsPerDegreeC;
const int OverheatLimitTenthsC   = 250 * TenthsPerDegreeC;

// How far each oven is warmed before it is checked and reported.
const int ReflowWarmUpSteps = 5;
const int CuringWarmUpSteps = 8;

//---COven---------------------------------------------------------------------
// COven holds an oven's name and current temperature. The temperature is
// private: callers change and inspect it only through the functions below, and
// so never see the units it is stored in.
class COven
{
  public:
    // Creates an oven with the given name, at room temperature.
    COven( const std::string& aName );

    // WarmUp raises the oven's temperature by one step.
    void WarmUp();

    // IsOverheating reports whether the oven has passed its safe limit.
    bool IsOverheating();

    // Report prints the oven's name and current temperature, rounded down to
    // whole degrees Celsius.
    void Report();

  private:
    std::string mName;         // the oven's label, e.g. "Reflow oven"
    int mTemperatureTenthsC;   // current temperature, in tenths of a degree C
};

//---main----------------------------------------------------------------------
// Sets up two ovens, warms each in steps, checks each for overheating, and
// reports both.
int main()
{
  COven ReflowOven( "Reflow oven" );
  COven CuringOven( "Curing oven" );

  for( int i = 0; i < ReflowWarmUpSteps; ++i )
    ReflowOven.WarmUp();

  for( int i = 0; i < CuringWarmUpSteps; ++i )
    CuringOven.WarmUp();

  if( ReflowOven.IsOverheating() )
    std::cout << "Warning: oven is overheating!" << std::endl;

  if( CuringOven.IsOverheating() )
    std::cout << "Warning: oven is overheating!" << std::endl;

  ReflowOven.Report();
  CuringOven.Report();

  return 0;
}

//---COven Implementation------------------------------------------------------
COven::COven( const std::string& aName )
  : mName( aName ),
    mTemperatureTenthsC( RoomTemperatureTenthsC )
{
}
//---
void COven::WarmUp()
{
  mTemperatureTenthsC += WarmUpStepTenthsC;
}
//---
bool COven::IsOverheating()
{
  return mTemperatureTenthsC >= OverheatLimitTenthsC;
}
//---
void COven::Report()
{
  std::cout << mName << " is at "
            << mTemperatureTenthsC / TenthsPerDegreeC << "C" << std::endl;
}
