// An oven temperature model (public-data version)
//
// This program models two ovens that warm up in steps and warn if they
// overheat. Each oven's data is stored in public member variables, and main()
// reads and changes the temperatures directly.
//
// Temperature is held in tenths of a degree Celsius, so that finer resolution
// can be represented. The printed output is unchanged: whole degrees. Because
// the data is public, every line of main() that touches a temperature had to
// be changed to suit the new units.
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
// COven holds an oven's name and current temperature. Both members are public,
// so any code can read or change them directly, and so any code that does must
// know the units the temperature is stored in.
class COven
{
  public:
    std::string mName;         // the oven's label, e.g. "Reflow oven"
    int mTemperatureTenthsC;   // current temperature, in tenths of a degree C
};

//---main----------------------------------------------------------------------
// Sets up two ovens, warms each in one-degree steps, checks each for
// overheating, and reports both. Every step reaches into the ovens' data
// directly, and so every step works in tenths of a degree.
int main()
{
  COven ReflowOven;
  ReflowOven.mName = "Reflow oven";
  ReflowOven.mTemperatureTenthsC = RoomTemperatureTenthsC;

  COven CuringOven;
  CuringOven.mName = "Curing oven";
  CuringOven.mTemperatureTenthsC = RoomTemperatureTenthsC;

  for( int i = 0; i < ReflowWarmUpSteps; ++i )
    ReflowOven.mTemperatureTenthsC += WarmUpStepTenthsC;

  for( int i = 0; i < CuringWarmUpSteps; ++i )
    CuringOven.mTemperatureTenthsC += WarmUpStepTenthsC;

  if( ReflowOven.mTemperatureTenthsC >= OverheatLimitTenthsC )
    std::cout << "Warning: oven is overheating!" << std::endl;

  if( CuringOven.mTemperatureTenthsC >= OverheatLimitTenthsC )
    std::cout << "Warning: oven is overheating!" << std::endl;

  std::cout << ReflowOven.mName << " is at "
            << ReflowOven.mTemperatureTenthsC / TenthsPerDegreeC
            << "C" << std::endl;

  std::cout << CuringOven.mName << " is at "
            << CuringOven.mTemperatureTenthsC / TenthsPerDegreeC
            << "C" << std::endl;

  return 0;
}
