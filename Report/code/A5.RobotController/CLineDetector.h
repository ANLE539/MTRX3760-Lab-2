// CLineDetector.h
//
// Declares the subsystem that watches the floor for the line the robot is
// following. It holds the last light reading and whether that reading means the
// line is underneath.
//
// MTRX3760 Lab 1, A5.

#ifndef CLINEDETECTOR_H
#define CLINEDETECTOR_H

#include <string>
#include "CSubsystem.h"

//--Consts---------------------------------------------------------------------
const int NumTrackReadings = 4;    // how many readings the canned track holds
const int LineThreshold    = 400;  // at or above this, the line is underneath

//---CLineDetector-------------------------------------------------------------
// A CLineDetector is the subsystem that senses the line. Each cycle it takes
// the next reading from a fixed track of test values, and works out from that
// reading whether the line is underneath the robot.
class CLineDetector : public CSubsystem
{
  public:
    // Creates a line detector with the given label, at the start of the track
    // with nothing read yet.
    CLineDetector( const std::string& aName );

    // GetLightReading returns the most recent reading, so that other code can
    // use the raw value rather than only the decision made from it.
    int GetLightReading();

    // Update takes the next reading from the track and decides from it whether
    // the line is underneath. The track repeats once it runs out, so the
    // detector keeps working however many cycles the robot runs for.
    void Update();

    // Report prints the last reading and whether the line was found.
    void Report();

  private:
    int mSensorValue;      // the most recent light reading
    bool mLineDetected;    // whether that reading means the line is underneath
    int mReadingIndex;     // how many readings have been taken so far
};

#endif
