#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    recognizer.initRecognizer();
    synthesizer.initSynthesizer("Whisper");
    synthesizer.listVoices();
    synthesizer.getCurrentVoice();
    
    //-- loading directly from a dictionary file
    recognizer.loadDictionaryFromFile("dictionary.txt");
    
    recognizer.startListening();
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

    if(key == 'd')
    {
        synthesizer.setDigitByDigit(true);
    }
    
    if(key == 'c')
    {
        synthesizer.setCharacterByCharacter(true);
        synthesizer.setDigitByDigit(false);
    }
    
    if(key == 'n')
    {
        synthesizer.setDigitByDigit(false);
        synthesizer.setCharacterByCharacter(false);
    }
    
    if(key == 'p')
    {
        synthesizer.pauseSpeaking();
    }
    
    if(key == 't')
    {
        synthesizer.continueSpeaking();
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
    synthesizer.speakPhrase("1000 elephants");
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

void testApp::speechRecognized(string & wordRecognized)
{
    //cout << "event handler notified and string detected was: " << wordRecognized << endl;
    if(wordRecognized == "red")
    {
        ofBackground(255, 0, 0);
        synthesizer.speakPhrase(wordRecognized);
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