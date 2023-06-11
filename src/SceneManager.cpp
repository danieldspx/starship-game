//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "gl_canvas2d.h"
#include "base/Utils.h"

SceneManager::SceneManager(float worldWidth, float worldHeight, float screenWidth, float screenHeight) {
    arrowKeyPressed = 0;
    isArrowKeyPressed = false;
    speedY = 350;
    currentLevel = 0;

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

    initLevels(worldHeight, screenHeight);
}

void SceneManager::initLevels(float worldHeight, float screenHeight) {
    levels[1] = {LevelDescriptor{1, 10}};
    levelsHeightTrigger[1] = screenHeight;

    levels[2] = {LevelDescriptor{1, 3}};
    levelsHeightTrigger[2] = screenHeight * 2;

    levels[3] = {};
    levelsHeightTrigger[3] = screenHeight * 3;

    endLevel = 3;
}

void SceneManager::render(float screenWidth, float scrHeight, float dt) {
    screenHeight = scrHeight;
    CV::clear(0,0,0);
    if (isArrowKeyPressed) {
        handleKeyPressed(arrowKeyPressed, dt);
    }
    renderLanes(screenWidth, screenHeight);

    spaceship->render(screenWidth, screenHeight, dt);

    for (auto monster: monsters) {
        monster->render(screenWidth, screenHeight, dt);
    }
}

void SceneManager::handleKeyPressed(int key, float dt) {
    switch (key) {
        case 201:
        case 203:
            float distance = speedY * dt;
            if (arrowKeyPressed == 201) {
                updateHeight(baseHeight + distance);
            } else {
                updateHeight(baseHeight - distance);
            }
            break;
    }
}

void SceneManager::updateHeight(float newHeight) {
    int levelIndex = currentLevel + 1 > endLevel ? endLevel : currentLevel + 1;
    if (levelsHeightTrigger[levelIndex] < newHeight) {
        setLevel(levelIndex);
    }
    baseHeight = newHeight;
}

void SceneManager::setLevel(int level) {
    currentLevel = level;
    if (DEBUG) printf("\nNew level %d", currentLevel);
    if (currentLevel == endLevel) {
        return;
    }
    float laneWidth = rightLaneMin - leftLaneMax;
    for (auto levelDescriptor: levels[currentLevel]) {
        float monsterRadius = Monster::getMonsterRadius(levelDescriptor.monsterType);
        for (int i = 0; i < levelDescriptor.quantity; i++) {
            float posX = monsterRadius + i*monsterRadius*4;
            fvec2 pos = fvec2{leftLaneMax + Utils::modularReduction(posX, laneWidth), screenHeight - 2*monsterRadius - 2*monsterRadius*floor(posX/laneWidth)};
            if (DEBUG) printf("\nMonster position: (%f, %f)\n", pos.x, pos.y);
            monsters.push_back(new Monster(pos, levelDescriptor.monsterType, leftLaneMax, rightLaneMin));
        }
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
