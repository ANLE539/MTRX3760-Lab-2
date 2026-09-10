// CSubsystem.h
//
// Declares the interface that every part of the robot implements. A subsystem
// holds its own state, can be advanced by one cycle, and can describe that
// state. The controller works only through this interface, so a new kind of
// subsystem can be added without changing the controller.
//
// MTRX3760 Lab 1, A5.

#ifndef CSUBSYSTEM_H
#define CSUBSYSTEM_H

#include <string>

//---CSubsystem----------------------------------------------------------------
// A CSubsystem is one part of the robot. It is an abstract base class: it
// carries the label every subsystem needs, and leaves the two operations that
// differ from one kind of subsystem to the next for derived classes to supply.
class CSubsystem
{
  public:
    // Creates a subsystem with a short label used when reporting.
    CSubsystem( const std::string& aName );

    // Virtual so that deleting through a CSubsystem pointer also runs the
    // derived class destructor.
    virtual ~CSubsystem();

    // GetName returns the subsystem's label. Every subsystem carries its label
    // the same way, so this is not virtual.
    const std::string& GetName();

    // Update advances this subsystem's own state by one cycle. Every kind of
    // subsystem changes in its own way, so there is no sensible version here.
    virtual void Update() = 0;

    // Report describes this subsystem's current state.
    //
    // The controller prints the label and the end of the line itself, so this
    // function prints the state only: no label, and no newline. For example a
    // drive motor might print
    //
    //     speed 3, position 6
    //
    // and the controller turns that into
    //
    //     DriveMotor: speed 3, position 6
    //
    // Only the subsystem knows what its own state means, so each kind supplies
    // its own version.
    virtual void Report() = 0;

  private:
    std::string mName;      // the subsystem's label, e.g. "DriveMotor"
};

#endif
