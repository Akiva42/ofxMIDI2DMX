#include "ofApp.h"

void ofApp::setup() {
	ofBackground(0);

	//dmx.connect("COM4"); // use the name
	dmx.connect(0); // or use a number

	for (int i = 0; i < 24; i++) {
		sliders[i].set("Channel 1", 0, 0, 255);
	}
    panel.setName("Panel");
    panel.setup();
	for (int i = 0; i < 24; i++) {
		panel.add(sliders[i]);
	}

	//------
	ofSetLogLevel(OF_LOG_VERBOSE);
	midiIn.listPorts();
	midiIn.openPort(0);
	midiIn.ignoreTypes(false, false, false);
	midiIn.addListener(this);
	//midiIn.setVerbose(true);
	//------

	receive.setup(PORT);
	ofSetFrameRate(60);
}

void ofApp::update() {
	for (int i = 1; i < 23; i++) {
		dmx.setLevel(i, sliders[i-1].get());
	}
	dmx.update();

	//----

	while (receive.hasWaitingMessages()) {
		ofxOscMessage m;
		receive.getNextMessage(&m);
		oscProp = m.getAddress();
		oscV = m.getArgAsFloat(0);
		//ofLogVerbose() << "osc---addres: ";
		//for (int i = 0; i < m.getNumArgs; i++) {
		//	ofLogVerbose() << oscProp << " value: " << m.getArgAsFloat(i);
		//}
		if (m.getAddress() == "/1/fader1") {
			//chan2 = ofMap(m.getArgAsFloat(0),0,1,0,255);
		}
		oscV = m.getArgAsFloat(0);
	}
}

void ofApp::draw() {
   panel.draw();
}

void ofApp::exit() {

	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// make a copy of the latest message
	midiMessage = msg;
	if (recording) {
		recordControl = midiMessage.control;
		recordPitch = midiMessage.pitch;
	}
	recording = false;
	ofLogVerbose() << "midi---ptich: " << midiMessage.pitch << " control: " << midiMessage.control << " value: " << midiMessage.value;
	if (midiMessage.control != 0) {
			sliders[midiMessage.control-1] = ofMap(midiMessage.value, 0, 127, 0, 255);
			//chans[midiMessage.control] = ofMap(midiMessage.value, 0, 127, 0, 255);
	}
	else {
		//chan2 = ofMap(midiMessage.pitch, 48, 72, 0, 255);
	}
}
void ofApp::keyPressed(int key) {

	switch (key) {
	case 'l':
		midiIn.listPorts();
		break;
	}
	
	if (key == 'a') {
		ofLogVerbose() << "recorded midi---ptich: " << recordPitch << " control: " << recordControl;
	}
	if (key == 'r') {
		recording = true;
	}
}