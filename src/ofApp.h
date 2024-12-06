#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofEvents.h"
#include "ofxImGui.h"
#include "Config.h"

class ofApp : public ofBaseApp {

public:
	// Arduino
	ofxImGui::Gui m_gui;

	int m_stretchVal;

	ofArduino				m_arduino;
	ofTrueTypeFont          m_font;
	bool					m_bSetup;       //is Arduinio initialized yet
	void setupArduino(const int& _version);
	void updateArduino();
	void digitalPinChanged(const int& pinNum);
	void analogPinChanged(const int& pinNum);

	float getIRDistance(int& val);

	// Main functions
	void setup();
	void update();
	void draw();

	// Images
	ofImage m_playerImg;
	ofImage m_playerImgflip;

	ofImage m_chainsawImg;

	ofImage m_birch;
	ofImage m_oak;
	ofImage m_jungle;

	ofRectangle m_birbox;
	ofRectangle m_oakbox;
	ofRectangle m_junbox;

	int playerX = 0;
	int playerY = 0;
	bool flip = false;

	// Chainsaw stuff
	float chainsawX;
	float chainsawY;
	bool m_chainsawActive;

	float chainsawRotation;
	float chainsawRotationSpeed = 1.5f;
	bool chainsawSwingingUp = true;

	ofRectangle m_playerhitbox;

	float startTime;
	bool TimerEnd;

	int m_timelimit = 32;
	ofTrueTypeFont m_text;
	ofTrueTypeFont m_text2;

	bool m_oakdel;
	bool m_birchdel;
	bool m_jungdel;

	bool m_gameover = false;

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};
