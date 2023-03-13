#include "ofApp.h"
//#include "notes.h"


//This application uses a gui slider to change the pitch of the notes and the size & colour of the circle.
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
        
    // Maximilian audio stuff
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    gui.setup();
    gui.add(mySlider.setup("Notes", 7, 1, 16));
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //circle size controlled by slider
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, (mySlider * 20 + 50));
    //circle colour controlled by slider
    ofSetColor((mySlider + 100), (mySlider * 25), 0);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        // handle input here
    }
    
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i){
        
        //frequency controlled by slider
        int j = mySlider;
        output[i * outChannels] = oscillator1.sinewave(frequencies[j-1]) * 1;
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}


