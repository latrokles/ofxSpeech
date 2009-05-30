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
        void initSynthesizer(std::string voice="");
        void selectVoice(std::string voice);
        std::map<std::string, int> getListOfVoices();
        std::string getCurrentVoice();
        void listVoices();
        void speakPhrase(std::string phraseToSpeak);
        void setDigitByDigit();
        void setCharacterByCharacter();
        
    private:
        std::map<std::string, int>  voices;
        std::string                 currentVoice;
        bool                        isSpeaking;
        SpeechChannel               speechChannel;
        
 };
 #endif