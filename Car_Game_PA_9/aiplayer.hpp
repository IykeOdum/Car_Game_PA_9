#include "header.hpp"

// The AIPlayer class represents an autonomous car that can avoid obstacles by switching lanes.
class AIPlayer {
public:
    // Constructor: initializes the car with texture and window size
    AIPlayer(const Texture& carTexture, Vector2u windowSize);

    // Updates the car's position and makes lane decisions based on obstacles and time
    void update(const vector<Sprite>& obstacles, float deltaTime);

    // Returns a reference to the car sprite (useful for rendering or collision checking)
    Sprite& getSprite();

    // Draws the car on the provided render window
    void draw(RenderWindow& window);

private:
    Sprite car;               // The graphical representation of the AI car
    float speed;              // Movement speed of the car
    Vector2u windowSize;      // Size of the game window (used for lane calculation)

    float reactionDistance;   // Distance at which the AI starts reacting to obstacles
    float avoidanceDistance;  // Reserved for future use to avoid obstacles more dynamically
    float decisionCooldown;   // Time between consecutive decisions (lane changes)
    float currentCooldown;    // Countdown timer until the next decision is allowed
    int currentLane;          // The current lane the car is in (0 = left, 1 = middle, 2 = right)

    // Calculates the target position of the car in a given lane
    Vector2f getLanePosition(int lane);

    // Determines the best lane to move to, based on obstacle positions
    int chooseBestLane(const vector<Sprite>& obstacles);
};      