/*

Names: Iyke Odum, Austin Daniels, Kadara Tandia
Assignment: Programming Assignment 9
Professor: Andrew O'Fallon
Due: 4/23/2025
Description: For this final assignment, we are required to create a solution, as a team,
to a game or graphical application of our choice

UPDATES NEEDED:

-create main menu (button to play the game and button for customization)
-allow customization of car? (change color)


UPDATES COMPLETED:
-create classes for car
-created obstacles
-class for background
-scrolling background
-moving car
-score system (time based or number of obstacles dodged based)
-create end screen (display score)


*/

#include "background.hpp"
#include "car.hpp"
#include "aiplayer.hpp"

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
	float carSpeed = 5.0f; //cars speed
	Car playerCar(carTexture, windowSize, carSpeed);


	Vector2f bgScale(2.0f, 4.0f); //scaling the background to fit the window
	float scrollSpeed = 4.0f; //speed that the background scrolls at
	Texture bgTexture("images/top down road 1.png"); //texture sourced from -- https://opengameart.org/content/2d-top-down-highway-background
	Background background(bgTexture, windowSize, bgScale, scrollSpeed);

	int score = 0; //game score
	float scoreTimer = 0.0f; //timer
	
    // Create AI player
    AIPlayer aiPlayer(carTexture, windowSize);

	//GameState -- tracks which action to perform based on the game state (Menu option will be added in the future)
	GameState gameState = GameState::Playing;

	Clock counter; //track the time

	//main font to be used throughout the game
	Font font("fonts/ByteBounce.ttf");  //font sourced from - https://www.1001fonts.com/bytebounce-font.html


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

			/* Update function: The update functions is responsible for moving all of the objects every frame
			Note: obstacle class doesnt inherit from the object manager which is why it is able to take a 
			parameter of time. This can and will be fixed in the future for more dynamic gameplay
			*/
			playerCar.update();
			background.update();
			obstacles.update(changeSeconds);

			
			window.clear();

			/*Draw function: This functions is responisble for drawing all of the elements on the screen each frame */
			background.draw(window);
			obstacles.draw(window);
			playerCar.draw(window);
      aiPlayer.draw(window);

			//Displays Score during the game
			Text scoreTopRight(font);
	 // reuse the same font already loaded
			scoreTopRight.setCharacterSize(24);
			scoreTopRight.setFillColor(Color::White);
			scoreTopRight.setString("Score: " + std::to_string(score));

			// Align to top-right corner
			FloatRect bounds = scoreTopRight.getLocalBounds();
			scoreTopRight.setOrigin({ bounds.size.x, 0 }); // anchor to the right edge
			scoreTopRight.setPosition({ static_cast<float>(window.getSize().x - 10), 10.f });

			window.draw(scoreTopRight);

			window.display();

			//checks to see if the player hit obstacles
			playerCar.checkCollision(obstacles, gameState);

			// System to count the score over time
			scoreTimer += changeSeconds;
			if(scoreTimer >= 1.0f) {
				score +=10;
				scoreTimer= 0.0f;
		}

		}
		else if (gameState == GameState::EndScreen) { //if the player collides into an obstacle

			//clear all the previous elements
			window.clear();

			Text gameOver(font);
			gameOver.setString("Game Over!\nScore: " + to_string(score) + "\nPress Space to restart");
			gameOver.setCharacterSize(40);
			gameOver.setFillColor(Color::White);

			FloatRect textBounds = gameOver.getLocalBounds(); 
			gameOver.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 }); 

			//game over text set at middle of the screen
			gameOver.setPosition({ static_cast<float>(window.getSize().x / 2.f), static_cast<float>(window.getSize().y / 2.f) });


			window.draw(gameOver);
			window.display();

			// Displaying the Score at the end of the game
			Text scoreText(font);
			scoreText.setCharacterSize(24);
			scoreText.setFillColor(Color::White);
                        
			scoreText.setString("Score: " + to_string(score));
			scoreText.setPosition({ 10.f,10.f });

			window.draw(scoreText);

			if (Keyboard::isKeyPressed(Keyboard::Key::Space)) { //Space for restart
				
				gameState = GameState::Playing;

				/* Restart Function: This function is reponsible for clearing/reseting 
				all of the elements on the screen */
				playerCar.restart();
				background.restart();
				obstacles.restart();
				score = 0;
				
			}

			continue;

		}
		
	}



	return 0;
}
