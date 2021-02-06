#pragma once

#include "ofMain.h"

enum position {None, left, right};

class GameObject {
public:
    ~GameObject();
    float x, y;
    float score;
    float x_vel, y_vel;
    float drag = 1.0;
    position pos;

    void updateObject();
    void drawObject();
};
class ScoreBoard: public GameObject{
public:
    int lscore;
    int rscore;
    int boardSize = 100;
    int boardWidth = 500;
    ScoreBoard();
    ~ScoreBoard();

    void drawObject();
    void updatescore(int lp, int rp);


};

class Player : public GameObject {
public:
    Player();
    Player(position p = None);
    ~Player();
    float batWidth = 20.0;
    float batSize = 100.0;

    void drawObject();
};

class Ball : public GameObject {
public:
    Ball();
    ~Ball();
    float ballSpeed = 5.0;
    float ballSize = 20.0;

    void drawObject();
    bool collide(Player p);
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    Ball ball;
    ScoreBoard board;
    Player player = Player(position::left);
    Player player1 = Player(position::right);

    int keys[128];

};

