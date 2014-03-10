#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

class Game;
class GameState
{
public:
    GameState(Game* game);

    virtual void keyPressed(unsigned char key, int x, int y);
    virtual void keyReleased(unsigned char key, int x, int y);
    virtual void mouseEvent(int button, int state, int x, int y);
    virtual void specialKeyPressed(int key, int x, int y);
    virtual void specialKeyReleased(int key, int x, int y);

    virtual void update(int delta);
    virtual void display();

private:
    Game* m_Game;
};

#endif // GAME_STATE_HPP
