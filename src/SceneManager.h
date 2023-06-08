//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_SCENEMANAGER_H
#define VECTORGRAPHICS_SCENEMANAGER_H

#include <random>
#include "base/interfaces/IMouse.h"
#include "base/interfaces/IRender.h"
#include "base/interfaces/IKeyboard.h"

#define LANE_POINTS 100

class SceneManager: public IRender, public IKeyboard{
public:
    float baseHeight, speedY;
    int keyPressed;
    bool isKeyPressed;

    fvec2* leftLane;
    fvec2* rightLane;

    void render(int screenWidth, int screenHeight) override;

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    void renderLanes();

    SceneManager(float worldWidth, float worldHeight) {
        keyPressed = 0;
        isKeyPressed = false;
        baseHeight = 0;
        speedY = 2.5;

        leftLane = new fvec2[LANE_POINTS];
        rightLane = new fvec2[LANE_POINTS];

        std::random_device rd;  // Seed for the random number engine
        std::mt19937 rng(rd()); // Mersenne Twister random number engine

        // Define the range for random numbers
        float xRange = 50;
        // Increment in the Y axes
        float stepY = (worldHeight / LANE_POINTS);

        // Create a uniform distribution
        std::uniform_real_distribution<float> distribution(0, xRange);
        for (int i = 0; i < LANE_POINTS; i++) {
            // Generate random position in the X axes to make the curves
            leftLane[i] = fvec2{distribution(rng) , stepY * static_cast<float>(i)};
            rightLane[i] = fvec2{(worldWidth - xRange) + distribution(rng) , (worldHeight / LANE_POINTS) * static_cast<float>(i)};
        }
    }
};


#endif //VECTORGRAPHICS_SCENEMANAGER_H
