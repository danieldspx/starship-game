//
// Created by daniel on 10/06/23.
//

#include "Bullet.h"
#include "../gl_canvas2d.h"

Bullet::Bullet(fvec2 position, float speed, float damage, int color): position(position), speed(speed), damage(damage), color(color) {

}

void Bullet::render(float screenWidth, float screenHeight, float dt) {
    position.y += speed * dt;

    renderBullet();
}

void Bullet::renderBullet() {
    auto minBoundary = getLeftDownBoundary();
    auto maxBoundary = getRightUpBoundary();
    CV::color(color);
    CV::rectFill(minBoundary, maxBoundary);
}

fvec2 Bullet::getLeftDownBoundary() {
    return fvec2{position.x - width/2, position.y};
}

fvec2 Bullet::getRightUpBoundary() {
    auto minBoundary = getLeftDownBoundary();
    return fvec2{minBoundary.x + width, minBoundary.y + height};
}

bool Bullet::isIntersecting(fvec2 position) {
    return false;
}

fvec2 Bullet::getLeftUpBoundary() {
    return fvec2{position.x - width/2, position.y + height};
}

fvec2 Bullet::getRightDownBoundary() {
    auto minBoundary = getLeftDownBoundary();
    return fvec2{minBoundary.x + width, minBoundary.y};
}
