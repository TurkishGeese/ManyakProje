#pragma once

class Timer {
public:
    Timer();

    float getElapsedSeconds();
private:
    unsigned int mTime;
};