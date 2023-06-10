//
// Created by daniel on 10/06/23.
//

#include "Spaceship.h"
#include "../gl_canvas2d.h"

Spaceship::Spaceship(fvec2 initialPosition, float radius): position(initialPosition), radius(radius) {}

bool Spaceship::isIntersecting(fvec2 p) {
    return position.distance(p) <= radius;
}

void Spaceship::keyboardDown(int key) {

}

void Spaceship::keyboardUp(int key) {

}

void Spaceship::render(float screenWidth, float screenHeight, float dt, float baseHeight) {
    renderSpaceship();
}

void Spaceship::renderSpaceship() {
    float ang = PI/2;
    if (DEBUG) {
        CV::color(1, 0, 0);
        CV::circle(position, radius, 50, ang);
    }
    CV::color(0, 1, 0);
    CV::circleFill(position, radius, 3, ang);
}
