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
		
        ofxSpeechSynthesizer    synthesizer;
        ofVideoGrabber          camera;
        int                     cam_x;
        int                     cam_y;
        int                     cam_width;
        int                     cam_height;
    
};
