#ifndef SEAT_H
#define SEAT_H

#include <mutex>
class Seat
{
    public:
        Seat(int index);
        virtual ~Seat();

        bool taken;
        bool isTaken();
        bool TryTake();
        void Take();
        void Release();
        int index;
        int getIndex();
        int passId;
        void SetPassId(int pid);
        int GetPassId();

    protected:

    private:
        std::mutex lock;
};

#endif // SEAT_H
