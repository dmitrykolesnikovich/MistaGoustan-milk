#ifndef MILK_TIMER_H
#define MILK_TIMER_H

#include "SDL.h"

namespace milk {
    class Timer {
    public:
        Timer();

        void start();

        void stop();

        void pause();

        void unpause();

        int milliseconds();

        float seconds();

        bool isStarted();

        bool isPaused();

    private:
        int startTicks_;
        int pausedTicks_;

        bool paused_;
        bool started_;
    };
}

#endif
