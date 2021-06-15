#ifndef TRAIN_H
#define TRAIN_H

#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <atomic>

class Train
{
    public:
        Train(int capacity);
        virtual ~Train();

        int capacity;

        std::atomic<int> pplCount;
        bool isBack;

        std::string state;
        std::string GetState();
        
        bool IsBack();
        void SetIsBack(bool s);
        int GetPplCount();
        void PplCountUp();
        void PplCountDown();
        void SetPplCount(int s);

        int GetCapacity();

        void Travel();

        std::mutex lock;
        std::condition_variable cv;

    protected:

    private:
};

#endif // TRAIN_H
