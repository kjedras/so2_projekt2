#ifndef PASSENGER_H
#define PASSENGER_H

#include "Seat.h"
#include "Train.h"
#include "Cashier.h"
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <atomic>

class Passenger
{
    public:
        Passenger(int index, Cashier *cashier, Train *train, std::atomic<bool> *run);
        virtual ~Passenger();

        int index;
        bool ticket;
        int seatNum;
        Cashier *cashier;
        Train *train;

        std::atomic<bool> *run;
        std::string state;
        void SetState(std::string s);
        std::string GetState();

        int tixCount;
        int travelCount;
        int GetTixCount();
        int GetTravelCount();

        void SetCashier(Cashier *cashier);
        bool HasTicket();
        void TicketAquired(bool t);
        void BuyTicket();
        void TakeASeat(Seat *seat);

        int GetSeatNum();
        void SetSeatNum(int seatNum);

    protected:

    private:
};

#endif // PASSENGER_H
