/*
 *  ofxSpeechSynthesizer.cpp
 *  openFrameworks
 *
 *  Created by latrokles on 5/11/09.
 *  Copyright 2009 Samurai Hippo. All rights reserved.
 *
 */
 
#include "ofxSpeechSynthesizer.h"

ofxSpeechSynthesizer::ofxSpeechSynthesizer()
{
    isSpeaking = false;
}

void ofxSpeechSynthesizer::initSynthesizer()
{
    std::cout << "Initiliazing synth" << std::endl;
    OSErr           errorStatus = noErr;
    short           numberOfVoices;
    VoiceSpec       theVoiceSpec;

    errorStatus = CountVoices(&numberOfVoices);

    if(!errorStatus)
    {
        //std::cout << "listing voices" << std::endl;
        for(int voiceIndex = 1; voiceIndex <= numberOfVoices; voiceIndex++)
        {
            VoiceDescription    theVoiceDescription;
            
            errorStatus = GetIndVoice(voiceIndex, &theVoiceSpec);
            
            if(!errorStatus)
            {
                //std::cout << "getting voice description" << std::endl;
                errorStatus = GetVoiceDescription(&theVoiceSpec, &theVoiceDescription, sizeof(theVoiceDescription));
                //std::cout << errorStatus << std::endl;
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

void ofxSpeechSynthesizer::selectVoice(std::string voice)
{
}

std::vector<std::string> ofxSpeechSynthesizer::getListOfVoices()
{
    return voices;
}

void ofxSpeechSynthesizer::displayVoices()
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