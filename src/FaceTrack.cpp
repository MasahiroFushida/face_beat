//
//  FaceTrack.cpp
//  face_beat
//
//  Created by LIFE_MAC_02 on 2018/07/18.
//
#pragma once
#include "FaceTrack.hpp"
using namespace ofxCv;

//--------------------------------------------------------------
FaceTrack::FaceTrack(double *emotion_ang){

    // カメラマンの起動
    cam.initGrabber(1280,720);
    color.allocate(1280,720);
    grayDiff.allocate(1280, 720);

    emotion_angf = emotion_ang;
    // トラッカーの設定
    tracker.setup();

    mySound.load(str[1]);
    mySound.play();

    threshold=60;

}
//void FaceTrack::setup(double *emotion_ang){
//
//    // カメラマンの起動
//    cam.initGrabber(1280,720);
//    color.allocate(1280,720);
//    grayDiff.allocate(1280, 720);
//
//    emotion_angf = emotion_ang;
//    // トラッカーの設定
//    tracker.setup();
//
//    mySound.load(str[1]);
//    mySound.play();
//
//    threshold=60;
//
//}
//--------------------------------------------------------------
void FaceTrack::update(){

    cam.update();
    
    // カメラ画像
    colorImg.setFromPixels(cam.getPixels().getData(), 1280, 720, OF_IMAGE_COLOR);
    
    
    colorImg.mirror(false, true); // 反転
    
    // facetrackerの更新
    tracker.update(toCv(colorImg));
    
    color.setFromPixels(cam.getPixels().getData(), 1280,720);
    grayImage = color;
    
    grayBg = grayImage;
    
    grayDiff.absDiff(grayBg,grayImage);
    
    grayDiff.threshold(50);
    
}

//--------------------------------------------------------------
void FaceTrack::draw(){
    

    int now = ofGetElapsedTimeMillis();
    
    ofSetColor(255,255,255);
    colorImg.draw(0,0, ofGetWidth(), ofGetHeight());

    img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
    
    if(now -save_second >3000){
        img.save("/Users/life_mac_02/Desktop/IAMAS/01_研究/node_test/screenshot.jpg");
        save_second = ofGetElapsedTimeMillis();
    }
    int angry_parm = *emotion_angf * 1000;
    int tempo;
    if(angry_parm<=1){
        tempo=500;
    }else if(angry_parm>1 && angry_parm < 10){
        tempo=400;
    }else if(angry_parm>10 && angry_parm < 20){
        tempo=300;
    }else if(angry_parm>20){
        tempo=200;
    }
    
//    grayImage.draw(0,0, ofGetWidth(), ofGetHeight());
    grayDiff.draw(0,0, ofGetWidth(), ofGetHeight());
//    //映像から各ピクセルのデータを抽出
//    pixels = cam.getPixelsRef();
//    //5ピクセルごとに色を取得
//    for (int y=0; y<pixels.getHeight(); y+=5) {
//        for (int x=0; x<pixels.getWidth(); x+=5) {
//            ofColor color = pixels.getColor(x, y);
//            //取得した色の明るさが閾値より暗ければ
//            if (color.getLightness() < threshold) {
//                int red = ofMap(x, 0, cam.getWidth(), 0, 255);
//                int blue = ofMap(y, 0, cam.getHeight(), 0, 255);
//                //画面右に行くほど赤、画面下に行くほど青の円を描く
//                ofSetColor(red, 0, blue);
//                ofCircle(x, y, 3);
//            }
//        }
//    }

    // 顔の各ポイントの座標を取得
    vector <ofVec2f> points = tracker.getImagePoints();
    
    for (int cnt = 0; cnt < points.size(); cnt++) {
        // 比の計算で座標を変更 1024*768用
        ofDrawCircle(points[cnt].x * 1.6, points[cnt].y * 1.6, 5);
    }
    
    // 口の縦の距離を取得
    int y = (int)tracker.getImagePoint(61).y;
    int y2 = (int)tracker.getImagePoint(64).y;
    
    int length = y2 -y;
    
    // 口の横の長さを取得
    int x = (int)tracker.getImagePoint(48).x;
    int x2 = (int)tracker.getImagePoint(54).x;
    
    int x_length = x2 -x;
    
    // 目の開き具合を取得(左目）
    int me_y = (int)tracker.getImagePoint(38).y;
    int me_y2 = (int)tracker.getImagePoint(40).y;

    // 目の開き具合を取得(右目）
    int me2_y = (int)tracker.getImagePoint(44).y;
    int me2_y2 = (int)tracker.getImagePoint(46).y;
    int me_length2 = me2_y2 - me2_y;
    
    // float me_length = float((me_y2 - me_y)/18.0);

    int me_length = me_y2 - me_y;
    float volume;
    switch (me_length){
        case 6 :
            volume = 0.1;
            break;
        case 7 :
            volume = 0.2;
            break;
        case 8 :
            volume = 0.3;
            break;
        case 9 :
            volume = 0.4;
            break;
        case 10 :
            volume = 0.5;
            break;
        case 11 :
            volume = 1.0;
            break;
        case 12 :
            volume = 1.0;
            break;
        default:
            volume = 0.3;
            break;
    }


    
    
//    std::printf("now: %d\n", now);
//    std::printf("second: %d\n", second);
    
    int sabun = now-second;
    
//    std::printf("sabun: %d\n", sabun);
//    std::printf("length: %d\n", length);
    
    if( length > 1 && second ==0) {
        mySound.load(str[0]);
        mySound.setVolume(volume);
        mySound.play();
        second = ofGetElapsedTimeMillis();
        
    }else if(length <= 5 && now -second >tempo) {
        //KICK
        mySound.load(str[0]);
        mySound.setVolume(volume);
        mySound.play();
        second = ofGetElapsedTimeMillis();
        //sleep(1);
    }else if(length > 5 && now -second >tempo) {
        //SN
        mySound.load(str[1]);
        mySound.setVolume(volume);
        mySound.play();
        second = ofGetElapsedTimeMillis();
        //sleep(1);
    }
//    if(me_length2 < 8 && now -second >tempo/2) {
//        //HH
//        mySound.load(str[2]);
//        mySound.setVolume(volume);
//        mySound.play();
//        second = ofGetElapsedTimeMillis();
//    }
    
    
    if ((*emotion_angf * 1000) > 0.1 && now -second >500) {
//        mySound.load(str[2]);
//        mySound.setVolume(1);
//        mySound.play();

    }
//    gui.draw();

}

void FaceTrack::keyPressed(int key){
    int x = (int)tracker.getImagePoint(61).x;
    int y = (int)tracker.getImagePoint(61).y;
    
    int x2 = (int)tracker.getImagePoint(64).x;
    int y2 = (int)tracker.getImagePoint(64).y;
    
}

//void FaceTrack::threadedFunction(){
//
////    setup();
//    while(isThreadRunning())
//    {
//        update();
//        draw();
//    }
//}
