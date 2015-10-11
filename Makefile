OS := $(shell uname)
ARCH := $(shell uname -m)
LEAP_LIBRARY := ./LeapSDK/lib/x64/libLeap.so -Wl,-rpath,./LeapSDK/lib/x64


leap_sample: leap_sample.cpp
	$(CXX) -Wall -g -I./LeapSDK/include leap_sample.cpp -o leap_sample $(LEAP_LIBRARY)

clean:
	rm -rf Sample Sample.dSYM

gl_2 : gl_2.cpp
	g++ -o $@ $< -lGL -lGLU -lglut

gl_3 : gl_3.cpp
	g++ -Wall -g -I./LeapSDK/include -o $@ $< -lGL -lGLU -lglut $(LEAP_LIBRARY)

gl_test : gl_test.cpp
	g++ -o $@ $< -lGL -lGLU -lglut

multiple_window: multiple_window.cpp
	g++ -o $@ $< -lGL -lGLU -lglut
