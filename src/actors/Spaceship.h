//
// Created by daniel on 10/06/23.
//

#ifndef CANVAS_CLION_SPACESHIP_H
#define CANVAS_CLION_SPACESHIP_H


#include "../base/interfaces/IEntity.h"

class Spaceship: public IEntity {
public:
    fvec2 position;
    int keyPressed;
    bool isKeyPressed;
    float speedX;
    float leftBoundary, rightBoundary, radius;

    Spaceship(fvec2 initialPosition, float radius, float leftBoundary, float rightBoundary);

    bool isIntersecting(fvec2 p) override;

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    void render(float screenWidth, float screenHeight, float dt) override;

    void renderSpaceship();

    void handleKeyPressed(int key, float dt);
};


#endif //CANVAS_CLION_SPACESHIP_H
