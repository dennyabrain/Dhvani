#include "testApp.h"
#include "TuioThread.h"
#include "TUIO/TuioObject.h"
#include "math.h"

int bufferSize = 512;
int sampleRate = 44100;
char a[20];
char b[2];
float temp;
int flagLfo=0;

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,236);
    ofEnableSmoothing();
    //ofSetCircleResolution(100);
    thread.startThread(true,false);
    tempX=0;
    tempY=0;
    tempSamp=0;
    tempWaveGen=0;
    oscFlag[0]=0;oscFlag[1]=0;
    oscSample[0]=0;oscSample[1]=0;

    sam[0]=1;sam[1]=1;sam[2]=1;sam[3]=1;
    osci[0]=1;osci[1]=1;osci[2]=1;osci[3]=1;
    low[0]=1;low[1]=1;low[2]=1;low[3]=1;
    ring[0]=1;ring[1]=1;ring[2]=1;ring[3]=1;
    tempo[0]=0;tempo[1]=0;tempo[2]=0;tempo[3]=0;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            objectMatrix[i][j]=-1;
        }
    }

//SOUND

sample[0].load("sounds/beat3.wav");
sample[0].setLooping(true);
sample[0].play();

sample[1].load("sounds/beat4.wav");
sample[1].setLooping(true);
sample[1].play();


soundStream.setup(this, 2, 0,sampleRate, bufferSize, 4);
ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update(){
    ofSoundUpdate();

//CHANGE NOTE
    for(long i=2;i<4;i++){
    tempObj=thread.client.getTuioObjectBySymbolID(i);
        if(tempObj!=NULL){
            if(tempObj->getRotationSpeed()>0.5){
                oscillator[i-2].NoteUp();
            }
            if(tempObj->getRotationSpeed()<-0.5){
                oscillator[i-2].NoteDown();
            }
    }
   }
    tempObj=thread.client.getTuioObjectBySymbolID(4);
        if(tempObj!=NULL){
            if(tempObj->getRotationSpeed()>0.5){
                lfo.FrequencyUp();
            }
            if(tempObj->getRotationSpeed()<-0.5){
                lfo.FrequencyDown();
            }
        }

    tempObj=thread.client.getTuioObjectBySymbolID(5);
        if(tempObj!=NULL){
            if(tempObj->getRotationSpeed()>0.5){
                rm.FrequencyUp();
            }
            if(tempObj->getRotationSpeed()<-0.5){
                rm.FrequencyDown();
            }
        }

    for(long i=0;i<2;i++){
    tempObj=thread.client.getTuioObjectBySymbolID(i);
        if(tempObj!=NULL){
            if(tempObj->getRotationSpeed()>0.5){
                sample[i].setSpeed(sample[i].getSpeed()+0.1);
            }
            if(tempObj->getRotationSpeed()<-0.5){
                sample[i].setSpeed(sample[i].getSpeed()-0.1);
            }
    }
   }

//CHANGE WAVEFORM
/*for(std::list<TuioCursor*>::iterator ci=allTuioCursors.begin();ci != allTuioCursors.end();++ci){
            for(std::list<TuioObject*>::iterator ci2=allTuioObjects.begin();ci2 != allTuioObjects.end();++ci2){
                if(sqrt(pow((*ci2)->getX() - (*ci)->getX(),2) + pow((*ci2)->getY() - (*ci)->getY(),2)) < 0.25){//Distance < threshold
                        oscillator[0].changeState();
                        break;
                }
            }
    }
*/
for(std::list<TuioCursor*>::iterator ci=allTuioCursors.begin();ci != allTuioCursors.end();++ci){
    tempObj=thread.client.getTuioObjectBySymbolID(2);
    if(tempObj!=NULL){
        if(sqrt(pow(tempObj->getX() - (*ci)->getX(),2) + pow(tempObj->getY() - (*ci)->getY(),2)) < 0.075){
            oscillator[0].changeState();
        }
    }
    tempObj=thread.client.getTuioObjectBySymbolID(3);
    if(tempObj!=NULL){
        if(sqrt(pow(tempObj->getX() - (*ci)->getX(),2) + pow(tempObj->getY() - (*ci)->getY(),2)) < 0.075){
            oscillator[1].changeState();
        }
    }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(236,236,236);
    ofSetColor(200,200,200);
    ofEllipse(ofGetWidth()/2,ofGetHeight()/2,10,10);
    ofSetColor(220,220,220);
    allTuioObjects = thread.client.getTuioObjects();
    allTuioCursors = thread.client.getTuioCursors();

//CHECKING FOR PRESENCE OF WAVE OBJECTS
    for(long x=2;x<=3;x++){
        tempObj=thread.client.getTuioObjectBySymbolID(x);
        if(tempObj!=NULL){
            oscFlag[x-3]=1;
            objectMatrix[x-2][1]=1;
        }
        else{
            objectMatrix[x-2][1]=-1;
            oscFlag[x-2]=0;
        }
    }

//CHECKING FOR PRESENCE OF SAMPLE OBJECTS
    for(long x=0;x<=1;x++){
        tempObj=thread.client.getTuioObjectBySymbolID(x);
        if(tempObj!=NULL){
            oscSample[x]=1;
            objectMatrix[x][0]=1;
        }
        else{
            objectMatrix[x][0]=-1;
            oscSample[x]=0;
        }
    }
//Establishing Connection between LFO and OSC
        tempObj=thread.client.getTuioObjectBySymbolID(4);
        if(tempObj!=NULL){
                for(long x=2;x<=3;x++){
                    tempObj2=thread.client.getTuioObjectBySymbolID(x);
                    if(tempObj2!=NULL){
                        if(sqrt(pow((tempObj2)->getX() - (tempObj)->getX(),2) + pow((tempObj2)->getY() - (tempObj)->getY(),2)) < 0.90){//Distance < threshold
                            ofSetColor(204,101,255);
                            ofSetLineWidth(100);
                            ofLine(1280*(tempObj)->getX()-110,800*(tempObj)->getY()-30,1280*(tempObj2)->getX()-110,800*(tempObj2)->getY()-30);
                            objectMatrix[x-2][2]=1;
                        }
                        else{
                            objectMatrix[x-2][2]=-1;
                        }
                    }
                }
        }


//Establishing Connection between RingModulator and SAMPLE  OBJECT
        tempObj=thread.client.getTuioObjectBySymbolID(5);
        if(tempObj!=NULL){
                for(long x=0;x<=1;x++){
                    tempObj2=thread.client.getTuioObjectBySymbolID(x);
                    if(tempObj2!=NULL){
                        if(sqrt(pow((tempObj2)->getX() - (tempObj)->getX(),2) + pow((tempObj2)->getY() - (tempObj)->getY(),2)) < 0.90){//Distance < threshold
                            ofSetColor(204,101,255);
                            ofSetLineWidth(100);
                            ofLine(1280*(tempObj)->getX()-110,800*(tempObj)->getY()-30,1280*(tempObj2)->getX()-110,800*(tempObj2)->getY()-30);
                            objectMatrix[x][3]=1;
                        }
                        else{
                            objectMatrix[x][3]=-1;
                        }
                    }
                }
        }

//DRAWING ALL THE OBJECTS
    if(allTuioObjects.front()==NULL){
        //cout<<"NULL DETECTED"<<endl;
        tempX=0;
        tempY=0;
    }
    else{
      for(std::list<TuioObject*>::iterator ci=allTuioObjects.begin();ci != allTuioObjects.end();++ci){
            tempX = (*ci)->getX();
            tempY = (*ci)->getY();
            ofSetColor(204,101,255);
            ofEllipse(1280*tempX-110,800*tempY-30,200,200);
            ofSetColor(236,236,236);
            ofEllipse(1280*tempX-110,800*tempY-30,150,150);
      }
    }

//DRAWING ALL CURSORS
    if(allTuioCursors.front()==NULL){
        //cout<<"NULL DETECTED"<<endl;
        tempX=0;
        tempY=0;
    }
    else{
      for(std::list<TuioCursor*>::iterator ci=allTuioCursors.begin();ci != allTuioCursors.end();++ci){
            tempX = (*ci)->getX();
            tempY = (*ci)->getY();
            ofSetColor(204,101,255);
            ofEllipse(1280*tempX,800*tempY,10,10);
      }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key=='s'){
        sample[0].setSpeed(0.25);
        ofSetColor(204,101,255);
        ofEllipse(200,200,10,10);
    }


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    //soundStream.start();

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    //soundStream.stop();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

void testApp::exit(){
    thread.stopThread();
}

void testApp::audioOut(float *output, int bufferSize, int nChannels){
         for (int i=0;i<bufferSize;i++){
             for(int x=0;x<2;x++){
                if(objectMatrix[x][0]==1){
                    sam[x]=sample[x].update();
                }
                else{
                    sam[x]=0;
                }

                if(objectMatrix[x][1]==1){
                    osci[x]=oscillator[x].getT();
                }
                else{
                    osci[x]=0;
                }
                if(objectMatrix[x][2]==1){
                    low[x]=10*lfo.getT();
                }
                else{
                    low[x]=1;
                }
                if(objectMatrix[x][3]==1){
                    ring[x]=10*rm.getT();
                }
                else{
                    ring[x]=1;
                }
            tempo[x]=((osci[x]*low[x])+(sam[x]*ring[x]));
            }
            temp=((tempo[0]+tempo[1]+tempo[2]+tempo[3]));

            //temp=ofMap(temp,0,(allTuioObjects.size()+1),0,1);
            output[i*nChannels] = temp;
            output[i*nChannels+1] = temp;
            //cout<<"LFO = "<<low[0]<<" "<<low[1]<<" "<<low[2]<<" "<<low[3]<<" "<<endl;
            temp=0;
        }
}




