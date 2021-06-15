#ifndef CASHIER_H
#define CASHIER_H

#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <iostream>

class Cashier
{
    public:
        Cashier();
        virtual ~Cashier();
        
        bool isfree;
        bool GetState();
        void SetState(bool state);

        int freeSeat;
        int seatNum;
        int Sell();
        
        std::mutex lock;
        std::condition_variable cv;

        void IsReleased();

    protected:

    private:
};

#endif // CASHIER_H
