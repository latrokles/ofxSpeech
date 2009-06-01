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

/*
 * Removes leading and trailing blank space from stringToClean.
 */
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

/*
 * Instantiates an ofxSpeechRecognizer object and sets listening to false
 */
ofxSpeechRecognizer::ofxSpeechRecognizer()
{
    listening = false;
}

ofxSpeechRecognizer::~ofxSpeechRecognizer()
{
    OSErr       errorStatus;
    stopListening();
    
    errorStatus = SRReleaseObject(speechRecognizer);
    errorStatus = SRCloseRecognitionSystem(recognitionSystem);
}
/*
 * Initializes the recognizer, by opening the recognition system, creating a 
 * a recognizer, settting listening parameters, selecting a speech source (for 
 * now just the microphone), and installing an event handler for OSX speech 
 * event.
 */
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

/*
 * creates a language model and adds the words contained in the wordsToRecognize
 * vector to said language model.
 */
void ofxSpeechRecognizer::loadDictionary(const std::vector<std::string> &wordsToRecognize)
{
    //-- If wordsToRecognize is empty, don't bother
    if(!wordsToRecognize.empty())
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
}

/*
 * Opens dictionaryFilename, reads its contents and loads them into a vector of
 * strings to them pass them along to addDictionary.
 */
void ofxSpeechRecognizer::loadDictionaryFromFile(std::string dictionaryFilename)
{
    dictionaryFilename          = ofToDataPath(dictionaryFilename);
    std::vector<std::string>    dictionary;
    std::string                 dictionaryWord;
    std::ifstream               dictionaryFile(dictionaryFilename.data(), std::ios_base::in);
    
    //-- Iterate through file and add each line to the dictionary vector
    while(getline(dictionaryFile, dictionaryWord, '\n'))
    {
        dictionary.push_back(dictionaryWord);
    }
    dictionaryFile.close();
    
    //-- Already wrote a function to add a vector of strings, may as well use it.
    /* It may be two inefficient since I am iterating through the same contents 
     * twice, once here and the other in addDictionary, may be worth it just to
     * use the same code here and be done with it, or just refactor it in a way
     * that I can do keep the language model creation code in one place. 
     * Something to consider.
     */
    loadDictionary(dictionary);
}

/*
 * Starts the recognizer if it's not already running
 */
void ofxSpeechRecognizer::startListening()
{
    if(!listening)
    {
        OSErr statusError;
        statusError = SRStartListening(speechRecognizer);
        listening = true;
    }
}

/*
 *  Stops the recoginzer if it's running
 */
void ofxSpeechRecognizer::stopListening()
{
    if(listening)
    {
        OSErr statusError;
        statusError = SRStopListening(speechRecognizer);
        listening = false;
    }
}

/*
 * Returns the status of the reconizer
 */
bool ofxSpeechRecognizer::isListening()
{
    return listening;
}

/*
 *  Handles the speechDone event as specified by the OSX speech recognition
 *  manager reference. It extracts the string that was recognized, converts it
 *  into a nice C++ string, cleans it up, and notifies any listeners of the 
 *  word detected.
 */
pascal OSErr ofxSpeechRecognizer::handleSpeechDone(const AppleEvent *theAEevt, AppleEvent* reply, long refcon)
{
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
            //-- We are done with the recognition result object, we can release it now
            SRReleaseObject(recognitionResult);
            
            std::string wordRecognized = std::string(resultStr);
            
            /*
             * Since the resulting string from the recgontionResult is 255 characters 
             * in length, we want to strip out any leading or trailing blank space so 
             * that we can compare it easily in the event handler inside of testApp
             */
            cleanUpString(wordRecognized);
            
            //-- Notify our speechRecognizedEvent listeners.
            ofNotifyEvent(speechRecognizedEvent, wordRecognized);
        }
    }
}