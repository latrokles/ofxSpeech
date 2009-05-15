/*
 *  ofxSpeechRecognizer.h
 *  openFrameworks
 *
 *  Created by latrokles on 5/11/09.
 *  Copyright 2009 Samurai Hippo. All rights reserved.
 *
 */
 
#ifndef _OFX_SPEECH_RECOGNIZER_
#define _OFX_SPEECH_RECOGNIZER_
#define MAX_RECOGNITION_LEN 512
#include <Carbon/Carbon.h>
#include <vector>
#include <string>
#include <iostream>

#include "ofEvents.h"
/*
 * Callback function for the speech recognition events in Carbon
 */
pascal OSErr HandleSpeechDoneAppleEvent(const AppleEvent *theAEevt, AppleEvent* reply, long refcon);

class ofxSpeechRecognizer
{
    public:
        ofxSpeechRecognizer();
        void initRecognizer();
        void setCallback(void (*callback)(char *));
        void addVocabulary(std::vector<std::string> wordsToRecognize);
        void startRecognizer();
        void stopRecognizer();
        bool isListening();
        
        //testApp Callback pointer... this will be replaced by an actual
        //event and event callback using poco
        static void                 (*testAppCallback)(char *);
        
    private:
        // Variables to store vocabulary and state
        std::vector<std::string>     vocabulary;
        bool                         listening;
        
        //Variables for Carbon Speech
        SRRecognitionSystem         recognitionSystem;
        SRRecognizer                speechRecognizer;
        
        ofEvent<std::string>        speechRecognizedEvent;
    
        
};
#endif
 