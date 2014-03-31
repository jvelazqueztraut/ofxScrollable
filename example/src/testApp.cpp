#include "testApp.h"

#define FRAME_WIDTH 404
#define FRAME_HEIGHT 504
#define FADE_SIZE 50
//--------------------------------------------------------------
void testApp::setup(){
    textLong.load("textLong.png",FRAME_WIDTH,FRAME_HEIGHT,FADE_SIZE);
    textLong.setAnchorPercent(0.5,0.5);
    textLongPos.set(ofGetWidth()*0.25,ofGetHeight()*0.5);

    ofImage textImg;
    textImg.loadImage("textShort.png");
    textImg.rotate90(2);
    textShort.load(textImg,FRAME_WIDTH,FRAME_HEIGHT,FADE_SIZE);
    textShort.setAnchorPercent(0.5,0.5);
    textShortPos.set(ofGetWidth()*0.75,ofGetHeight()*0.5);
}

//--------------------------------------------------------------
void testApp::update(){
    textLong.update();
    
    textShort.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(ofColor::white);
    ofSetColor(255);
    
    textLong.draw(textLongPos.x,textLongPos.y);
    
    textShort.draw(textShortPos.x,textShortPos.y);
    
    //Just squares to show the dimensions of the scrollable zone and fade
    ofSetColor(0);
    ofNoFill();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(ofGetWidth()*0.25,ofGetHeight()*0.5,textLong.getWidth(),textLong.getHeight());
    ofLine(ofGetWidth()*0.25-textLong.getWidth()*0.5,ofGetHeight()*0.5-textLong.getHeight()*0.5+FADE_SIZE,ofGetWidth()*0.25+textLong.getWidth()*0.5,ofGetHeight()*0.5-textLong.getHeight()*0.5+FADE_SIZE);
    ofLine(ofGetWidth()*0.25-textLong.getWidth()*0.5,ofGetHeight()*0.5+textLong.getHeight()*0.5-FADE_SIZE,ofGetWidth()*0.25+textLong.getWidth()*0.5,ofGetHeight()*0.5+textLong.getHeight()*0.5-FADE_SIZE);
    
    //Just squares to show the dimensions of the scrollable zone and fade
    ofSetColor(0);
    ofNoFill();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(ofGetWidth()*0.75,ofGetHeight()*0.5,textLong.getWidth(),textLong.getHeight());
    ofLine(ofGetWidth()*0.75-textLong.getWidth()*0.5,ofGetHeight()*0.5-textLong.getHeight()*0.5+FADE_SIZE,ofGetWidth()*0.75+textLong.getWidth()*0.5,ofGetHeight()*0.5-textLong.getHeight()*0.5+FADE_SIZE);
    ofLine(ofGetWidth()*0.75-textLong.getWidth()*0.5,ofGetHeight()*0.5+textLong.getHeight()*0.5-FADE_SIZE,ofGetWidth()*0.75+textLong.getWidth()*0.5,ofGetHeight()*0.5+textLong.getHeight()*0.5-FADE_SIZE);
    //
    ofSetRectMode(OF_RECTMODE_CORNER);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    ofRectangle textLongRect(textLongPos.x-0.5*textLong.getWidth(),textLongPos.y-0.5*textLong.getHeight(),textLong.getWidth(),textLong.getHeight());
    if(textLongRect.inside(x,y)){
        textLong.pressed(ofPoint(x,y));
        return;
    }
    ofRectangle textShortRect(textShortPos.x-0.5*textShort.getWidth(),textShortPos.y-0.5*textShort.getHeight(),textShort.getWidth(),textShort.getHeight());
    if(textShortRect.inside(x,y)){
        textShort.pressed(ofPoint(x,y));
        return;
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if(textLong.dragged(ofPoint(x,y))){
        return;
    }
    if(textShort.dragged(ofPoint(x,y))){
        return;
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if(textLong.released(ofPoint(x,y))){
        return;
    }
    if(textShort.released(ofPoint(x,y))){
        return;
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
