//
// Created by daniel on 10/06/23.
//

#include "Bullet.h"
#include "../gl_canvas2d.h"

Bullet::Bullet(fvec2 position, float speed): position(position), speed(speed) {

}

void Bullet::render(float screenWidth, float screenHeight, float dt) {
    position.y += speed * dt;

    renderBullet();
}

void Bullet::renderBullet() {
    auto minBoundary = getMinBoundary();
    auto maxBoundary = getMaxBoundary();
    CV::color(8);
    CV::rectFill(minBoundary, maxBoundary);
}

fvec2 Bullet::getMinBoundary() {
    return fvec2{position.x - width/2, position.y};
}

fvec2 Bullet::getMaxBoundary() {
    auto minBoundary = getMinBoundary();
    return fvec2{minBoundary.x + width, minBoundary.y + height};
}

bool Bullet::isIntersecting(fvec2 position) {
    return false;
}
