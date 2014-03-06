#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "Game.hpp"

const int WIDTH = 1024;
const int HEIGHT = 640;
const char* TITLE = "Mazel!";

int oldTimeElapsed;

Game game(WIDTH, HEIGHT);

void specialDown(int key, int x, int y)
{
    game.specialKeyPressed(key, x, y);
}

void specialUp(int key, int x, int y)
{
    game.specialKeyReleased(key, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
    game.keyEvent(key, x, y);
}

void mouse(int button, int state, int x, int y)
{
    game.mouseEvent(button, state, x, y);
}

int calculateDelta()
{
    int timeElapsed = glutGet(GLUT_ELAPSED_TIME);
    int delta = timeElapsed - oldTimeElapsed;
    oldTimeElapsed = timeElapsed;

    return delta;
}

void update(int delta)
{
    game.update(delta);
}

void display()
{
    int delta = calculateDelta();
    update(delta);

    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    game.display();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    game.resize(width, height);
}

void initGlew()
{
    GLenum status = glewInit();

    if (status != GLEW_OK)
        std::cerr << "Error initializing GLEW: " << glewGetErrorString(status) << std::endl;
}

void setupCallbacks()
{
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
}

void setupWindow()
{
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(TITLE);
}

void initGlut(int argc, char** argv)
{
    glutInit(&argc, argv);
    setupWindow();
    setupCallbacks();
}

int main(int argc, char** argv)
{
    initGlut(argc, argv);
    initGlew();

    game.init();

    glutMainLoop();
}
