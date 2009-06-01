/*
 *  ofxSpeechSynthesizer.h
 *  openFrameworks
 *
 *  Created by latrokles on 5/11/09.
 *  Copyright 2009 Samurai Hippo. All rights reserved.
 *
 */
 
 #ifndef _OFX_SPEECH_SYNTHESIZER_
 #define _OFX_SPEECH_SYNTHESIZER_
 
 #include <map>
 #include <string>
 #include <iostream>
 #include <Carbon/Carbon.h>
 
 class ofxSpeechSynthesizer
 {
    public:
        ofxSpeechSynthesizer();
        ~ofxSpeechSynthesizer();
        
        //-- Initiallize the speech synthesizer with a voice. If no voice is selected,
        //-- then the synthesizer starts with the default system voice
        void initSynthesizer(std::string voice="");
        
        //-- You can select a new voice for the system (not implemented yet)
        void selectVoice(std::string voice);
        
        //-- Returns a map containing a list of voices and their index number in the system
        std::map<std::string, int> getListOfVoices();
        
        //-- Returns a string with the name of the currently selected voice
        std::string getCurrentVoice();
        
        //-- Displays a list of the available voices in the system
        void listVoices();
        
        //-- Uses the established speech channel to speak a phrase or text
        void speakPhrase(std::string phraseToSpeak);
        
        //-- Pauses speaking immediatly, even if it's in the middle of a sentence or word.
        //-- It can be resumed with continue speaking
        void pauseSpeaking();
        
        //-- Stops speaking completely.
        void stopSpeaking();
        
        //-- Continues speaking from the point at which pauseSpeaking was called.
        void continueSpeaking();
        
        //-- Sets the synthesizer so that it speaks numbers in a digit by digit manner
        void setDigitByDigit(bool enabled);
        
        //-- Sets the synthesizer so that it spells out words, character by character
        //-- This spelling out includes digits as well (bug maybe?)
        void setCharacterByCharacter(bool enabled);
        
    private:
        std::map<std::string, int>  voices;
        std::string                 currentVoice;
        bool                        isSpeaking;
        SpeechChannel               speechChannel;
        
 };
 #endif