#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    ofSetWindowShape(600, 400);
    
    cam_x = cam_y = 20;
    cam_width     = 320;
    cam_height    = 280;
    
    camera.initGrabber(cam_width, cam_height);

    //-- let's see the voices available in the system
    synthesizer.listVoices();
    synthesizer.initSynthesizer("Ralph");
}

//--------------------------------------------------------------
void testApp::update(){
    camera.grabFrame();
}

//--------------------------------------------------------------
void testApp::draw(){
    camera.draw(cam_x, cam_y);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    synthesizer.speakPhrase("A Key has been pressed");
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if((x >= cam_x && x <= cam_x + cam_width) && (y >= cam_y && y <= cam_y + cam_height))
        synthesizer.speakPhrase("This is the video stream");
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

