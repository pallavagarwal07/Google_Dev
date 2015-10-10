#include <iostream>
#include <string.h>
#include "Leap.h"

using namespace Leap;
using namespace std;

class SampleListener:public Listener {
	public:
	virtual void onConnect(const Controller&);
	virtual void onFrame(const Controller&);
};

void SampleListener::onConnect(const Controller& controller){
	cout << "Connected" << endl;
}

void SampleListener::onFrame(const Controller& controller){
	
}

int main(int argc, char** argv)
{
	Controller controller;

	cout << "Press Enter to quit..." << endl;
	cin.get();

	return 0;
}