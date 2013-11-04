
# ofxSpeech 
* May 30th 2009 - by Ruben Duque (latrokles)
* Updated - Nov 4 2013 - Jeff Crouse (jefftimesten)

This addon is a wrapper around the Apple [speech recognition](https://developer.apple.com/library/mac/documentation/Carbon/Reference/Speech_Recognition_Manager/Reference/reference.html) and [speech synthesis](https://developer.apple.com/library/mac/documentation/Carbon/Reference/Speech_Synthesis_Manager/Reference/reference.html) APIs. Ergo, it is Mac only.

Check out [this video](https://www.youtube.com/watch?v=aQZA8Im3UqA) to see the "zoo" example in action.  This will give you a realistic expectation of the accuracy of the library.

## Installation:
1. Place ofxSpeech in the addons folder.

## Adding to a Project:
1. Add the ofxSpeech to your project in the IDE (Xcode presumably).
2. Add #include "ofxSpeech.h" in your testApp.h

## ofxSpeechRecognizer usage:

Two things to keep in mind before beginning:
- Add a function to your testApp.h/testApp.cpp that takes a string by reference, this function will get called when a word is recognized.
i.e.
void speechRecognized(string & wordRecognized);

- In the testApp.cpp setup() function, add the function mentioned above as a listener to a speechRecognized event. 
i.e.
	ofAddListener(recognizer.speechRecognizedEvent, this, &testApp::speechRecognized);

	ofxSpeechRecognizer recognizer;
	recognizer.initRecognizer();

- You can load a list of words to recognize from a file in your data directory containing each word
in a separate line.

	recognizer.loadDictionaryFromFile("dictionary.txt");

- Alternatively you can have a vector of words and add them that way
	vector<string> words;
	words.push_back("red");
	words.push_back("green");
	words.push_back("black");
	recognizer.loadDictionary(words);

	//startListening for words
	recognizer.startListening();

	//in the function defined in testApp.cpp place code to be executed once a given word is detected
	void testApp::speechRecognized(string & wordRecognized)
	{
	    if(wordRecognized == "red")
	        ofBackground(255, 0, 0);

	    if(wordRecognized == "green")
	        ofBackground(0, 255, 0);
	}

	//the recognized can be stopped
	recognizer.stopListening();



## ofxSpeechSynthesizer usage:

	//define and create an ofxSpeechSynthesizer object
	ofxSpeechSynthesizer synthesizer;

	//list available voices in the system
	synthesizer.listVoices();

	//initalize synthesizer with voice, if no voice is given the default system voice is used.
	synthesizer.initSynthesizer("Whisper");

	//speak a word or sentence
	synthesizer.speakPhrase("hello, this a test of the synthesizer");

	//to turn on spelling character by character
	synthesizer.setCharacterByCharacter(true);

	//to turn off spelling character by character
	synthesizer.setCharacterByCharacter(false);

	//to turn on digit by digit for numbers
	synthesizer.setDigitByDigit(true)

	//to turn off digit by digit for numbers
	synthesizer.setDigitByDigit(true)

	//to pause speaking
	synthesizer.pauseSpeaking();

	//to resume speaking
	synthesizer.continueSpeaking();

	//to stop speaking completely
	synthesizer.stopSpeaking();
