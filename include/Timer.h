#ifndef TIMER_H
#define TIMER_H

class Timer {
    float time;
    public:
        Timer();
        void Update(float dt);
        void Restart();
        float Get();
};


#endif