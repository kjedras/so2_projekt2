#include "Passenger.h"

Passenger::Passenger(int index)
{
    this->index = index;
    ticket=false;
    //ctor
}

Passenger::~Passenger()
{
    //dtor
}

bool Passenger::HasTicket() {
    return ticket;
}

void Passenger::TicketAquired(bool t) {
    ticket = t;
}

int Passenger::GetSeatNum() {
    return seatNum;
}

void Passenger::SetSeatNum(int seatNum) {
    this->seatNum = seatNum;
}
