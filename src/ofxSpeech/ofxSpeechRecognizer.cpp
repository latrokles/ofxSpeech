/*
 *  ofxSpeechRecognizer.cpp
 *  openFrameworks
 *
 *  Created by latrokles on 5/11/09.
 *  Copyright 2009 Samurai Hippo. All rights reserved.
 *
 */
#include "ofxSpeechRecognizer.h"
ofEvent<std::string>        ofxSpeechRecognizer::speechRecognizedEvent;

void cleanUpString(std::string &stringToClean)
{
    if(!stringToClean.empty())
    {
        int firstCharacter      = stringToClean.find_first_not_of(" ");
        int lastCharacter       = stringToClean.find_last_not_of(" ");
        std::string tempString  = stringToClean;
        stringToClean.erase();
        
        stringToClean           = tempString.substr(firstCharacter, (lastCharacter-firstCharacter + 1));
    }
    
}

ofxSpeechRecognizer::ofxSpeechRecognizer()
{
    listening = false;
}

void ofxSpeechRecognizer::initRecognizer()
{
    OSErr errorStatus;
    
    //-- Install eventHandler
    errorStatus = AEInstallEventHandler(kAESpeechSuite, kAESpeechDone, NewAEEventHandlerUPP((AEEventHandlerProcPtr)handleSpeechDone), 0, false);
    
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

pascal OSErr ofxSpeechRecognizer::handleSpeechDone(const AppleEvent *theAEevt, AppleEvent* reply, long refcon)
{
    //-- Some debugging output
    //std::cout << "Speech Event Detected" << std::endl;

    long                actualSize;
    DescType            actualType;
    OSErr               errorStatus = 0, recStatus = 0;
    SRRecognitionResult recognitionResult;
    char                resultStr[MAX_RECOGNITION_LEN];
    Size                len;
    
    //-- Check status of the speech recognizer
    errorStatus = AEGetParamPtr(theAEevt, keySRSpeechStatus, typeShortInteger, &actualType, (Ptr)&recStatus, sizeof(errorStatus), &actualSize);
    
    //-- Get the recognition result object from the recognizer
    if(!errorStatus && !recStatus)
    {
        errorStatus = AEGetParamPtr(theAEevt, keySRSpeechResult, typeSRSpeechResult, &actualType, (Ptr)&recognitionResult, sizeof(SRRecognitionResult), &actualSize);
    }
    
    //-- Extract the words recognized in the result object
    if(!errorStatus)
    {
        len = MAX_RECOGNITION_LEN - 1;
        errorStatus = SRGetProperty(recognitionResult, kSRTEXTFormat, resultStr, &len);
        
        if(!errorStatus)
        {
            //resultStr[0] = len;
            
            //-- We are done with the recognition result object, we can release it now
            SRReleaseObject(recognitionResult);
            
            std::string wordRecognized = std::string(resultStr);
            
            //-- Some debugging output
            std::cout << "Word recognized is: " << wordRecognized << std::endl;
            
            //-- Clean up leading and trailing blanks in the recognized string
            cleanUpString(wordRecognized);
            
            //-- Notify our speechRecognizedEvent listeners.
            ofNotifyEvent(speechRecognizedEvent, wordRecognized);
        }
    }
}