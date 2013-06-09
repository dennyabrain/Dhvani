#pragma once

#include "ofMain.h"
#include "TuioDump.h"
#include "TUIO/TuioClient.h"
#include "TuioThread.h"
#include "waveGenerator.h"
#include "Sample.h"
#include "LFO.h"
#include "RingModulator.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

//TUIO OBJECTS
        TuioThread thread;
        std::list <TuioObject *> allTuioObjects;
        std::list <TuioCursor *> allTuioCursors;

        waveGenerator oscillator[2];
        int oscFlag[2];

        Sample sample[2];
        int oscSample[2];

        LFO lfo;
        RingModulator rm;

        int objectMatrix[4][4];

//      Sample sample;
        ofSoundStream soundStream;
        void audioOut(float *input, int bufferSize, int nChannels);

//      TuioObject *tempObj1,*tempObj2;
        TuioObject *tempObj;
        TuioObject *tempObj2;

        float tempX,tempY;
        float tempSamp,tempWaveGen;

//QUICKFIX
        float sam[2];
        float osci[2];
        float low[2];
        float ring[2];
        float tempo[2];
        float tempA,tempB;
};
