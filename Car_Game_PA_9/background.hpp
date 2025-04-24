
#include "header.hpp"


class Background : public ObjectManager{

public:

	Background(Texture& newTexture, Vector2u newWindowSize, Vector2f newbgScale, float newScrollSpeed) :
		ObjectManager(newTexture, newWindowSize, newScrollSpeed) {
	
		this->bgScale = newbgScale;
		this->bgHeight = this->texture.getSize().y * this->bgScale.y;

	
		//creating the sprites -- These will loop together to create the illusion of a moving road
		Sprite bg1(this->texture);
		Sprite bg2(this->texture);

		//scale the background -- original png doesnt fit the window
		bg1.setScale(this->bgScale);
		bg2.setScale(this->bgScale);

		//set the intial positions of the backgrounds
		bg1.setPosition({ 0.f, 0.f });
		bg2.setPosition({ 0.f, this->bgHeight });

		//add these to the background vector
		this->backgrounds.push_back(bg1);
		this->backgrounds.push_back(bg2);
	}

	void update() override;
	void draw(RenderWindow& window) override;
	void restart() override;
private:
	
	vector<Sprite> backgrounds; //multiple backgrounds to create the illusion of movement


	Vector2f bgScale; //scale to so that the vector fits the window properly
	float bgHeight; //height of the scaled vector
};