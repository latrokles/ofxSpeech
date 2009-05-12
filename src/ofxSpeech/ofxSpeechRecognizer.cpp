/*
 *  ofxSpeechRecognizer.cpp
 *  openFrameworks
 *
 *  Created by latrokles on 5/11/09.
 *  Copyright 2009 Samurai Hippo. All rights reserved.
 *
 */
#include "ofxSpeechRecognizer.h"

ofxSpeechRecognizer::ofxSpeechRecognizer()
{
    listening = false;
}

void ofxSpeechRecognizer::initRecognizer()
{
}

void ofxSpeechRecognizer::addVocabulary(std::vector<std::string> wordsToRecognize)
{
}

void ofxSpeechRecognizer::startRecognizer()
{
    OSErr statusError;
    statusError = SRStartListening(speechRecognizer);
    listening = true;
}

void ofxSpeechRecognizer::stopRecognizer()
{
    OSErr statusError;
    statusError = SRStopListening(speechRecognizer);
    listening = false;
}

bool ofxSpeechRecognizer::isListening()
{
    return listening;
}

pascal OSErr HandleSpeechDoneAppleEvent(AppleEvent *theAEevt, AppleEvent* reply, long refcon)
{
}