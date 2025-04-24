/*

Names: Iyke Odum, Austin Daniels, Kadara Tandia
Assignment: Programming Assignment 9
Professor: Andrew O'Fallon
Due: 4/23/2025
Description: For this final assignment, we are required to create a solution, as a team,
to a game or graphical application of our choice

UPDATES NEEDED:


-create main menu (button to play the game and button for customization)
-score system (time based or number of obstacles dodged based)
-create end screen (display score)
-allow customization of car? (change color)


UPDATES COMPLETED:
-create classes for car
-created obstacles
-class for background
-scrolling background
-moving car


*/

#include "background.hpp"
#include "car.hpp"

int main(void) {

	//randomness -- Used for obstacles 
	srand(static_cast<unsigned>(time(nullptr)));

	//creating the game window
	Vector2u windowSize(500, 600);
	RenderWindow window(VideoMode(windowSize), "Top Down Driving Game");
	window.setFramerateLimit(60);


	float spawnInterval = 1.0f; //how fast the trash bags spawn - the lower the faster 
	float obstacleSpeed = 4.0f; //how fast the obstacles scroll down the screen 
	Texture obstacleTexture("images/trash bag.png");
	ObstacleManager obstacles(obstacleTexture, windowSize, spawnInterval, obstacleSpeed);

	
	Texture carTexture("images/car.png"); //texture sourced from -- https://www.youtube.com/watch?v=YzhhVHb0WVY
	float carSpeed = 5.0f;
	Car playerCar(carTexture, windowSize, carSpeed);


	Vector2f bgScale(2.0f, 4.0f);
	float scrollSpeed = 4.0f;
	int score = 0;
	float scoreTimer = 0.0f;
	Texture bgTexture("images/top down road 1.png"); //texture sourced from -- 
	Background background(bgTexture, windowSize, bgScale, scrollSpeed);
    // Create AI player
    AIPlayer aiPlayer(carTexture, windowSize);

	GameState gameState = GameState::Playing;

	Clock counter; //track the time


	//main game loop
	while (window.isOpen()) {


		Time changeTime = counter.restart(); //starts the timer back to 0
		float changeSeconds = changeTime.asSeconds();
		/* This could also be used for a time based scoring system
		Example: Every 10 second the player gets an additional 100 points */

		//exit program
		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>()) {
				window.close();
			}

		}


		if (gameState == GameState::Playing) {

			playerCar.update();
			background.update();
			obstacles.update(changeSeconds);

			//drawing all of the elements onto the window
			window.clear();
			background.draw(window);
			obstacles.draw(window);
			playerCar.draw(window);
      aiPlayer.draw(window);
			window.display();

			playerCar.checkCollision(obstacles, gameState);


			// System to count the score over time
			scoreTimer += changeSeconds;
			if(scoreTimer >= 1.0f) {
				score +=10;
				scoreTimer= 0.0f;
		}

		}
		else if (gameState == GameState::EndScreen) {

			window.clear();


			Font font;
			font.openFromFile("fonts/ByteBounce.ttf"); //font sourced from - https://www.1001fonts.com/bytebounce-font.html

			Text gameOver(font);
			gameOver.setString("Game Over!\nScore: " + std::to_string(score) + "\nPress R to restart");
			gameOver.setCharacterSize(40);
			gameOver.setFillColor(Color::White);

			FloatRect textBounds = gameOver.getLocalBounds();
			gameOver.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 });
			gameOver.setPosition({ static_cast<float>(window.getSize().x / 2.f), static_cast<float>(window.getSize().y / 2.f) });


			window.draw(gameOver);
			window.display();
			// Displaying the Score at the end of the game
			Font font;
			font.loadfromfile("fonts/ByteBounce.tff);
			Text scoreText;
			scoreText.setFont(font);
			scoreText.setCharacterSize(24);
			scoreText.setFillColor(Color::White);
			scoreText.setString("Score: " + std::to_string(score));
			scoreText.setPosition(10.f,10.f);
			window.draw(scoreText);

			if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
				
				gameState = GameState::Playing;
				playerCar.restart();
				background.restart();
				obstacles.restart();
				
			}

			continue;

		}
		
	}



	return 0;

}
