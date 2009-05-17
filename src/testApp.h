#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxSpeech.h"

class testApp : public ofBaseApp, public ofxSpeechListener{

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
        
        //-- test event handler for speech recognition, 
        //-- I will probably just subclass testApp as it is the preferred method.
        void speechRecognized(ofxSpeechArgs & speechArgs);
        
        //-- test stuff for speech addon
        ofxSpeechRecognizer         recognizer;
        vector<string>              words;
        bool                        redBackground;
};

#endif
