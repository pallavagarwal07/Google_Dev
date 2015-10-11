#include <iostream>
#include <string.h>
#include "Leap.h"

using namespace Leap;
using namespace std;

void oneFrame(const Controller& controller);

class SampleListener:public Listener {
	public:
	virtual void onConnect(const Controller&);
	virtual void onFrame(const Controller&);
};

void SampleListener::onConnect(const Controller& controller){
	cout << "Connected" << endl;
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	//oneFrame(controller);
}

void SampleListener::onFrame(const Controller& controller)
{
	//cout << "Testing";
	const Frame frame = controller.frame();
	Leap::GestureList gestures = frame.gestures();
	for(Leap::GestureList::const_iterator gl = gestures.begin(); gl != gestures.end(); gl++)
	{
	    switch ((*gl).state()) {
	        case Leap::Gesture::STATE_START:
	            cout << "Start" << endl;//Handle starting gestures
	            break;
	        case Leap::Gesture::STATE_UPDATE:
	            //cout << "continuing";//Handle continuing gestures
	            break;
	        case Leap::Gesture::STATE_STOP:
	        {    cout << "stop" << endl;//Handle ending gestures
	            std::string clockwiseness;
	            Leap::CircleGesture circleGesture = Leap::CircleGesture(*gl);
				/*if ((circleGesture).pointable().direction().angleTo((circleGesture.normal())) <= Leap::PI/2) {
    				clockwiseness = "clockwise";
				}
				else
				{
				    clockwiseness = "counterclockwise";
				}*/
				cout << circleGesture.normal() << endl;
	            break;
	        }    
	        default:
	            //Handle unrecognized states
	            break;
	    }
	}
}

void oneFrame(const Controller& controller){
	cout << "Frame availables" << endl;
	const Frame frame = controller.frame();
	/*std::cout << "Frame id: " << frame.id()
          << ", timestamp: " << frame.timestamp()
          << ", hands: " << frame.hands().count()
          << ", fingers: " << frame.fingers().count()
          << ", tools: " << frame.tools().count()
          << ", gestures: " << frame.gestures().count() << std::endl;*/
    HandList hands = frame.hands();
    int i;
    Finger fingers[10];
    Vector coordinates[10][4];
    for(i=0;i<10;i++)
    {
    	fingers[i]=hands[i/5].fingers()[i%5];
    	//cout << "TIP " << fingers[i].tipPosition();
    	int j;
    	for(j=1;j<4;j++)
    	{
			Bone::Type boneType = static_cast<Leap::Bone::Type>(j);
			//cout << "NUMBER " << j << endl;
			Bone bone = fingers[i].bone(boneType);// << endl;
			if(j==1)
				coordinates[i][0]=bone.prevJoint();
			coordinates[i][j]=bone.nextJoint();
			//cout << "NEXT " << bone.nextJoint() << endl;
			//cout << "PREVIOUS  " << bone.prevJoint() << endl;
			//cout << bone.type() << endl;

		}

		for(j=0;j<10;j++)
		{
			int k;
			for(k=0;k<4;k++)
			{
				cout << coordinates[j][k];
			}
		}
	}

    //Hand firstHand = hands[0];
    //Finger rightFinger = firstHand.fingers().rightmost();
    //cout << rightFinger.tipPosition();
}

void gesture(const Controller& controller)
{
	const Frame frame = controller.frame();	
	Leap::GestureList gestures = frame.gestures();
	for(Leap::GestureList::const_iterator gl = gestures.begin(); gl != gestures.end(); gl++)
	{
	    switch ((*gl).state()) {
	        case Leap::Gesture::STATE_START:
	            cout << "Start";//Handle starting gestures
	            break;
	        case Leap::Gesture::STATE_UPDATE:
	            cout << "continuing";//Handle continuing gestures
	            break;
	        case Leap::Gesture::STATE_STOP:
	            cout << "stop";//Handle ending gestures
	            break;
	        default:
	            //Handle unrecognized states
	            break;
	    }
	}
}

int main(int argc, char** argv)
{
	SampleListener listener;
	Controller controller;

	controller.addListener(listener);
	gesture(controller);
	

	cout << "Press Enter to quit..." << endl;
	cin.get();
	while(1)
	oneFrame(controller);

	controller.removeListener(listener);
	return 0;
}