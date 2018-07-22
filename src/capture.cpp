//
//  capture.cpp
//  face_beat
//
//  Created by LIFE_MAC_02 on 2018/07/18.
//

#include "capture.hpp"
Capture::Capture(){

    //感情検出用の写真を削除
    remove("/Users/life_mac_02/Desktop/IAMAS/01_研究/node_test/screenshot.jpg");
    ofBackground(0,0,0);
    ofSetFrameRate(30);
    
    //キャプチャする画像のサイズを指定
    camWidth = ofGetWidth();
    camHeight = ofGetHeight();
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    
    
}

void Capture::update(){
    //キャプチャする
    vidGrabber.update();

}

void Capture::draw(){

    ofSetColor(0xFFFFFF);
    vidGrabber.draw(0,0);
    
    img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());

    img.save("/Users/life_mac_02/Desktop/IAMAS/01_研究/node_test/screenshot.jpg");


}
