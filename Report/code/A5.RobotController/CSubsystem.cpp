// CSubsystem.cpp
//
// Implements the parts of the subsystem interface that are the same for every
// kind of subsystem: holding a label and handing it back.
//
// MTRX3760 Lab 1, A5.

//--Includes-------------------------------------------------------------------
#include "CSubsystem.h"

//---CSubsystem Implementation-------------------------------------------------
CSubsystem::CSubsystem( const std::string& aName )
  : mName( aName )
{
}
//---
CSubsystem::~CSubsystem()
{
}
//---
const std::string& CSubsystem::GetName()
{
  return mName;
}
