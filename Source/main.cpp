#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <iostream>

#include "Game.hpp"

int oldTimeElapsed = 0;

Game game;

void keyPressed(unsigned char key, int x, int y)
{
    game.keyPressed(key, x, y);
}

void specialKeyPressed(int key, int x, int y)
{
    game.specialKeyPressed(key, x, y);
}

void specialKeyReleased(int key, int x, int y)
{
    game.specialKeyReleased(key, x, y);
}

void mousePressed(int button, int state, int x, int y)
{
    game.mousePressed(button, state, x, y);
}

void update(int delta)
{
    game.update(delta);
}

int calculateDelta()
{
    int timeElapsed = glutGet(GLUT_ELAPSED_TIME);
    int delta = timeElapsed - oldTimeElapsed;
    oldTimeElapsed = timeElapsed;

    return delta;
}

void display()
{
    int delta = calculateDelta();
    update(delta);

    game.render();

    glutSwapBuffers();
}

void initGlew()
{
    auto status = glewInit();
    if (status != GLEW_OK)
        std::cerr << glewGetErrorString(status) << std::endl;
}

void createWindow()
{
    glutInitWindowSize(1024, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Mazel!");
}

void setupCallbacks()
{
    glutKeyboardFunc(&keyPressed);
    glutSpecialFunc(&specialKeyPressed);
    glutSpecialUpFunc(&specialKeyReleased);
    glutMouseFunc(&mousePressed);
    glutDisplayFunc(&display);
    glutIdleFunc(&display);
}

void setupGL()
{
    glDisable(GL_DEPTH_TEST);
    game.setupGL();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    createWindow();
    initGlew();
    setupCallbacks();
    setupGL();

    glutMainLoop();

    return 0;
}

