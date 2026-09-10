// CRobotController.cpp
//
// Implements the controller. Every subsystem is reached through the CSubsystem
// interface, so nothing here mentions a particular kind of subsystem.
//
// MTRX3760 Lab 1, A5.

//--Includes-------------------------------------------------------------------
#include <iostream>
#include "CRobotController.h"
#include "CSubsystem.h"

//---CRobotController Implementation-------------------------------------------
CRobotController::CRobotController()
  : mNumSubsystems( 0 ),
    mCycleCount( 0 )
{
  // Start every slot empty, so an unused slot never holds a stray address.
  for( int i = 0; i < MaxSubsystems; ++i )
  {
    mpSubsystems[i] = 0;
  }
}
//---
CRobotController::~CRobotController()
{
  // The controller owns its subsystems, so it destroys them. CSubsystem has a
  // virtual destructor, so each derived destructor runs even though these are
  // CSubsystem pointers.
  for( int i = 0; i < mNumSubsystems; ++i )
  {
    delete mpSubsystems[i];
  }
}
//---
void CRobotController::AddSubsystem( CSubsystem* apSubsystem )
{
  if( mNumSubsystems < MaxSubsystems )
  {
    mpSubsystems[mNumSubsystems] = apSubsystem;
    ++mNumSubsystems;
  }
  else
  {
    std::cout << "Controller is full, " << apSubsystem->GetName()
              << " was not added" << std::endl;
    delete apSubsystem;
  }
}
//---
void CRobotController::RunCycle()
{
  ++mCycleCount;

  std::cout << "--- Cycle " << mCycleCount << " ---" << std::endl;

  for( int i = 0; i < mNumSubsystems; ++i )
  {
    mpSubsystems[i]->Update();

    std::cout << mpSubsystems[i]->GetName() << ": ";
    mpSubsystems[i]->Report();
    std::cout << std::endl;
  }
}
