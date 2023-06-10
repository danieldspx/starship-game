#include <iostream>
#include <chrono>
#include <thread>

class Object {
public:
    float position;
    float velocity;

    Object(float initialPosition, float initialVelocity)
        : position(initialPosition), velocity(initialVelocity) {}

    void Update(float elapsedSeconds) {
        float distanceToMove = velocity / FPS;
        float distanceMoved = distanceToMove * elapsedSeconds;
        position += distanceMoved;
    }
};

int main() {
    const int FPS = 60;
    const float desiredVelocity = 100.0f; // Units per second

    Object obj(0.0f, desiredVelocity);

    while (true) {
        auto startTime = std::chrono::high_resolution_clock::now();

        // Update and render logic
        obj.Update(1.0f / FPS);
        std::cout << "Object Position: " << obj.position << std::endl;

        // Calculate elapsed time
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration<float>(endTime - startTime).count();

        // Sleep if necessary to achieve desired FPS
        std::chrono::milliseconds frameTime(static_cast<long>((1.0f / FPS - elapsed) * 1000));
        std::this_thread::sleep_for(frameTime);
    }

    return 0;
}
