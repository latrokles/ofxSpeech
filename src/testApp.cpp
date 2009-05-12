#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    recognizer.initRecognizer();
    words.push_back("red");
    words.push_back("green");
    words.push_back("blue");
    
    recognizer.addVocabulary(words);
    
    recognizer.startRecognizer();
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

