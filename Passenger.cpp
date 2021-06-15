#include "Passenger.h"

Passenger::Passenger(int index, Cashier *cashier, Train *train, std::atomic<bool> *run)
{
    this->index = index;
    this->cashier = cashier;
    this->train = train;
    this->run = run;
    ticket=false;
    tixCount = 0;
    travelCount = 0;

    state = "IN QUEUE";
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

void Passenger::SetCashier(Cashier *cashier) {

    this->cashier = cashier;

}

void Passenger::BuyTicket() {
    if (this->run->load()) {
        state = "------IN QUEUE------";
        std::unique_lock<std::mutex> lk(cashier->lock);
        cashier->cv.wait(lk, [&]() {return cashier->GetState();});
        cashier->SetState(false);
        state = "--#BUYING A TICKET--";
        SetSeatNum(cashier->Sell());
        TicketAquired(true);
        tixCount++;
        lk.unlock();
        cashier->SetState(true);
        cashier->cv.notify_all();
        state = "#WAITING FOR ARRIVAL";
    }

}

void Passenger::TakeASeat(Seat *seat) {
    if (this->run->load()) {
        std::unique_lock<std::mutex> lk1(seat->lock);
        seat->cv.wait(lk1, [&]() {return seat->IsFree();});
        state = "----IN THE TRAIN----";
        seat->SetIsFree(false);
        seat->SetPassId(index);
        train->PplCountUp();
        while (train->IsBack() != true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        travelCount++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        if (seat->IsFree()) lk1.unlock();

        TicketAquired(false);
    }
}

void Passenger::SetState(std::string s) {
    state = s;
}

std::string Passenger::GetState() {
    return state;
}

int Passenger::GetTixCount() {
    return tixCount;
}

int Passenger::GetTravelCount() {
    return travelCount;
}