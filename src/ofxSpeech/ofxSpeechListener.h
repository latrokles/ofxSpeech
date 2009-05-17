/*
 *  ofxSpeechRecognizer.cpp
 *  openFrameworks
 *
 *  Created by latrokles on 5/16/09.
 *  Copyright 2009 Samurai Hippo. All rights reserved.
 *
 */
 
#ifndef _OFX_SPEECH_LISTENER_
#define _OFX_SPEECH_LISTENER_

#include <string>

#include "ofEvents.h"

/*
 * Speech Event Args definition
 */
class ofxSpeechArgs: public ofEventArgs
{
    public:
        std::string         word;
};

/*
 * ofxSpeechEvents
 */
 class ofxSpeechEvents
 {
    public:
        ofEvent<ofxSpeechArgs>      speechRecognized;
        ofEvent<ofxSpeechArgs>      speechDone;
 };

class ofxSpeechListener
{
    public:
        virtual ~ofxSpeechListener() {}
        virtual void speechRecognized(ofxSpeechArgs & speechArgs) = 0;
};

extern ofxSpeechEvents             speechEvents;
#endif