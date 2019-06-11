#ifndef LOWER_HALF_HPP
#define LOWER_HALF_HPP

#include "ofMain.h"

class LowerHalf {
public:
	LowerHalf(size_t x, size_t y, size_t width, size_t height) :
		x(x), y(y), width(width), height(height),
		background("lower/background.png"), hand("lower/hand.png")
	{
		// Do Nothing
	}

	void draw() {
		background.draw(x, y, width, height);
		hand.draw(x, y, width, height);
	}

private:
	size_t x, y;
	size_t height, width;

	ofImage background;
	ofImage hand;

	ofImage lunchbox[4];
};

#endif