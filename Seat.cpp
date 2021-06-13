#include "Seat.h"

Seat::Seat(int index)
{
    this->index = index;
    taken = false;
    //ctor
}

Seat::~Seat()
{
    //dtor
}

bool Seat::IsTaken(){
    return taken;
}

void Seat::Take(){
    taken = true;
}

bool Seat::TryTake(){
    return lock.try_lock();
}

void Seat::Release(){
    lock.unlock();
}

void Seat::SetPassId(int pid) {
    passId = pid;
}

int Seat::GetPassId(){
    return passId;
}
