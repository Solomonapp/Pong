#include "ofApp.h"

int score1=0;
int score2=0;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

    if(ball.x>player1.x && ball.y>player1.y+(player1.batSize) && ball.x_vel<0) player1.y_vel = 5.0;
    if(ball.x>player1.x && ball.y<player1.y && ball.x_vel<0) player1.y_vel = -5.0;

    if(ball.x_vel>0 && (ofGetHeight()/2)>player1.y+(player1.batSize)) player1.y_vel = 7.0;
    if(ball.x_vel>0 && (ofGetHeight()/2)<player1.y) player1.y_vel = -7.0;

    if(keys['s']) player.y_vel = 15.0;
    if(keys['w']) player.y_vel = -15.0;
//    if(ball.x > ofGetWidth()) player1.score++;
//    if(ball.x < 0) player.score++;
   // if(keys['a']) player1.y_vel = 15.0;
   // if(keys['q']) player1.y_vel = -15.0;

    player1.x = 40.0;

    ball.collide(player);
    ball.collide(player1);
    ball.updateObject();
    player.updateObject();
    player1.updateObject();
    board.updatescore(player.score,player1.score);


}

//--------------------------------------------------------------
void ofApp::draw(){
 board.drawObject();
 ball.drawObject();
 player.drawObject(); //rpaddle
 player1.drawObject();//lpaddle

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    keys[key] = 1;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    keys[key] = 0;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

GameObject::~GameObject() {
}

void GameObject::updateObject(){

    int w = ofGetWidth();
    int h = ofGetHeight();
    x_vel *= drag;
    y_vel *= drag;
    x += x_vel;
    y += y_vel;
    if( x < 0 ) {
        x=w/2; x_vel = x_vel;
        if (this->pos == position::left) this->score++;
        score1++;
    }
    if( y < 0 ) {y=0; y_vel *= -1.0;}
    if( x>w ) {
        x=w/2; x_vel = -x_vel;
        if (this->pos == position::right) this->score++;
        score2++;
    }

    if( y>h ) {y=h; y_vel *=-1.0;}
}

void GameObject::drawObject(){

}



bool Ball::collide( Player p ) {
    // does the ball overlap the bat in y axis?
    float top = p.y-ballSize/2;
    float bot = p.y+p.batSize+ballSize/2;

    if(y<top || y>bot) return false;

    // does the ball overlap the bat in x axis?
    if (p.x != 40) {
    float x_dist = abs(x-p.x);
    float intersect_dist_x = ballSize;
    if( x_dist < intersect_dist_x ) {
        x_vel = -abs(x_vel + (0.3*p.y_vel) );
        return true;
    }
    return false;
    } else {
        float x_dist = abs(x-p.x);
        float intersect_dist_x = ballSize;
        if( x_dist < intersect_dist_x ) {
            x_vel = -(x_vel +(0.3*p.y_vel) );
            return true;
        }
        return false;
    }
}

Ball::Ball() {
    x=ofGetWidth()/2.0;
    y=ofGetHeight()/2.0;
    float angle = ofRandom(6.284);

    x_vel = ballSpeed * cos(angle);
    y_vel = ballSpeed * sin(angle);
}

Ball::~Ball() {
}

void Ball::drawObject(){

    ofDrawCircle(x,y,ballSize);
}

Player::Player() {
    x = ofGetWidth() - 40.0;
    y = ofRandom(0, ofGetHeight());
    x_vel = 0;
    y_vel = 0;
    drag = 0.9;
    score = 0;
}

Player::Player(position p) {
    this->pos = p;
    x = ofGetWidth() - 40.0;
    y = ofRandom(0, ofGetHeight());
    x_vel = 0;
    y_vel = 0;
    drag = 0.9;
    score = 0;
}



Player::~Player() {
}


void Player::drawObject() {
    ofDrawRectangle(x,y,batWidth,batSize);
}

ScoreBoard::ScoreBoard(){
    x =(ofGetWidth()/2)-(boardWidth/2);
    y = 0;
    lscore=0;
    rscore=0;
}

ScoreBoard::~ScoreBoard(){}

void ScoreBoard::drawObject(){
    ofNoFill();
    ofSetColor(255,255,255,255);
    ofDrawRectangle(x,y,boardWidth,boardSize);
    ofFill();
    ofSetColor(255,255,255,255);
    ofDrawBitmapString(ofToString(lscore),x+20,y+boardSize/2);
    ofDrawBitmapString(ofToString(rscore),x+boardWidth-30,y+boardSize/2);
}

void ScoreBoard::updatescore(int lp, int rp){
//    lscore = lp;
//    rscore = rp;
    lscore = score1;
    rscore=score2;
}
