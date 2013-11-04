#pragma once

#include "ofMain.h"
#include "ofxSpeech.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //-- test event handler for speech recognition,
        void speechRecognized(string & wordRecognized);
        
        //-- test stuff for speech addon
        ofxSpeechRecognizer         recognizer;
        ofxSpeechSynthesizer        synthesizer;
        vector<string>              words;
        bool                        redBackground;
};
