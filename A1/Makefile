CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS = main.cpp CDifferentialDrive.cpp CLoopReader.cpp CRender.cpp CRangeSensor.cpp CRobot.cpp CRoom.cpp CSegmentLoop.cpp CSimulation.cpp CTrail.cpp CWallFollowerRobot.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = robot_sim

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)