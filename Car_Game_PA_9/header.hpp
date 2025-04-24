/*

Names: Iyke Odum, Austin Daniels, Kadara Tandia
Assignment: Programming Assignment 9
Due: 4/23/2025
Description: For this final assignment, we are required to create a solution, as a team,
to a game or graphical application of our choice

*/

//gaurd code
#pragma once

//libraries
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <array>;


//using statements
using std::cin;
using std::cout;
using std::cerr; 
using std::endl;
using std::srand; //using for randomness in the obstacles
using std::time;  //using for randomness in the obstacles
using std::to_string;
using std::string;
using std::optional;
using std::vector;
using std::array;


using namespace sf;

//Object Manager
class ObjectManager {

public:

	ObjectManager(Texture& newTexture, Vector2u newWindowSize, float newSpeed) :
		texture(newTexture), windowSize(newWindowSize), speed(newSpeed) {}

	virtual void update() = 0;
	virtual void draw(RenderWindow& window) = 0;
	virtual void restart() = 0;

protected:
	Texture& texture;
	Vector2u windowSize;
	float speed;
};

//Game State
enum GameState {
	Menu, //for future use to add a menu
	Playing,
	EndScreen
};