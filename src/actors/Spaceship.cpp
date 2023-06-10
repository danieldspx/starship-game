//
// Created by daniel on 10/06/23.
//

#include "Spaceship.h"
#include "../gl_canvas2d.h"

Spaceship::Spaceship(fvec2 initialPosition, float radius, float leftBoundary, float rightBoundary): position(initialPosition), radius(radius), leftBoundary(leftBoundary), rightBoundary(rightBoundary) {
    speedX = 150;
}

bool Spaceship::isIntersecting(fvec2 p) {
    return position.distance(p) <= radius;
}

void Spaceship::keyboardDown(int key) {
    keyPressed = key;
    isKeyPressed = true;
}

void Spaceship::keyboardUp(int key) {
    if (keyPressed == key) isKeyPressed = false;
}

void Spaceship::render(float screenWidth, float screenHeight, float dt) {
    if (isKeyPressed) {
        handleKeyPressed(keyPressed, dt);
    }

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

void Spaceship::handleKeyPressed(int key, float dt) {
    switch (key) {
        // Move left or right
        case 200:
        case 202:
            float distance = speedX * dt;
            position.x += keyPressed == 200 ? -distance : distance;
            // Make sure that the spaceship does not go over the right boundary
            if (position.x + radius > rightBoundary) {
                position.x = rightBoundary - radius;
            }
            // Make sure that the spaceship does not go over the left boundary
            if (position.x - radius < leftBoundary) {
                position.x = leftBoundary + radius;
            }
            break;
    }
}
