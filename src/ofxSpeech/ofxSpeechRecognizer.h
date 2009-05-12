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

#include <Carbon/Carbon.h>
#include <vector>
#include <string>
#include <iostream>

/*
 * Callback function for the speech recognition events in Carbon
 */
pascal OSErr HandleSpeechDoneAppleEvent(const AppleEvent *theAEevt, AppleEvent* reply, long refcon);

class ofxSpeechRecognizer
{
    public:
        ofxSpeechRecognizer();
        void initRecognizer();
        void addVocabulary(std::vector<std::string> wordsToRecognize);
        void startRecognizer();
        void stopRecognizer();
        bool isListening();
        
     private:
        // Variables to store vocabulary and state
        std::vector<std::string>     vocabulary;
        bool                         listening;
        
        //Variables for Carbon Speech
        SRRecognitionSystem         recognitionSystem;
        SRRecognizer                speechRecognizer;
};
#endif
 