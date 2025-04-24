

#include "obstaclemanager.hpp"

class Car : public ObjectManager {

public:

	//constructor for the car class 
	Car(Texture &newTexture, Vector2u newWindowSize, float newSpeed) : ObjectManager(newTexture, newWindowSize, newSpeed), car(newTexture) {

		this->movement = Vector2f(0.f, 0.f);

		//starting position dynamically starts at the bottom of the window regardless of size
		this->car.setPosition({ (windowSize.x - car.getGlobalBounds().size.x) / 2.f ,windowSize.y - car.getGlobalBounds().size.y - 10.f });
	}

	void update() override; //update the position each frame
	void draw(RenderWindow& window) override; //drawe the car onto the screen
	void checkCollision(ObstacleManager& obstacles, GameState &gameState); //check to see if the car ran into an obstacle
	void restart() override; //resets the position of the car
private:

	void checkBounds();

	Vector2f movement;
	Sprite car;
};