#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    recognizer.initRecognizer();
    
    /*
    //-- loading from a vector of strings
    words.push_back("red");
    words.push_back("green");
    words.push_back("black");
    recognizer.addDictionary(words);
    */
    
    //-- loading directly from a dictionary file
    recognizer.addDictionaryFromFile("dictionary.txt");
    
    recognizer.startRecognizer();
    ofAddListener(recognizer.speechRecognizedEvent, this, &testApp::speechRecognized);
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

void testApp::speechRecognized(string & wordRecognized)
{
    cout << "event handler notified and string detected was: " << wordRecognized << endl;
    if(wordRecognized == "red")
    {
        ofBackground(255, 0, 0);
    }
    else if(wordRecognized == "green")
    {
        ofBackground(0, 255, 0);
    }
    else if(wordRecognized == "black")
    {
        ofBackground(0, 0, 0);
    }
    else if(wordRecognized == "white")
    {
        ofBackground(255, 255, 255);
    }
}