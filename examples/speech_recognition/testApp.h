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
        
        //-- Define function to handle the speech recognition event
        void speechRecognized(string & wordRecognized);
        

        ofxSpeechRecognizer         recognizer;
        bool                        drawCircle;
        int                         circle_x;
        int                         circle_y;
        int                         circle_radius;
};

#endif
