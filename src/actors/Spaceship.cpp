//
// Created by daniel on 10/06/23.
//

#include "Spaceship.h"
#include "../gl_canvas2d.h"

Spaceship::Spaceship(fvec2 initialPosition, float radius, float leftBoundary, float rightBoundary): position(initialPosition), radius(radius), leftBoundary(leftBoundary), rightBoundary(rightBoundary) {
    speedX = 150;
    lastShoot= std::chrono::high_resolution_clock::now();
    firerate = std::chrono::milliseconds(300);
}

bool Spaceship::isIntersecting(fvec2 p) {
    return position.distance(p) <= radius;
}

void Spaceship::keyboardDown(int key) {
    // Key V does not interfer
    if (200 <= key && key <= 203) {
        arrowKeyPressed = key;
        isArrowKeyPressed = true;
    }
}

void Spaceship::keyboardUp(int key) {
    if (arrowKeyPressed == key && 200 <= key && key <= 203) isArrowKeyPressed = false;

    handleKeyUp(key);
}

void Spaceship::render(float screenWidth, float screenHeight, float dt) {
    if (isArrowKeyPressed) {
        handleKeyPressed(arrowKeyPressed, dt);
    }

    for (auto it = bullets.begin(); it != bullets.end(); ) {
        (*it)->render(screenWidth, screenHeight, dt);

        if ((*it)->getMinBoundary().y > screenHeight) {
            delete *it; // Free the memory occupied by the bullet
            it = bullets.erase(it); // Remove the bullet from the vector and update the iterator
            if (DEBUG) {
                printf("Removed Bullet instance\n");
            }
        } else {
            ++it; // Move to the next bullet
        }
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
            position.x += arrowKeyPressed == 200 ? -distance : distance;
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

void Spaceship::handleKeyUp(int key) {
    // Key is V
    if (key == 86 || key == 118) {
        shootBullet();
    }
}

void Spaceship::shootBullet() {
    auto now = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastShoot).count() >= firerate.count()) {
        bullets.push_back(new Bullet(position, 200));
        lastShoot = now;
    }

}
