//
// Created by daniel on 10/06/23.
//

#ifndef CANVAS_CLION_MONSTER_H
#define CANVAS_CLION_MONSTER_H


#include <random>
#include <functional>
#include <chrono>
#include "./Bullet.h"
#include "../base/interfaces/IRender.h"
#include "../base/vectors/Vector2D.h"
#include "../base/interfaces/IIntersect.h"

class Monster: public IRender, public IIntersect {

public:
    fvec2 position;
    int type;
    float speedX;
    float leftBoundary, rightBoundary;
    float health;

    std::random_device rd;  // Seed for the random number engine
    std::mt19937 rng; // Mersenne Twister random number engine
    std::uniform_int_distribution<int> distribution;

    std::function<void(Bullet*)> addBulletCallback;

    std::chrono::milliseconds firerate;
    std::chrono::high_resolution_clock::time_point lastShoot;

    Monster(fvec2 pos, int type, float leftBoundary, float rightBoundary, std::function<void(Bullet*)> addBulletCallback);

    bool isIntersecting(fvec2 position) override;

    void render(float screenWidth, float screenHeight, float dt) override;

    void renderMonster();

    static float getMonsterRadius(int type);

    void animate(float dt);

    void hit(float damage);

    bool isAlive();

    void shootBullet();
};


#endif //CANVAS_CLION_MONSTER_H
