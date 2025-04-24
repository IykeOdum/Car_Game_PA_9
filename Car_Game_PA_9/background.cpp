#include "background.hpp"

//Checks to see if the background is off screen and then puts it in front of the next background
void Background::update() {

	this->backgrounds[0].move({ 0, this->speed });
	this->backgrounds[1].move({ 0, this->speed });

	if (this->backgrounds[0].getPosition().y >= windowSize.y) {
		this->backgrounds[0].setPosition({ 0, this->backgrounds[1].getPosition().y - bgHeight });
	}
	if (this->backgrounds[1].getPosition().y >= windowSize.y) {
		this->backgrounds[1].setPosition({ 0, this->backgrounds[0].getPosition().y - bgHeight });
	}
}

//Draws the backgrounds on the screen
void Background::draw(RenderWindow& window) {

	window.draw(this->backgrounds[0]);
	window.draw(this->backgrounds[1]);
}

//resets the position of the backgrouds to where they were at the start
void Background::restart() {
	this->backgrounds[0].setPosition({ 0.f, 0.f });
	this->backgrounds[1].setPosition({ 0.f, this->bgHeight });
}
