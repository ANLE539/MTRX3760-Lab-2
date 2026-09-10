#!/bin/sh
# Builds A2.
#
# If raylib was installed via apt, this works as-is. If it was built from
# source into $HOME/raylib instead, run with the include/lib paths added,
# e.g.:
#   g++ ... -I$HOME/raylib/include -L$HOME/raylib/lib -lraylib -o A2

g++ -std=c++17 -Wall -Wextra main.cpp CRender.cpp CLoopReader.cpp \
    CSegmentLoop.cpp CVecMath.cpp CRoom.cpp CFloorLine.cpp CTrail.cpp \
    CDifferentialDrive.cpp CWheel.cpp CRangeSensor.cpp CLineSensor.cpp \
    CRobot.cpp CWallFollowerRobot.cpp CLineFollowerRobot.cpp CSimulation.cpp \
    -lraylib -o A2
