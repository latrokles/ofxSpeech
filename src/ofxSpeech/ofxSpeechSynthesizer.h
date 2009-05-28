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
 
 #include <vector>
 #include <string>
 #include <iostream>
 #include <Carbon/Carbon.h>
 
 class ofxSpeechSynthesizer
 {
    public:
        ofxSpeechSynthesizer();
        void initSynthesizer(std::string voice="");
        void selectVoice(std::string voice);
        std::vector<std::string> getListOfVoices();
        void listVoices();
        void speakWord(std::string wordToSpeak);
        
    private:
        std::vector<std::string>    voices;
        bool                        isSpeaking;
        SpeechChannel               speechChannel;
        
 };
 #endif