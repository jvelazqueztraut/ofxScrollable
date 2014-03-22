//
//  ScrolleableT.cpp
//  scrolleableText
//
//  Created by Zaira on 18/02/14.
//
//

#include "ofxScrollable.h"

#define DAMPING 10.
#define MASS 1.
#define K 30.

ofxScrollable::ofxScrollable(){
    p=false;
    pOrigin=0;
    desOrigin=0;

    reset();
}

void ofxScrollable::load(string path, float w, float h, float f){
    width = w;
    height = h;
    
    ofFbo::allocate(width,height,GL_RGBA32F_ARB);
    
    ofPixels imagePixels;
    ofLoadImage(imagePixels, path);
    texWidth = imagePixels.getWidth();
    texHeight = imagePixels.getHeight();
    tex.loadData(imagePixels);
    tex.setAnchorPercent(0.5,0.0);
    
    fadeSize = f;
    ofFloatPixels fadePixels;
    fadePixels.allocate(width,fadeSize,OF_PIXELS_RGBA);
    int i=0;
    for(int y=0;y<(int)fadeSize;y++) {
        for(int x=0;x<(int)width;x++){
            fadePixels[i+0]=0.;
            fadePixels[i+1]=0.;
            fadePixels[i+2]=0.;
            fadePixels[i+3]=1.-(y*y)/(fadeSize*fadeSize); //QUADRATIC_EASE_IN
            i+=4;
        }
    }
    fade.loadData(fadePixels);
    time = ofGetElapsedTimef();
}
    
void ofxScrollable::update(){
        
    ofPushStyle();
    ofFbo::begin();
    ofClear(0, 0);
    glBlendFuncSeparate(GL_ONE, GL_SRC_COLOR, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    ofSetColor(255);
    tex.draw(width*0.5,position);
    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    ofPushMatrix();
    ofScale(1.,ofClamp(-1*position/fadeSize,0.,1.));
    fade.draw(0,0);
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(width,height);
    ofRotateZ(-180);
    ofScale(1.,ofClamp((position+texHeight-height)/fadeSize,0.,1.));
    fade.draw(0,0);
    ofPopMatrix();
    ofFbo::end();
    ofPopStyle();
        
    float t=ofGetElapsedTimef();
    float dt=t-time;
    time=t;
        
    float accel=destination-position;
    accel*=(K/MASS);
    accel-=(DAMPING/MASS)*velocity;
    velocity+=(accel*dt);
    position+=(velocity*dt);
}

bool ofxScrollable::pressed(ofPoint pos, int ID){
    p=true;
    pID=ID;
    pOrigin=pos.y;
    desOrigin=destination;
    return true;
}

bool ofxScrollable::dragged(ofPoint pos, int ID){
    if(p && pID==ID){
        destination = desOrigin + (pos.y - pOrigin);
        return true;
    }
    return false;
}
    
bool ofxScrollable::released(ofPoint pos, int ID){
    if(p && pID==ID){
        destination = desOrigin + (pos.y - pOrigin);
        if(texHeight<height){
            destination = 0;
        }
        else if(destination>0){
            destination = 0;
        }
        else if(destination< (height-texHeight)){
            destination = (height-texHeight);
        }
        p = false;
        return true;
    }
    return false;
}

float ofxScrollable::getWidth(){
    return width;
}
float ofxScrollable::getHeight(){
    return height;
}

void ofxScrollable::reset(){
    position=0;
    destination=0;
    velocity=0;
}