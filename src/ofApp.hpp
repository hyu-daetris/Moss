#pragma once

#include "ofMain.h"

#include "Constant.hpp"
#include "LowerHalf.hpp"

class ofApp : public ofBaseApp
{
public:
	ofApp() : lower_half(0, Constant::HALF, Constant::WIDTH, Constant::HALF) {
		// Do Nothing
	}

	void setup() {

	}

	void update() {

	}

	void draw() {
		lower_half.draw();
	}

	/*
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	*/

private:
	LowerHalf lower_half;
};
