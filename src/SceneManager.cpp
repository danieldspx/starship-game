//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "gl_canvas2d.h"
#include "base/Utils.h"

SceneManager::SceneManager(float worldWidth, float worldHeight, float screenWidth, float scrHeight) {
    arrowKeyPressed = 0;
    isArrowKeyPressed = false;
    speedY = 350;
    currentLevel = 0;
    screenHeight = scrHeight;
    gameEnded = false;
    gameWon = false;

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

    addBulletsFn = [&](Bullet* bullet){
        this->monsterBullets.push_back(bullet);
    };

    initLevels(worldHeight, screenHeight);
}

void SceneManager::initLevels(float worldHeight, float scrHeight) {
    levels[1] = {LevelDescriptor{1, 10}};
    levelsHeightTrigger[1] = scrHeight;

    levels[2] = {LevelDescriptor{1, 3}, LevelDescriptor{2, 5}};
    levelsHeightTrigger[2] = screenHeight * 2;

    levels[3] = {LevelDescriptor{2, 8}, LevelDescriptor{1, 5}};
    levelsHeightTrigger[3] = screenHeight * 3;

    levels[4] = {LevelDescriptor{2, 8}, LevelDescriptor{1, 5}};
    levelsHeightTrigger[4] = screenHeight * 5;

    levels[5] = {LevelDescriptor{2, 5}, LevelDescriptor{1, 5}};
    levelsHeightTrigger[5] = screenHeight * 7;

    levels[6] = {LevelDescriptor{2, 6}};
    levelsHeightTrigger[6] = screenHeight * 8;

    levels[7] = {LevelDescriptor{2, 6}};
    levelsHeightTrigger[7] = screenHeight * 9;

    levels[8] = {};
    levelsHeightTrigger[8] = screenHeight * 10;

    endLevel = 8;
}

void SceneManager::render(float screenWidth, float scrHeight, float dt) {
    screenHeight = scrHeight;
    CV::clear(0,0,0);

    if (gameEnded) {
        CV::color(1,0,0);
        CV::text(0, scrHeight/2, "You were killed, please restart to play again.");
        return;
    }

    if (gameWon) {
        CV::color(1,0,0);
        CV::text(0, scrHeight/2, "You won the game, congratulations!!");
        CV::text(0, scrHeight/2 - 100, "Please restart if you want to play again.");
        return;
    }

    if (isArrowKeyPressed) {
        handleKeyPressed(arrowKeyPressed, dt);
    }
    renderLanes(screenWidth, screenHeight);

    spaceship->render(screenWidth, screenHeight, dt);

    for (auto itMonster = monsters.begin(); itMonster != monsters.end();) {
        if ((*itMonster)->isAlive()) {
            (*itMonster)->render(screenWidth, screenHeight, dt);
            itMonster++;
        } else {
            delete *itMonster;
            itMonster = monsters.erase(itMonster);
        }
    }

    for (auto it = monsterBullets.begin(); it != monsterBullets.end();) {
        (*it)->render(screenWidth, screenHeight, dt);

        if ((*it)->getRightUpBoundary().y < 0) {
            delete *it; // Free the memory occupied by the bullet
            it = monsterBullets.erase(it); // Remove the bullet from the vector and update the iterator
            if (DEBUG) {
                printf("Removed Monster Bullet instance\n");
            }
        } else {
            ++it; // Move to the next bullet
        }
    }

    checkBulletsHits();
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
    // We do not allow moving back or forward when there are monsters,
    // the user should fight the monsters before moving. The idea
    // is to not allow the user to run away from them.
    if (!monsters.empty()) {
        return;
    }
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
        gameWon = true;
        if (DEBUG) printf("\nGame won %d");
        return;
    }
    float laneWidth = rightLaneMin - leftLaneMax;
    float posAcc = 0;
    for (auto levelDescriptor: levels[currentLevel]) {
        float monsterRadius = Monster::getMonsterRadius(levelDescriptor.monsterType);
        for (int i = 0; i < levelDescriptor.quantity; i++) {
            float posX = posAcc + monsterRadius + i*monsterRadius*4;
            fvec2 pos = fvec2{leftLaneMax + Utils::modularReduction(posX, laneWidth), screenHeight - 2*monsterRadius - 2*monsterRadius*floor(posX/laneWidth)};
            if (DEBUG) printf("\nMonster position: (%.2f, %.2f)", pos.x, pos.y);
            monsters.push_back(new Monster(pos, levelDescriptor.monsterType, leftLaneMax, rightLaneMin, addBulletsFn));

            if (i + 1 >= levelDescriptor.quantity) {
                posAcc += posX + monsterRadius;
            }
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

void SceneManager::renderLanes(float _screenWidth, float _screenHeight) {
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

void SceneManager::checkBulletsHits() {
    for (auto itBullet = spaceship->bullets.begin(); itBullet != spaceship->bullets.end();) {
        auto bullet = *itBullet;
        bool bulletRemoved = false;
        for (auto itMonster = monsters.begin(); itMonster != monsters.end();) {
            auto monster = *itMonster;
            if (
                monster->isIntersecting(bullet->getLeftDownBoundary()) ||
                monster->isIntersecting(bullet->getLeftUpBoundary()) ||
                monster->isIntersecting(bullet->getRightDownBoundary()) ||
                monster->isIntersecting(bullet->getRightUpBoundary()) ||
                monster->isIntersecting(bullet->position)
            ) {
                delete *itBullet; // Free the memory occupied by the bullet
                monster->hit(bullet->damage);
                itBullet = spaceship->bullets.erase(itBullet); // Remove the bullet from the vector and update the iterator
                bulletRemoved = true;
                if (DEBUG) {
                    printf("\nBullet intercepted monster\n");
                }
                break;
            } else {
                itMonster++;
            }
        }
        if (!bulletRemoved) itBullet++;
    }

    // Check if monster bullets hits spaceship
    for (auto itBullet = monsterBullets.begin(); itBullet != monsterBullets.end();) {
        auto bullet = *itBullet;
        bool bulletRemoved = false;
        if (
            spaceship->isIntersecting(bullet->getLeftDownBoundary()) ||
            spaceship->isIntersecting(bullet->getRightDownBoundary()) ||
            spaceship->isIntersecting(bullet->getLeftUpBoundary()) ||
            spaceship->isIntersecting(bullet->getRightUpBoundary()) ||
            spaceship->isIntersecting(bullet->position)
        ) {
            delete *itBullet; // Free the memory occupied by the bullet
            spaceship->hit(bullet->damage);
            if (spaceship->health <= 0) {
                // Ends the game
                gameEnded = true;
            }
            itBullet = monsterBullets.erase(itBullet); // Remove the bullet from the vector and update the iterator
            bulletRemoved = true;
            if (DEBUG) {
                printf("\nBullet has hit spaceship\n");
            }
        }
        if (!bulletRemoved) itBullet++;
    }
}
