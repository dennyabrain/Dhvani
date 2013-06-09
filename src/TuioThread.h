#pragma once
#include "ofMain.h"
#include "TuioDump.h"

class TuioThread : public ofThread{
    public:
        TuioDump dump;
        TuioClient client;
        void threadedFunction();
};





