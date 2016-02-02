#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
#include "ofxGui.h"
#include "ofxMidi.h"
#include "ofxOsc.h"

#define PORT 12345

class ofApp : public ofBaseApp, public ofxMidiListener {
public:
	void setup();
	void update();
	void exit();
	void draw();
	
	
	ofxDmx dmx;
	int level;
    
    ofxPanel panel;
	ofParameter<int> sliders[24];

	void keyPressed(int key);

	void newMidiMessage(ofxMidiMessage& eventArgs);

	stringstream text;
	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;

	int recordPitch = 0;
	int recordControl = 0;
	bool recording = false;

	//---------
	ofxOscReceiver receive;
	float oscV = 0.0;
	string oscProp = "";
};
