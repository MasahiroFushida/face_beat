//
//  FaceTrack.hpp
//  face_beat
//
//  Created by LIFE_MAC_02 on 2018/07/18.
//

#pragma once
#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class FaceTrack {
public:
    FaceTrack(double *emotion_ang);
    //void setup(double *emotion_ang);
    void update();
    void draw();
    void keyPressed(int key);
    void threadedFunction();
    
    int second;
    
    ofParameter<float> value;
    ofxPanel gui;
    
    // カメラ
    ofVideoGrabber cam;
    
    // トラッキング用のインスタンス変数
    ofxFaceTracker tracker;
    
    // カメラからの画像データをカラー画像にするための変数
    ofImage colorImg;
    
    // 音源を鳴らす
    ofSoundPlayer   mySound;
    
    char *str[3] = {"Kick_01_SP.wav","Clap_80s_01_SP.wav","26_Hat_01_SP.wav"};
    
    ofImage     img;
    ofPixels pixels;
    int threshold;
    int save_second;
    
    double *emotion_angf;
    
    ofxCvColorImage color;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayDiff;
    ofxCvGrayscaleImage grayBg;
    
    
};
