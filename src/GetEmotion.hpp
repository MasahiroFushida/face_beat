//
//  GetEmotion.hpp
//  face_beat
//
//  Created by LIFE_MAC_02 on 2018/07/18.
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

class GetEmotion : public ofThread{
public:
    void setup();
    void update(double *emotion_ang);
    void draw(double *emotion_ang);
    void OSCsender(string message,int value);
    void OSCrecv(double *emotion_ang);
    
    double threadedFunction(double *emotion_ang);
    
    
    // 感情検出のカメラ用変数
    ofxOscSender sender;
    ofxOscReceiver receiver;
    double d ;
    
    bool emoFlg = false;
    bool emoSend = false;
    double emotion_ang;
    int cnt=0;
    void threadedFunction();

};
