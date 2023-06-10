//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "gl_canvas2d.h"
#include "base/Utils.h"

SceneManager::SceneManager(float worldWidth, float worldHeight) {
    arrowKeyPressed = 0;
    isArrowKeyPressed = false;
    speedY = 350;

    leftLane = new fvec2[LANE_POINTS];
    rightLane = new fvec2[LANE_POINTS];

    std::random_device rd;  // Seed for the random number engine
    std::mt19937 rng(rd()); // Mersenne Twister random number engine

    // Define the range for random numbers
    float xRange = 50;
    // Increment in the Y axes
    float stepY = (worldHeight / LANE_POINTS);
    baseHeight = 2*stepY;

    // Create a uniform distribution
    std::uniform_real_distribution<float> distribution(0, xRange);
    for (int i = 0; i < LANE_POINTS; i++) {
        // Generate random position in the X axes to make the curves
        leftLane[i] = fvec2{distribution(rng) , stepY * static_cast<float>(i)};
        rightLane[i] = fvec2{(worldWidth - xRange) + distribution(rng) , (worldHeight / LANE_POINTS) * static_cast<float>(i)};

        if (i == 0) {
            leftLaneMax = leftLane[i].x;
            rightLaneMin = rightLane[i].x;
        }

        if (leftLaneMax < leftLane[i].x) leftLaneMax = leftLane[i].x;
        if (rightLaneMin > rightLane[i].x) rightLaneMin = rightLane[i].x;
    }

    float spaceshipRadius = 20;
    spaceship = new Spaceship(fvec2{worldWidth/2, 25}, spaceshipRadius, leftLaneMax, rightLaneMin);
}

void SceneManager::render(float screenWidth, float screenHeight, float dt) {
    CV::clear(0,0,0);
    if (isArrowKeyPressed) {
        handleKeyPressed(arrowKeyPressed, dt);
    }
    renderLanes(screenWidth, screenHeight);

    spaceship->render(screenWidth, screenHeight, dt);
}

void SceneManager::handleKeyPressed(int key, float dt) {
    switch (key) {
        case 201:
        case 203:
            float distance = speedY * dt;
            baseHeight += arrowKeyPressed == 201 ? distance : -distance ;
            break;
    }
}

void SceneManager::keyboardDown(int key) {
    if (200 <= key && key <= 203) {
        arrowKeyPressed = key;
        isArrowKeyPressed = true;
    }

    spaceship->keyboardDown(key);
}

void SceneManager::keyboardUp(int key) {
    if (arrowKeyPressed == key && 200 <= key && key <= 203) isArrowKeyPressed = false;

    spaceship->keyboardUp(key);
}

void SceneManager::renderLanes(float screenWidth, float screenHeight) {
    if (DEBUG) {
        CV::color(0, 0, 1);
        CV::line(leftLaneMax, 0, leftLaneMax, screenHeight);
        CV::line(rightLaneMin, 0, rightLaneMin, screenHeight);
    }
    for (int p = 0; p + 3 < LANE_POINTS; p++) {
        for (float t = 0; t <= 1; t += 0.01) {
            CV::color(3);
            fvec2 leftPoint = Utils::bspline(leftLane, t, p, LANE_POINTS);
            fvec2 rightPoint = Utils::bspline(rightLane, t, p, LANE_POINTS);

            leftPoint.y -= baseHeight;
            rightPoint.y -= baseHeight;

            CV::point(leftPoint);
            CV::point(rightPoint);
        }
    }
}
