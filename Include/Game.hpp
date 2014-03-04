#ifndef GAME_HPP
#define GAME_HPP

class Game
{
public:
    Game(int width, int height);

    void init();

    void keyEvent(unsigned char key, int x, int y);
    void mouseEvent(int button, int state, int x, int y);
    void specialKeyPressed(int key, int x, int y);
    void specialKeyReleased(int key, int x, int y);

    void update(int delta);
    void display();

    void resize(int width, int height);

private:
    int m_Width;
    int m_Height;
};

#endif // GAME_HPP
