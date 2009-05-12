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
 
 class ofxSpeechSynthesizer
 {
    public:
        ofxSpeechSynthesizer();
        void initSynthesizer();
        void selectVoice(std::string voice);
        std::vector<std::string> getListOfVoices();
        void speakWord(std::string wordToSpeak);
        
    private:
        std::vector<std::string>    voices;
        
 };
 #endif