#pragma once
#include "ofApp.h"
#include <signal.h>


//--------------------------------------------------------------
void ofApp::setup(){
    
    
    cap = new Capture();

    getemo.startThread();

//    facetrack.setup(&getemo.emotion_ang );
//    facetrack.startThread();
    
    facetrack = new FaceTrack(&getemo.emotion_ang );

    emotion.set("emotion_anger", emotion, 0, 100); // name, default value, min, max
    gui.setup();
    gui.add(emotion);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    double emo;
    cap->update();

    facetrack->update();
    emo = getemo.emotion_ang;

}

//--------------------------------------------------------------
void ofApp::draw(){
    

    
    facetrack->draw();
    emotion = getemo.emotion_ang * 1000;

    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
