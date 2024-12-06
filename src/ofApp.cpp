#include "ofApp.h"
#include "ofxXmlSettings.h"
#include <string>

//--------------------------------------------------------------
void ofApp::setup() {
	// Set window size and framerate
	ofSetWindowShape(Config::APP_WINDOW_WIDTH, Config::APP_WINDOW_HEIGHT);
	ofSetFrameRate(Config::APP_DESIRED_FRAMERATE);

	// Arduino
	m_font.load("franklinGothic.otf", 16);

	m_arduino.connect(Config::ARDUINO_DEVICE_NAME, Config::ARDUINO_BAUD_RATE);

	m_stretchVal = 0.0f;

	ofAddListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

	m_bSetup = false;

	// Images
	m_playerImg.load("paul.webp");
	m_playerImgflip.load("paulflipped.png");

	m_chainsawImg.load("chainsaw.png");

	m_oak.load("oak.webp");
	m_birch.load("birch.webp");
	m_jungle.load("jungle.webp");

	ofSetRectMode(OF_RECTMODE_CENTER);

	playerX = (ofGetWidth() / 2) - m_playerImg.getWidth() / 2;
	playerY = (ofGetHeight() / 2) - (m_playerImg.getHeight() / 2) + 520;

	chainsawX = playerX;
	chainsawY = playerY;

	m_playerhitbox.set(playerX, playerY + 520, 100, 200);

	m_oakbox.set(600, playerY, 100, 500);
	//m_birbox.set(); 
	//m_junbox.set(); 

	startTime = ofGetElapsedTimeMillis();

	m_text.load("fontfile.TTF", 64);
	m_text2.load("fontfile.TTF", 64);

	m_oakdel = true;

	m_chainsawActive = false;
	chainsawRotation = -90.0f; // -90 degree angle is the initial rotation angle, the chainsaw should be facing upwards
}

//--------------------------------------------------------------
void ofApp::update() {
	// Arduino
	updateArduino();

	// If the stretch sensor value is above 10, then the chainsaw will appear
	if (m_stretchVal > 10 && !m_chainsawActive) {
		m_chainsawActive = true;
		chainsawX = playerX;
		chainsawY = playerY;
	}

	// Chainsaw position will follow the player
	if (m_chainsawActive) {
		chainsawX = playerX;
		chainsawY = playerY;

		// Swinging motion
		if (chainsawSwingingUp) {
			chainsawRotation += chainsawRotationSpeed;
			if (chainsawRotation >= 90.0f) { // Upper limit
				chainsawSwingingUp = false;
			}
		}
		else {
			chainsawRotation -= chainsawRotationSpeed;
			if (chainsawRotation <= -90.0f) { // Lower limit
				chainsawSwingingUp = true;
			}
		}
	}

	// Other
	if (m_gameover == false && flip == false && !(m_playerhitbox.intersects(m_oakbox))) {
		playerX = playerX + 2;
	}

	if (m_gameover == false && flip == true && !(m_playerhitbox.intersects(m_oakbox))) {
		playerX = playerX - 2;
	}


	if (playerX > 2000 || playerX < 300) {
		flip = true;
	}

	if (playerX < 300) {
		flip = false;
	}

	/* if (m_playerhitbox.intersects(m_oakbox)) {
		std:: cout << "Collison detected";
	} */

	m_playerhitbox.set(playerX - m_playerImg.getWidth(), playerY, 100, 200);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofPushMatrix();
	ofSetColor(181, 230, 90);
	ofDrawRectangle(1000, 950, 3000, 150);
	ofSetColor(255, 255, 255, 255);
	ofPopMatrix();

	if (flip == true) {
		m_playerImgflip.draw(playerX - m_playerImg.getWidth(), playerY);

		//ofRect(playerX - m_playerImg.getWidth(), playerY, 100,200);
		ofDrawRectangle(m_playerhitbox);

	}
	else {

		m_playerImg.draw(playerX - m_playerImg.getWidth(), playerY);


		//ofDrawRectangle(playerX - m_playerImg.getWidth(), playerY, 100, 200);
		ofDrawRectangle(m_playerhitbox);

	}
	//ofSetColor(181,230,29);
	//ofScale(3.5f, 3.0f);
	//m_playerImg.draw(0, 0);

	// Draw the chainsaw if it's active
	if (m_chainsawActive) {
		ofPushMatrix();
		ofTranslate(chainsawX - 100, chainsawY);
		ofRotateDeg(chainsawRotation);
		m_chainsawImg.draw(50, 0);
		ofPopMatrix();
	}

	if (m_oakdel == true) {
		ofPushMatrix();
		ofScale(1.0f, 1.0f);
		m_oak.draw(600, playerY);
		//m_oakbox.draw(); 
		//ofSetColor(0, 0, 0, 0);
		ofDrawRectangle(m_oakbox);
		ofSetColor(255, 255, 255, 255);
		ofPopMatrix();
	}


	ofPushMatrix();
	ofScale(1.0f, 1.0f);
	m_birch.draw(900, playerY - 200);
	ofSetColor(0, 0, 0, 0);
	ofDrawRectangle(900, playerY - 200, 100, 1000);
	ofSetColor(255, 255, 255, 255);
	ofPopMatrix();

	ofPushMatrix();
	ofScale(0.5f, 0.5f);
	m_jungle.draw(2800, playerY + 50);
	ofSetColor(0, 0, 0, 0);
	ofDrawRectangle(2800, playerY + 100, 200, 2000);
	ofSetColor(255, 255, 255, 255);
	ofPopMatrix();

	float timer = ofGetElapsedTimeMillis() - startTime;

	// display time 

	ofPushMatrix();
	if (m_gameover == false) {
		m_text.drawString(to_string(int(m_timelimit - ofGetElapsedTimef())), 50, 80);
		//m_text.drawString(to_string(int(playerX)), 50, 80);
	}
	ofPopMatrix();

	if (timer > 3000) {
		//ofDrawRectangle(100, 100, 100, 100);
	}


	if (m_timelimit - ofGetElapsedTimef() <= 0) {
		m_gameover = true;
		ofSetColor(255, 0, 0);
		m_text.drawString("Game Over", 550, 700);
	}

	/* if (m_playerhitbox.intersects(m_oakbox)) {
		ofSetColor(255, 0, 0);
		m_text.drawString("intersect", 550, 700);
	} */

	if (m_playerhitbox.intersects(m_oakbox)) {
		ofSetColor(255, 0, 0);
		m_text.drawString("intersect", 550, 700);
	}

	ofSetColor(255, 0, 0);
	m_text2.drawString(to_string(playerX), 0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	/*
	if (m_gameover == false) {
		if (key == OF_KEY_LEFT) {
			flip = true;
			playerX = playerX - 10;
		}
		else if (key == OF_KEY_RIGHT) {
			flip = false;
			playerX = playerX + 10;
		}
	}
	 */

	if (key = ' ' && m_gameover == false) {
		if (m_playerhitbox.intersects(m_oakbox)) {
			m_oakdel = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::setupArduino(const int& _version)
{
	m_bSetup = true;

	ofRemoveListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

	ofLogNotice() << m_arduino.getFirmwareName();
	ofLogNotice() << "firmata v" << m_arduino.getMajorFirmwareVersion() << "." << m_arduino.getMinorFirmwareVersion();

	m_arduino.sendAnalogPinReporting(Config::PIN_STRETCH_INPUT, ARD_ANALOG);

	m_arduino.sendDigitalPinMode(Config::PIN_RGB_PWM_BLUE_OUTPUT, ARD_PWM);

	ofAddListener(m_arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
	ofAddListener(m_arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino() {
	m_arduino.update();
}

void ofApp::digitalPinChanged(const int& pinNum) {
	//std::cout  << "digital pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getDigital(pinNum)) << std::endl;
}

void ofApp::analogPinChanged(const int& pinNum) {
	//std::cout  << "analog pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getAnalog(pinNum)) << std::endl;

	switch (pinNum) {
	case Config::PIN_STRETCH_INPUT: {
		m_stretchVal = m_arduino.getAnalog(pinNum);
		m_stretchVal = (int)ofMap(m_stretchVal, 850, 830, 0, Config::MAX_BRIGHTNESS, true);      //map and clamp

		m_arduino.sendPwm(Config::PIN_RGB_PWM_BLUE_OUTPUT, (int)m_stretchVal);
	};
	}
}

float ofApp::getIRDistance(int& val)
{
	if (val < 16)
	{
		val = 16;
	}

	return 2076.0f / (val - 11.0f);
}

