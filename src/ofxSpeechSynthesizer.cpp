/*
 *  ofxSpeechSynthesizer.cpp
 *  openFrameworks
 *
 *  Created by latrokles on 5/11/09.
 *  Copyright 2009 Samurai Hippo. All rights reserved.
 *
 */
 
#include "ofxSpeechSynthesizer.h"

/*
 * The constructor for the ofxSpeechSynthesizer sets the status of the synthesizer 
 * as well as populates the list of voices available in the system. This way one
 * can call listVoices and then initialize the synthesizer with one of those
 * available voices.
 */
ofxSpeechSynthesizer::ofxSpeechSynthesizer()
{
    isSpeaking = false;
    
    //-- Populate the list of available voices in the system.
    OSErr           errorStatus = noErr;
    short           numberOfVoices;
    VoiceSpec       theVoiceSpec;

    errorStatus = CountVoices(&numberOfVoices);

    if(!errorStatus)
    {
        for(int voiceIndex = 1; voiceIndex <= numberOfVoices; voiceIndex++)
        {
            VoiceDescription    theVoiceDescription;
            
            errorStatus = GetIndVoice(voiceIndex, &theVoiceSpec);
            
            if(!errorStatus)
            {
                errorStatus = GetVoiceDescription(&theVoiceSpec, &theVoiceDescription, sizeof(theVoiceDescription));
            }
            
            //-- Get the voice's name and add it to the list of available voices
            //-- The voices available vary depending on the version of the OS.
            if(!errorStatus)
            {
                size_t voiceNameLength = theVoiceDescription.name[0];
                char        voiceName[voiceNameLength];
                for(int i=0; i < voiceNameLength; i++)
                {
                    voiceName[i] = theVoiceDescription.name[i+1];
                }         
                std::string aVoice = std::string(voiceName, voiceNameLength);
                voices[aVoice] = voiceIndex;
            }
        }
    }
}

ofxSpeechSynthesizer::~ofxSpeechSynthesizer()
{
    OSErr       errorStatus;
    errorStatus = DisposeSpeechChannel(speechChannel);
}

/*
 * The initSynthesizer method creates the speech channel to be used by the 
 * synthesizer with the specified voice. If no voice is specified, then the
 * the synthesizer is initializeed with the default system voice.
 */
void ofxSpeechSynthesizer::initSynthesizer(std::string voice)
{
    OSErr           errorStatus;
    VoiceSpec       theVoiceSpec;

    if(voice == "")
    {
        //-- Create a speech channel with a null voice spec, this returns the default system voice
        currentVoice = "Default";
        errorStatus = NewSpeechChannel(NULL, &speechChannel);
    }
    else
    {
        //-- Create a speech channel with the voice spec that has the specified voice
        currentVoice = voice;
        short voiceIndex = voices[voice];
        errorStatus = GetIndVoice(voiceIndex, &theVoiceSpec);
        
        if(!errorStatus)
            errorStatus = NewSpeechChannel(&theVoiceSpec, &speechChannel);
    }
}

void ofxSpeechSynthesizer::selectVoice(std::string voice)
{
    //-- Allow for this???
}

std::map<std::string, int> ofxSpeechSynthesizer::getListOfVoices()
{
    return voices;
}

std::string ofxSpeechSynthesizer::getCurrentVoice()
{
    return currentVoice;
}

void ofxSpeechSynthesizer::listVoices()
{
    if(voices.size() > 0)
    {
        std::map<std::string, int>::iterator iter;
        for(iter = voices.begin(); iter != voices.end(); ++iter)
        {
            std::cout << iter->second << ", " << iter->first << std::endl;
        }
    }
}

void ofxSpeechSynthesizer::speakPhrase(std::string phraseToSpeak)
{
    OSErr   errorStatus;
    
    errorStatus = SpeakText(speechChannel, phraseToSpeak.c_str(), phraseToSpeak.length());
}

void ofxSpeechSynthesizer::pauseSpeaking()
{
    OSErr       errorStatus;
    errorStatus = PauseSpeechAt(speechChannel, kImmediate);
}

void ofxSpeechSynthesizer::stopSpeaking()
{
    OSErr       errorStatus;
    errorStatus = StopSpeech(speechChannel);
}

void ofxSpeechSynthesizer::continueSpeaking()
{
    OSErr       errorStatus;
    errorStatus = ContinueSpeech(speechChannel);
}

void ofxSpeechSynthesizer::setDigitByDigit(bool enable)
{
    OSErr       errorStatus;
    OSType      theMode;
    if(enable)
        theMode = modeLiteral;
    else
        theMode = modeNormal;
    
    errorStatus = SetSpeechInfo(speechChannel, soNumberMode, &theMode);
}

void ofxSpeechSynthesizer::setCharacterByCharacter(bool enable)
{
    OSErr       errorStatus;
    OSType      theMode;
    if(enable)
        theMode = modeLiteral;
    else
        theMode = modeNormal;
    
    errorStatus = SetSpeechInfo(speechChannel, soCharacterMode, &theMode);
}