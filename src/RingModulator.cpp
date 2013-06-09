#include "RingModulator.h"
#include "ofMain.h"

extern int bufferSize;
extern int sampleRate;

RingModulator::RingModulator(){
    state = 0;
    volume = 0.1f;
    rotationCount=1;
    phase = 0.0f;
    phaseAdder = 0.0f;
    frequency=1000;
    phaseAdderTarget = (frequency/(float)sampleRate)*TWO_PI;
}

void RingModulator::FrequencyUp(){
    frequency+=20;
    frequency = min(2000,frequency);
    phaseAdderTarget = (frequency/(float)sampleRate)*TWO_PI;
    phase=0;
}

void RingModulator::FrequencyDown(){
    frequency-=20;
    frequency = max(80,frequency);
    phaseAdderTarget = (frequency/(float)sampleRate)*TWO_PI;
    phase=0;
}

void RingModulator::changeState(){
    state=(state+1)%5;
}

void RingModulator::volumeUp(){
    volume+=0.05;
    volume = MIN(volume,1);
}


void RingModulator::volumeDown(){
    volume-=0.05;
    volume = MAX(volume,0);
}

float RingModulator::getT(){
    while(phase>TWO_PI)
    {
        phase-=TWO_PI;
    }

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



