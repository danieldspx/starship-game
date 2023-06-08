//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "gl_canvas2d.h"
#include "base/Utils.h"

void SceneManager::render(int screenWidth, int screenHeight) {
    CV::clear(0,0,0);
    if (isKeyPressed) {
        switch (keyPressed) {
            case 201:
                baseHeight += speedY;
                break;
            case 203:
                baseHeight += -speedY;
                break;
        }
    }
    renderLanes();
}

void SceneManager::keyboardDown(int key) {
    keyPressed = key;
    isKeyPressed = true;
}

void SceneManager::keyboardUp(int key) {
    isKeyPressed = false;
}

void SceneManager::renderLanes() {
    for (int p = 0; p + 3 < LANE_POINTS; p++) {
        for (float t = 0; t <= 1; t += 0.01) {
            CV::color(3);
            fvec2 leftPoint = Utils::bspline(leftLane, t, p, LANE_POINTS);
            fvec2 rightPoint = Utils::bspline(rightLane, t, p, LANE_POINTS);

            leftPoint.y -= baseHeight;
            rightPoint.y -= baseHeight;

            CV::point(leftPoint);
            CV::point(rightPoint);
        }
    }

//    Utils::bspline(, 0.01, 0, LANE_POINTS)
}
