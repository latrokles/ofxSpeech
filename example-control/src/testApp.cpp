#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofAddListener(recognizer.speechRecognizedEvent, this, &testApp::speechRecognized);
    recognizer.initRecognizer();
    recognizer.loadDictionaryFromFile("dictionary.txt");
    recognizer.startListening();
    
    drawCircle      = false;
    circle_x        = ofGetWidth()/2;
    circle_y        = ofGetHeight()/2;
    circle_radius   = 5;
}

//--------------------------------------------------------------
void testApp::speechRecognized(string & wordRecognized)
{
    cout << wordRecognized << endl;
    if(wordRecognized == "circle")
    {
        drawCircle =! drawCircle;
    }
    
    if(wordRecognized == "center")
    {
        circle_x = ofGetWidth()/2;
        circle_y = ofGetHeight()/2;
    }
    
    if(wordRecognized == "bigger")
    {
        circle_radius += 20;
    }
    
    if(wordRecognized == "smaller")
    {
        circle_radius -= 20;
    }
    
    if(wordRecognized == "upper")
    {
        circle_y -= 10;
    }
    
    if(wordRecognized == "lower")
    {
        circle_y += 10;
    }
    
    if(wordRecognized == "red")
    {
        ofSetColor(255, 0, 0);
    }
    
    if(wordRecognized == "green")
    {
        ofSetColor(0, 255, 0);
    }
    
    if(wordRecognized == "blue")
    {
        ofSetColor(0, 0, 255);
    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    if(drawCircle)
        ofCircle(circle_x, circle_y, circle_radius);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    circle_x = mouseX;
    circle_y = mouseY;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    circle_radius ++;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
