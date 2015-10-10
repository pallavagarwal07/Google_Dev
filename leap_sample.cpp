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
	controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onFrame(const Controller& controller){
	cout << "Frame availables" << endl;
	const Frame frame = controller.frame();
	/*std::cout << "Frame id: " << frame.id()
          << ", timestamp: " << frame.timestamp()
          << ", hands: " << frame.hands().count()
          << ", fingers: " << frame.fingers().count()
          << ", tools: " << frame.tools().count()
          << ", gestures: " << frame.gestures().count() << std::endl;*/
    HandList hands = frame.hands();
    Hand firstHand = hands[0];
    Finger rightFinger = firstHand.fingers().rightmost();
    cout << rightFinger.tipPosition();
}

int main(int argc, char** argv)
{
	SampleListener listener;
	Controller controller;

	controller.addListener(listener);
	

	cout << "Press Enter to quit..." << endl;
	cin.get();

	controller.removeListener(listener);
	return 0;
}