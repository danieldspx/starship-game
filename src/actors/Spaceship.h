//
// Created by daniel on 10/06/23.
//

#ifndef CANVAS_CLION_SPACESHIP_H
#define CANVAS_CLION_SPACESHIP_H


#include "../base/interfaces/IEntity.h"

class Spaceship: public IEntity {
public:
    fvec2 position;
    float radius;

    Spaceship(fvec2 initialPosition, float radius);

    bool isIntersecting(fvec2 p) override;

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    void render(float screenWidth, float screenHeight, float dt, float baseHeight) override;

    void renderSpaceship();
};


#endif //CANVAS_CLION_SPACESHIP_H
