#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    font.loadFont("verdana.ttf", 24);
    
    synthesizer.listVoices();
    synthesizer.initSynthesizer("Alex");
    
    //-- intialize recognizer, load dictionary, and register callback
    recognizer.initRecognizer();

    ofDirectory dir;
    dir.listDir("images/");
    
    //allocate the vector to have as many ofImages as files
	if( dir.size() ){
		images.assign(dir.size(), ofImage());
        words.assign(dir.size(), "");
        count.assign(dir.size(), 0);
	}
    
	// you can now iterate through the files and load them into the ofImage vector
	for(int i = 0; i < (int)dir.size(); i++){
        images[i].loadImage(dir.getPath(i));
        words[i] = dir.getName(i);
        ofStringReplace(words[i], ".jpg", "");
        ofLogNotice() << "\""+words[i]+"\"";
	}
    
    recognizer.loadDictionary(words);
    
    ofAddListener(recognizer.speechRecognizedEvent, this, &testApp::speechRecognized);
    
    //-- start recognizing words
    recognizer.startListening();
}

//--------------------------------------------------------------
void testApp::speechRecognized(string& wordRecognized) {
    recognizedWord = wordRecognized;
    showRecognizedWordTimer = ofGetElapsedTimef()+2;
    
    for(int i=0; i<words.size(); i++) {
        //ofLogNotice() << wordRecognized << " == " << words[i];
        if(words[i]==wordRecognized) {
            idx = i;
            count[i]++;
            synthesizer.speakPhrase(words[i]);
            return;
        }
    }
    idx = -1;
}


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0);
    if(showRecognizedWordTimer > ofGetElapsedTimef()) {
        font.drawString("\""+recognizedWord+"\"", 210, 30);
    }
    

    ofRect(0, 0, 200, ofGetHeight());
    for(int i=0; i<words.size(); i++) {
        if(idx==i) ofSetColor(0, 0, 255);
        else ofSetColor(255);
        string label = words[i];
        if(count[i]>0) {
            label += " ("+ofToString(count[i])+")";
        }
        ofDrawBitmapString(label, 10, 20+i*14);
    }
    
    if(idx!=-1) {
        ofSetColor(255);
        images[idx].draw(200, 80);
    }
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

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

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
