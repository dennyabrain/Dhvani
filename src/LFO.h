#pragma once
#include <vector>

class LFO{
    public:
        int state;
        int frequency;
        float phase;
        float phaseAdder;
        float phaseAdderTarget;
        float note[100];
        int noteIndex;
        float volume;
        int rotationCount;

        LFO();

        void volumeUp();
        void volumeDown();

        void FrequencyUp();
        void FrequencyDown();

        void changeState();

        float getT();
};
