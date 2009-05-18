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

#include "ofMain.h"
#include <Carbon/Carbon.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "ofEvents.h"
//-- Short function to clean up the detected string
void cleanUpString(std::string &stringToClean);

class ofxSpeechRecognizer
{
    public:
        ofxSpeechRecognizer();
        void initRecognizer();
        void addDictionary(const std::vector<std::string> &wordsToRecognize);
        void addDictionaryFromFile(std::string dictionaryFilename);
        void startRecognizer();
        void stopRecognizer();
        bool isListening();
        
        /*
         * Callback function for the speech recognition events in Carbon
         */
        static pascal OSErr handleSpeechDone(const AppleEvent *theAEevt, AppleEvent* reply, long refcon);
        static ofEvent<std::string>  speechRecognizedEvent;
        
    private:
        //-- Variables to store vocabulary and state
        std::vector<std::string>     vocabulary;
        bool                         listening;
        
        //-- Variables for Carbon Speech
        SRRecognitionSystem          recognitionSystem;
        SRRecognizer                 speechRecognizer;
};
#endif
 