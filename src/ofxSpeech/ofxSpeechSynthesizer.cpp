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
                voices.push_back(aVoice);
            }
        }
    }
}

/*
 * The initSynthesizer method creates the speech channel to be used by the 
 * synthesizer with the specified voice. If no voice is specified, then the
 * the synthesizer is initializeed with the default system voice.
 */
void ofxSpeechSynthesizer::initSynthesizer(std::string voice)
{
    std::cout << "Initiliazing synth" << std::endl;
}

void ofxSpeechSynthesizer::selectVoice(std::string voice)
{
}

std::vector<std::string> ofxSpeechSynthesizer::getListOfVoices()
{
    return voices;
}

void ofxSpeechSynthesizer::listVoices()
{
    if(voices.size() > 0)
    {
        for(int voiceIndex = 0; voiceIndex < voices.size(); voiceIndex++)
        {
            std::cout << voices[voiceIndex] << std::endl;
        }
    }
}

void ofxSpeechSynthesizer::speakWord(std::string wordToSpeak)
{
}