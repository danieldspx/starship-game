//
// Created by daniel on 10/06/23.
//

#ifndef CANVAS_CLION_BULLET_H
#define CANVAS_CLION_BULLET_H


#include "../base/interfaces/IRender.h"
#include "../base/vectors/Vector2D.h"
#include "../base/interfaces/IIntersect.h"

class Bullet: public IRender, public IIntersect {
public:
    fvec2 position;
    float speed;
    float height = 15, width = 5;
    float damage = 10;

    Bullet(fvec2 position, float speed);

    void render(float screenWidth, float screenHeight, float dt) override;

    bool isIntersecting(fvec2 position) override;

    void renderBullet();

    fvec2 getLeftDownBoundary();

    fvec2 getLeftUpBoundary();

    fvec2 getRightUpBoundary();

    fvec2 getRightDownBoundary();
};


#endif //CANVAS_CLION_BULLET_H
