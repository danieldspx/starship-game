http://www.chrishecker.com/Miscellaneous_Technical_Articles

#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <vector>

// Structure to represent a particle
struct Particle {
    float x, y; // Position
    float vx, vy; // Velocity
    float lifetime; // Lifetime of the particle

    Particle(float xPos, float yPos, float xVel, float yVel, float life)
        : x(xPos), y(yPos), vx(xVel), vy(yVel), lifetime(life) {}
};

std::vector<Particle> particles; // Vector to store particles

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Update and draw particles
    for (auto& particle : particles) {
        particle.x += particle.vx;
        particle.y += particle.vy;
        particle.vx *= 0.98f;
        particle.vy *= 0.98f;
        particle.lifetime -= 0.02f;

        // Draw the particle as a point
        glBegin(GL_POINTS);
        glColor3f(1.0f, particle.lifetime, 0.0f);
        glVertex2f(particle.x, particle.y);
        glEnd();
    }

    // Remove dead particles
    particles.erase(
        std::remove_if(
            particles.begin(),
            particles.end(),
            [](const Particle& p) { return p.lifetime < 0.0f; }),
        particles.end());

    glutSwapBuffers();
}

void timer(int value) {
    // Generate new particles
    for (int i = 0; i < 50; ++i) {
        float angle = 2 * M_PI * rand() / RAND_MAX;
        float speed = 0.02f * rand() / RAND_MAX;
        particles.emplace_back(0.0f, 0.0f, speed * cos(angle), speed * sin(angle), 1.0f);
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Explosion Example");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}
