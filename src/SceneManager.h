//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_SCENEMANAGER_H
#define VECTORGRAPHICS_SCENEMANAGER_H

#include <random>
#include <map>
#include <vector>
#include "base/interfaces/IMouse.h"
#include "base/interfaces/IRender.h"
#include "base/interfaces/IKeyboard.h"
#include "actors/Spaceship.h"
#include "actors/Monster.h"

#define LANE_POINTS 100

class SceneManager: public IRender, public IKeyboard{
public:
    struct LevelDescriptor {
        int monsterType;
        int quantity;
    };

    SceneManager(float worldWidth, float worldHeight, float screenWidth, float screenHeight);

    int currentLevel;
    int endLevel;

    float baseHeight, speedY, screenHeight;
    int arrowKeyPressed;
    bool isArrowKeyPressed;

    std::map<int, std::vector<LevelDescriptor>> levels;
    std::map<int, float> levelsHeightTrigger;
    std::vector<Monster*> monsters;

    Spaceship* spaceship;
    // Max and Min in the lanes in the X axes so
    // we do not allow the spaceship to pass it
    float leftLaneMax, rightLaneMin;
    fvec2* leftLane;
    fvec2* rightLane;

    void render(float screenWidth, float screenHeight, float dt) override;

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    void handleKeyPressed(int key, float dt);

    void renderLanes(float screenWidth, float screenHeight);

    void initLevels(float worldHeight, float screenHeight);

    void updateHeight(float newHeight);

    void setLevel(int level);
};


#endif //VECTORGRAPHICS_SCENEMANAGER_H
