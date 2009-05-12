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
    OSErr errorStatus;
    
    //-- Install eventHandler
    errorStatus = AEInstallEventHandler(kAESpeechSuite, kAESpeechDone, NewAEEventHandlerUPP(HandleSpeechDoneAppleEvent), 0, false);
    
    //-- Open the recognition system
    errorStatus = SROpenRecognitionSystem(&recognitionSystem, kSRDefaultRecognitionSystemID);
    
    //-- Override system defaults
    if(false && !errorStatus)
    {
        short feedbackModes = kSRNoFeedbackNoListenModes;
        errorStatus         = SRSetProperty(recognitionSystem, kSRFeedbackAndListeningModes, &feedbackModes, sizeof(feedbackModes));
    }
    
    //-- Create a recognizer that uses the default speech source (microphone)
    if(!errorStatus)
    {
        errorStatus = SRNewRecognizer(recognitionSystem, &speechRecognizer, kSRDefaultSpeechSource);
    }
}

void ofxSpeechRecognizer::addVocabulary(std::vector<std::string> wordsToRecognize)
{
    OSErr               errorStatus;
    SRLanguageModel     speechLanguageModel;
    const char *        languageModelName = "<Single Model>";
    
    vocabulary = wordsToRecognize;
    
    //-- Make language model
    errorStatus = SRNewLanguageModel(recognitionSystem, &speechLanguageModel, languageModelName, strlen(languageModelName));
    
    //-- Add words to the language model
    if(!errorStatus)
    {
        for(int wordIndex = 0; wordIndex < vocabulary.size(); wordIndex++)
        {
            //-- SRAddText requires c strings so need to convert, or maybe we should 
            //-- pass a vector of const char * to begin with, something to think about.
            const char * word = vocabulary[wordIndex].c_str();
            errorStatus = SRAddText(speechLanguageModel, word, strlen(word), 0);
        }
    }
    
    //-- If there's an error adding the words, release the language model
    if(errorStatus)
    {
        SRReleaseObject(speechLanguageModel);
    }
    //-- else set the language model in the system and release model
    else
    {
        errorStatus = SRSetLanguageModel(speechRecognizer, speechLanguageModel);
        SRReleaseObject(speechLanguageModel);
    }
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

pascal OSErr HandleSpeechDoneAppleEvent(const AppleEvent *theAEevt, AppleEvent* reply, long refcon)
{
    std::cout << "Speech Event Detected" << std::endl;
}