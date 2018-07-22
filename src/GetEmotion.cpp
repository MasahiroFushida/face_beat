//
//  GetEmotion.cpp
//  face_beat
//
//  Created by LIFE_MAC_02 on 2018/07/18.
//

#include "GetEmotion.hpp"


#include "string.h"
#include <thread>

using namespace std;

#define HOST "127.0.0.1" //送信先ホストのIPを設定


#define SEND_PORT 5000
#define RECIEVE_PORT 6000
std::__1::string test;


//--------------------------------------------------------------
 void GetEmotion::setup(){
    sender.setup(HOST, SEND_PORT);
    receiver.setup(RECIEVE_PORT);
    emoFlg = false;
}


//--------------------------------------------------------------
void GetEmotion::update(double *emotion_ang){
     OSCrecv(emotion_ang);
}

//--------------------------------------------------------------
void GetEmotion::draw(double *emotion_ang){
    OSCsender("/test", 123);
    //OSCrecv(emotion_ang);
    

}

void GetEmotion::OSCsender(string address, int x){
    
    
    ofxOscMessage m;
    m.setAddress(address);
    m.addIntArg(x);
    //3秒 sleep
    sleep(3000);

    sender.sendMessage(m);

}

void GetEmotion::OSCrecv(double *emotion_ang){
    
    while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage m;
        
        receiver.getNextMessage( &m );
        
        //OSC message setting
        if ( m.getAddress() == "/address" ){
            test = m.getArgAsString(0);
            if(test.compare("") != 0 && test.size() < 20 && test.compare("undefined\n") != 0){
    
                *emotion_ang = std::stod(test);
            }

        }
    }
}

void GetEmotion::threadedFunction(){
    
    emoFlg=true;
    setup();
    while(isThreadRunning())
    {
        update(&emotion_ang);
        draw(&emotion_ang);
    }
}
