CC = g++
CXX_FLAGS = -O3 -Wall
CXX_FLAGS+="-DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED"

build:
	$(CC) $(CXX_FLAGS) -g master.cpp -o master `pkg-config --cflags --libs gtk+-3.0` -L. -lsl_lidar_sdk
#	$(CC) $(CXX_FLAGS) -g get-arr.c -o get-arr
#	$(CC) $(CXX_FLAGS) -g navigation.cpp -o navigation