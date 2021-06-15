#include "Seat.h"

Seat::Seat(int index)
{
    this->index = index;
    isfree = true;
    cv.notify_all();
    //ctor
}

Seat::~Seat()
{
    //dtor
}

bool Seat::IsFree(){
    return isfree;
}

void Seat::SetIsFree(bool s) {
    isfree = s;
}

void Seat::Take(){
    
    //TODO
}

void Seat::Release(){
    cv.notify_one();
}

void Seat::SetPassId(int pid) {
    passId = pid;
}

int Seat::GetPassId(){
    return passId;
}

void Seat::SetTrain(Train *train){

    this->train = train;

}