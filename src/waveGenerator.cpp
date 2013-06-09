#include "waveGenerator.h"
#include "ofMain.h"

extern int bufferSize;
extern int sampleRate;

waveGenerator::waveGenerator(){
    state = 0;
    volume = 0.1f;
    rotationCount=1;
    phase = 0.0f;
    phaseAdder = 0.0f;
    noteIndex = 57;

    phaseAdderTarget = (note[noteIndex]/(float)sampleRate)*TWO_PI;
}

void waveGenerator::draw(){
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);

	ofBeginShape();
	//	for (int i = 0; i < lAudio.size(); i++){
			//float x =  ofMap(i, 0, lAudio.size(), 0, 900, true);
			ofVertex(100, 100 -getT()*180.0f);
			ofVertex(100, 100 -getT()*180.0f);

	//	}
		ofEndShape(false);
}

void waveGenerator::NoteUp(){
    noteIndex+=1;
    noteIndex = min(99,noteIndex);
    phaseAdderTarget = (note[noteIndex]/(float)sampleRate)*TWO_PI;
    phase=0;
}

void waveGenerator::NoteDown(){
    noteIndex-=1;
    noteIndex = max(0,noteIndex);
    phaseAdderTarget = (note[noteIndex]/(float)sampleRate)*TWO_PI;
    phase=0;
}

void waveGenerator::changeState(){
    state=(state+1)%5;
}


void waveGenerator::volumeUp(){
    volume+=0.05;
    volume = MIN(volume,1);
}


void waveGenerator::volumeDown(){
    volume-=0.05;
    volume = MAX(volume,0);
}

float waveGenerator::getT(){
    while(phase>TWO_PI)
    {
        phase-=TWO_PI;
    }
//    phaseAdder=0.95f*phaseAdder+0.05f*phaseAdderTarget;
//    phase+=phaseAdder;
//        return(sin(phase));

	if (state == 0){ //SINE

		phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
    	phase += phaseAdder;
		float sample = sin(phase);
			return sample*volume;
		}

	else if (state == 1) //SQUARE
	{
            phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
            phase += phaseAdder;
			float sample = sin(phase);
            if(sample>0){
                sample=1;
            }
            else{
                sample=-1;
            }
            return sample*volume;
    }

    else if (state == 2) //SAW
	{
	    phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
		phase += phaseAdder;
		float sample;
           if (phase<=PI/2){
                sample=ofMap(phase,0,PI/2,0,1);
            }
            else if (phase>PI/2 && phase<=PI){
                sample=ofMap(phase,PI/2,PI,0,1);
            }
            else if (phase>PI && phase<= 3*PI/2){
                sample=ofMap(phase,PI,3*PI/2,0,1);
            }
            else if (phase>3*PI/2 && phase<= 2*PI){
                sample=ofMap(phase,3*PI/2,2*PI,0,1);
            }
            else{
                phase=0;
            }

			return sample*volume;
    }

	else if (state == 3) //TRIANGLE
	{
        phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
		phase += phaseAdder;
			float sample;
            if (phase<=PI/2){
                sample=ofMap(phase,0,PI/2,0,1);
            }
            else if (phase>PI/2 && phase<=PI){
                sample=ofMap(phase,PI/2,PI,1,0);
            }
            else if (phase>PI && phase<= 3*PI/2){
                sample=ofMap(phase,PI,3*PI/2,0,1);
            }
            else if (phase>3*PI/2 && phase<= 2*PI){
                sample=ofMap(phase,3*PI/2,2*PI,1,0);
            }
            else{
                phase=0;
            }

			return sample*volume;
    }

	else if(state==4){
            return ofRandom(0,1)*volume;
	}
}



