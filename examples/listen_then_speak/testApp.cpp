#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowShape(600, 600);
    ofSetVerticalSync(true);
    r = g = b = 0;
    ofBackground(r, g, b);
    
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
    
    ofSetColor(r, g, b);
        
    displayFont.loadFont("verdana.ttf", 32);
    
    //synthesizer.listVoices();
    //-- initialize with voice
    spelling = false;
    synthesizer.initSynthesizer("Alex");
    
    //-- intialize recognizer, load dictionary, and register callback
    recognizer.initRecognizer();
    recognizer.loadDictionaryFromFile("dictionary.txt");
    ofAddListener(recognizer.speechRecognizedEvent, this, &testApp::speechRecognized);
    
    //-- start recognizing words
    recognizer.startListening();
}

//--------------------------------------------------------------
void testApp::update(){
    word_x = (ofGetWidth()/2) - (displayFont.stringWidth(wordToDisplay)/2);
    word_y = (ofGetHeight()/2) - (displayFont.stringHeight(wordToDisplay)/2);
}

//--------------------------------------------------------------
void testApp::draw(){
    displayFont.drawString(wordToDisplay, word_x, word_y);
    
    if(spelling)
    {
        ofDrawBitmapString("Spelling of words enabled.", 20, 20);
    }
    else
    {
        ofDrawBitmapString("Spelling of words disabled.", 20, 20);
    }
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key == ' ')
    {
        spelling = !spelling;
        synthesizer.setCharacterByCharacter(spelling);
    }
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
    //-- we don't want to display the default error ???, or do we?
    if((wordRecognized != "???") && (wordRecognized != "invert"))
    {
        wordToDisplay = wordRecognized;
        
        synthesizer.speakPhrase(wordRecognized);
    }
    
    if(wordRecognized == "invert")
    {
        //-- r, g, b are the fill color at the moment
        //-- so turn background to fill color
        ofBackground(r, g, b);
        
        //-- invert fill color
        r = 255 - r;
        g = 255 - g;
        b = 255 - b;
        
        //-- set new fill color
        ofSetColor(r, g, b);
    }
}