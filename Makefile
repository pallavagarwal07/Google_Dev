OS := $(shell uname)
ARCH := $(shell uname -m)
LEAP_LIBRARY := ./LeapSDK/lib/x64/libLeap.so -Wl,-rpath,./LeapSDK/lib/x64


leap_sample: leap_sample.cpp
	$(CXX) -Wall -g -I./LeapSDK/include leap_sample.cpp -o leap_sample $(LEAP_LIBRARY)

clean:
	rm -rf Sample Sample.dSYM

gl_test: gl_test.cpp
	g++ -o $@ $< -lGL -lGLU -lglut

multiple_window: multiple_window.cpp
	g++ -o $@ $< -lGL -lGLU -lglut
