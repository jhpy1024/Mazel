#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

const int WIDTH = 1024;
const int HEIGHT = 600;
const char* TITLE = "Mazel!";

void specialDown(int key, int x, int y)
{

}

void specialUp(int key, int x, int y)
{

}

void keyboard(unsigned char key, int x, int y)
{

}

void mouse(int button, int state, int x, int y)
{

}

void display()
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
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
    setupCallbacks();
    setupWindow();
}

int main(int argc, char** argv)
{
    initGlut(argc, argv);
    initGlew();

    glutMainLoop();
}
