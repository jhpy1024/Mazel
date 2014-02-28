#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <iostream>

int oldTimeElapsed = 0;

void handleInput(unsigned char key, int x, int y)
{

}

void update(int delta)
{

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
    glutKeyboardFunc(&handleInput);
    glutDisplayFunc(&display);
    glutIdleFunc(&display);
}

void setupGL()
{

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

