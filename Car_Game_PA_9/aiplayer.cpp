// aiplayer.cpp
#include "aiplayer.hpp"

// Constructor initializes the AI car with texture, position, and movement parameters
AIPlayer::AIPlayer(const Texture& carTexture, Vector2u windowSize) : 
    windowSize(windowSize), speed(4.0f), reactionDistance(300.0f),
    avoidanceDistance(150.0f), decisionCooldown(0.5f), currentCooldown(0.0f),
    currentLane(1) {
    
    car.setTexture(carTexture); // Set the car texture
    car.setPosition(windowSize.x / 2 - car.getGlobalBounds().width / 2, 100); // Start at top-center
    car.setScale(0.1f, 0.1f); // Scale down the car
}

// Update method: updates the car's position based on obstacle positions and time elapsed
void AIPlayer::update(const vector<Sprite>& obstacles, float deltaTime) {
    currentCooldown -= deltaTime; // Decrease the cooldown timer
    
    if (currentCooldown <= 0) {
        // Time to reassess best lane based on obstacle positions
        currentLane = chooseBestLane(obstacles);
        currentCooldown = decisionCooldown; // Reset decision cooldown
    }
    
    // Calculate target position in current lane
    Vector2f targetPosition = getLanePosition(currentLane);
    Vector2f direction = targetPosition - car.getPosition(); // Direction vector to target position
    
    // Normalize direction vector to ensure consistent speed
    if (direction.x != 0 || direction.y != 0) {
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;
    }
    
    car.move(direction * speed); // Move car towards target
}

// Returns a reference to the car sprite for collision checking or rendering
Sprite& AIPlayer::getSprite() {
    return car;
}

// Draws the car to the given render window
void AIPlayer::draw(RenderWindow& window) {
    window.draw(car);
}

// Computes the center X position of a lane and returns the position for the car to move towards
Vector2f AIPlayer::getLanePosition(int lane) {
    float laneWidth = windowSize.x / 3; // Divide window into 3 lanes
    float x = laneWidth * (0.5f + lane); // Compute center of the specified lane
    return Vector2f(x - car.getGlobalBounds().width / 2, car.getPosition().y); // Return position aligned to center
}

// Determines the best lane to avoid obstacles
int AIPlayer::chooseBestLane(const vector<Sprite>& obstacles) {
    // Initialize all lanes as safe
    array<bool, 3> laneSafe = {true, true, true};
    
    // Loop through all obstacles to check if any are within reaction distance in each lane
    for (const auto& obstacle : obstacles) {
        if (obstacle.getPosition().y > car.getPosition().y + reactionDistance) {
            continue; // Ignore obstacles too far ahead or behind
        }
        
        // Determine the lane index of the obstacle based on its X position
        float obstacleX = obstacle.getPosition().x + obstacle.getGlobalBounds().width / 2;
        int obstacleLane = static_cast<int>(obstacleX / (windowSize.x / 3));
        
        // If the obstacle is in a valid lane, mark it as unsafe
        if (obstacleLane >= 0 && obstacleLane <= 2) {
            laneSafe[obstacleLane] = false;
        }
    }
    
    // Prefer to stay in the current lane if it's safe
    if (laneSafe[currentLane]) {
        return currentLane;
    }
    
    // Try to switch to an adjacent safe lane
    if (currentLane > 0 && laneSafe[currentLane - 1]) {
        return currentLane - 1;
    }
    if (currentLane < 2 && laneSafe[currentLane + 1]) {
        return currentLane + 1;
    }
    
    // No safe lanes found, choose a random one
    return rand() % 3;
}
     