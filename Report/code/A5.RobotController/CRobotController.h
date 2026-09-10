// CRobotController.h
//
// Declares the controller that owns the robot's subsystems and runs them. The
// controller reaches every subsystem through the CSubsystem interface only, so
// a new kind of subsystem can be added without changing anything in this file.
//
// MTRX3760 Lab 1, A5.

#ifndef CROBOTCONTROLLER_H
#define CROBOTCONTROLLER_H

// Forward declaration: this header only stores and passes CSubsystem pointers,
// so it does not need the full declaration.
class CSubsystem;

//--Consts---------------------------------------------------------------------
const int MaxSubsystems = 16;   // how many subsystems one controller can hold

//---CRobotController----------------------------------------------------------
// A CRobotController owns a set of subsystems and drives them. On each cycle it
// updates every subsystem it holds and prints one line describing each. It
// knows nothing about what kinds of subsystem it is holding.
class CRobotController
{
  public:
    // Creates a controller with no subsystems, ready to be filled.
    CRobotController();

    // Destroys the controller and every subsystem it was given.
    ~CRobotController();

    // AddSubsystem puts a subsystem under this controller's care.
    //
    // The controller TAKES OWNERSHIP: it deletes the subsystem in its own
    // destructor, so the caller must not delete it and must not keep using it
    // afterwards. The intended call is
    //
    //     controller.AddSubsystem( new CDriveMotor( "DriveMotor" ) );
    //
    // A controller already holding MaxSubsystems subsystems has no room for
    // another. Rather than drop it silently it prints a message and destroys
    // the subsystem it was handed, so nothing is leaked.
    void AddSubsystem( CSubsystem* apSubsystem );

    // RunCycle runs one cycle of the robot: it updates every subsystem in turn
    // and prints its state, under a heading giving the cycle number.
    void RunCycle();

  private:
    CSubsystem* mpSubsystems[MaxSubsystems];   // the subsystems, owned by this
    int mNumSubsystems;                        // how many of them are in use
    int mCycleCount;                           // cycles run so far
};

#endif
