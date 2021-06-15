#include "Train.h"

Train::Train(int capacity)
{
    this->capacity = capacity;
    pplCount = 0;
    isBack = false;
    state = "ON THE PLATFORM";
    cv.notify_all();
    //ctor
}

Train::~Train()
{
    //dtor
}

int Train::GetCapacity(){
    return capacity;
}

void Train::Travel(){
    state = "TRAVELING";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    state = "ON THE PLATFORM";
    isBack = true;
    pplCount = 0;

}

std::string Train::GetState(){
    return state;
}

int Train::GetPplCount(){

    return pplCount;

}

void Train::PplCountUp() {

    pplCount++;

}

void Train::PplCountDown() {

    pplCount = pplCount -1;

}

void Train::SetPplCount(int s) {
    pplCount = s;
}

bool Train::IsBack(){
    return isBack;

}

void Train::SetIsBack(bool s){
    isBack = s;
}