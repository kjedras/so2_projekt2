#include "Cashier.h"


Cashier::Cashier()
{
    seatNum = 0;
    isfree = true;
    cv.notify_all();
    //ctor
}

Cashier::~Cashier()
{
    //dtor
}

void Cashier::IsReleased(){

    cv.notify_all();

}

bool Cashier::GetState(){

    return isfree;

}

void Cashier::SetState(bool state) {

    isfree = state;

}

int Cashier::Sell() {

    std::this_thread::sleep_for(std::chrono::seconds(2));
    if (seatNum < 3) {
        seatNum++;
        return seatNum-1;
    } else {
        seatNum = 1;
        return 0;
    }

}