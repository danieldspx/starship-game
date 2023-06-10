//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_SCENEMANAGER_H
#define VECTORGRAPHICS_SCENEMANAGER_H

#include <random>
#include "base/interfaces/IMouse.h"
#include "base/interfaces/IRender.h"
#include "base/interfaces/IKeyboard.h"
#include "actors/Spaceship.h"

#define LANE_POINTS 100

class SceneManager: public IRender, public IKeyboard{
public:
    SceneManager(float worldWidth, float worldHeight);

    float baseHeight, speedY;
    int keyPressed;
    bool isKeyPressed;

    Spaceship* spaceship;
    // Max and Min in the lanes in the X axes so
    // we do not allow the spaceship to pass it
    float leftLaneMax, rightLaneMin;
    fvec2* leftLane;
    fvec2* rightLane;

    void render(float screenWidth, float screenHeight, float dt) override;

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    void renderLanes(float screenWidth, float screenHeight);
};


#endif //VECTORGRAPHICS_SCENEMANAGER_H
