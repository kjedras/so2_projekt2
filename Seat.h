#ifndef SEAT_H
#define SEAT_H

#include <mutex>
#include "Train.h"
#include <condition_variable>
#include <iostream>
class Seat
{
    public:
        Seat(int index);
        virtual ~Seat();

        bool isfree;
        bool IsFree();
        void Take();
        void Release();
        int index;
        int getIndex();
        int passId;
        void SetPassId(int pid);
        int GetPassId();
        void SetIsFree(bool s);

        Train *train;
        void SetTrain(Train *train);

        std::mutex lock;
        std::condition_variable cv;

    protected:

    private:
        
};

#endif // SEAT_H
