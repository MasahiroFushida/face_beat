//
//  capture.hpp
//  face_beat
//
//  Created by LIFE_MAC_02 on 2018/07/18.
//


#pragma once
#include "ofMain.h"


class Capture {
public:
    Capture();
    void update();
    void draw();

    // 感情検出のカメラ用変数
    ofVideoGrabber vidGrabber;
    ofImage img;
    int camWidth, camHeight;
    
};
