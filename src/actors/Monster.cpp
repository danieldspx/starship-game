//
// Created by daniel on 10/06/23.
//

#include "Monster.h"
#include "../gl_canvas2d.h"

Monster::Monster(fvec2 pos, int type, float leftBoundary, float rightBoundary): position(pos), type(type), leftBoundary(leftBoundary), rightBoundary(rightBoundary) {
    rng = std::mt19937(rd());
    distribution = std::uniform_int_distribution<int>(1, 10);
    speedX = 25;
    speedX = distribution(rng) % 2 == 0 ? +speedX : -speedX;
}

void Monster::render(float screenWidth, float screenHeight, float dt) {
    renderMonster();
    animate(dt);
}

void Monster::animate(float dt) {
    float radius = getMonsterRadius(type);
    position.x += speedX * dt;
    // Make sure they don't go over the lanes
    if (position.x - radius < leftBoundary) {
        position.x = leftBoundary + radius;
        speedX = -speedX;
    } else if (position.x + radius > rightBoundary) {
        position.x = rightBoundary - radius;
        speedX = -speedX;
    }
}

void Monster::renderMonster() {
    float radius = Monster::getMonsterRadius(type);

    if (DEBUG) {
        CV::color(0,0,1);
        CV::circle(position, radius, 50);
    }

    if (type == 1) {
        CV::color(252/255.0, 3/255.0, 65/255.0);
        CV::circleFill(position, radius, 6);
    } else if (type == 2) {
        CV::color(152/255.0, 3/255.0, 252/255.0);
        CV::circleFill(position, radius, 4);
    } else if (type == 3) {
        CV::color(1,0,0);
        CV::circleFill(position, radius, 4, PI/4);
        CV::color(0,0,0);
        CV::circleFill(fvec2 {position.x - 10, position.y + 10}, 5, 4, PI/4);
        CV::circleFill(fvec2 {position.x + 10, position.y + 10}, 5, 4, PI/4);
        CV::circleFill(position, 5, 4, PI/4);
        CV::circleFill(fvec2 {position.x - 10, position.y - 10}, 5, 4, PI/4);
        CV::circleFill(fvec2 {position.x + 10, position.y - 10}, 5, 4, PI/4);
        CV::color(1, 136/255.0, 25/255.0);
        CV::circleFill(fvec2 {position.x + 11, position.y - 21}, 8, 3, PI/6);
        CV::circleFill(fvec2 {position.x - 11, position.y - 21}, 8, 3, PI/6);
    }
}

float Monster::getMonsterRadius(int type) {
    switch (type) {
        case 1:
        case 2:
            return 18;
        case 3:
            return 25;
    }
    return 0;
}