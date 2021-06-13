#include "Cashier.h"

Cashier::Cashier()
{
    seatNum = 0;
    //ctor
}

Cashier::~Cashier()
{
    //dtor
}

int Cashier::SellTicket(){

    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (seatNum<3) {
        seatNum++;
        return seatNum-1;
    } else {
        seatNum = 0;
        return seatNum;
    }

}
