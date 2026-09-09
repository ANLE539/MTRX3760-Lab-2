A1/   Wall Follower
A2/   Wall Follower + Line Follower running together

A1 stays as its own frozen submission. A2 is a separate copy that builds on it - same wall follower, same base classes, plus a line follower added alongside. Each folder is self-contained: its own copy of the supplied CRender/CLoopReader files, its own .map file(s), its own build.sh. You can copy either folder out on its own and it has everything it needs.

Building

Install raylib first - see the top of CRender.h in either folder for the two install routes (apt on your own machine, or building from source into $HOME/raylib on a lab machine without sudo).

Then, from inside A1/ or A2/:

./build.sh

or run the g++ command by hand - the exact command is at the top of main.cpp in each folder, and in build.sh. If raylib was built from source rather than installed with apt, add the -I/-L flags noted in build.sh.

Run with:

./A1
./A2

Both read their .map file(s) from the current directory, so run them from inside their own folder.

What each one does

A1 opens an 800x600 window, draws the room from SimpleWalls.map, and drives one robot around it hugging the wall on its right, leaving a trail. It runs for 4000 fixed-timestep updates (about three laps), then just sits showing the finished trail until the window is closed. Collisions print to the console as they happen; a summary prints at the end.

A2 does the same, plus a second robot following the floor line from SimpleLine.map at the same time. The two robots don't interact. It runs for 6000 updates - comfortably more than one lap of the line, which takes about 3300.

Design

Both programs are built from the same small set of classes:

CSegmentLoop - raw geometry: ray-casting and nearest-point distance against a closed loop of segments. Knows nothing about walls or lines.
CRoom / CFloorLine - give a CSegmentLoop domain meaning: something to bump into, or something to sense underfoot.
CRangeSensor / CLineSensor - one sensor each, mounted at a fixed offset from the robot.
CRobot - abstract base: pose, CDifferentialDrive, CTrail, drawing the body. Subclasses supply ComputeWheelSpeeds().
CWallFollowerRobot / CLineFollowerRobot - the two concrete robots.
CSimulation - owns the window and the fixed-timestep loop, generic over any number of CRobots.
