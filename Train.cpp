#include "Train.h"

Train::Train(int capacity)
{
    this->capacity = capacity;
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

    std::this_thread::sleep_for(std::chrono::seconds(10));

}
