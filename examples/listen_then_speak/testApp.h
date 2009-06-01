#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxSpeech.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);
        
        //-- handler for speech recognized event
        void speechRecognized(string & wordRecognized);
        
        ofxSpeechSynthesizer            synthesizer;
        ofxSpeechRecognizer             recognizer;
        ofTrueTypeFont                  displayFont;
        string                          wordToDisplay;
        int                             word_x, word_y;
        int                             r, g, b;
};

#endif
