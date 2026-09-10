// CLineDetector.cpp
//
// Implements the line detector subsystem.
//
// MTRX3760 Lab 1, A5.

//--Includes-------------------------------------------------------------------
#include <iostream>
#include "CLineDetector.h"

//---CLineDetector Implementation----------------------------------------------
CLineDetector::CLineDetector( const std::string& aName )
  : CSubsystem( aName ),
    mSensorValue( 0 ),
    mLineDetected( false ),
    mReadingIndex( 0 )
{
}
//---
int CLineDetector::GetLightReading()
{
  return mSensorValue;
}
//---
void CLineDetector::Update()
{
  // A stand-in for real hardware: a fixed stretch of track, bright where the
  // line is and dark where it is not.
  const int Track[NumTrackReadings] = { 512, 300, 640, 180 };

  mSensorValue = Track[ mReadingIndex % NumTrackReadings ];
  ++mReadingIndex;

  mLineDetected = ( mSensorValue >= LineThreshold );
}
//---
void CLineDetector::Report()
{
  std::cout << "reading " << mSensorValue << ", ";

  if( mLineDetected )
  {
    std::cout << "on the line";
  }
  else
  {
    std::cout << "off the line";
  }
}
