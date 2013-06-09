#pragma once
#include <vector>

class RingModulator{
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

        RingModulator();

        void volumeUp();
        void volumeDown();

        void FrequencyUp();
        void FrequencyDown();

        void changeState();

        float getT();
};
