//
// Created by daniel on 10/06/23.
//

#ifndef CANVAS_CLION_SPACESHIP_H
#define CANVAS_CLION_SPACESHIP_H


#include <vector>
#include <chrono>
#include "../base/interfaces/IEntity.h"
#include "Bullet.h"

class Spaceship: public IEntity {
public:
    fvec2 position;
    int arrowKeyPressed;
    bool isArrowKeyPressed;
    float speedX;
    float leftBoundary, rightBoundary, radius;
    std::chrono::milliseconds firerate;
    std::chrono::high_resolution_clock::time_point lastShoot;
    std::vector<Bullet*> bullets;

    Spaceship(fvec2 initialPosition, float radius, float leftBoundary, float rightBoundary);

    bool isIntersecting(fvec2 p) override;

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    void render(float screenWidth, float screenHeight, float dt) override;

    void renderSpaceship();

    void handleKeyPressed(int key, float dt);

    void handleKeyUp(int key);

    void shootBullet();
};


#endif //CANVAS_CLION_SPACESHIP_H
