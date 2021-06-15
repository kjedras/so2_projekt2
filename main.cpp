#include <iostream>
#include "Passenger.h"
#include "Train.h"
#include "Draw.h"
#include "Seat.h"
#include "Cashier.h"
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <ctime>
#include <ncurses.h>
#include <condition_variable>

#define numOfSeats 3

using namespace std;

std::atomic<bool> run(true);

Passenger *pass[10];
thread *passThread;

Train *train;
Cashier *cashier;
Seat *seat[numOfSeats];

void ExitListener(std::atomic<bool>& run)
{
    while(run) this_thread::sleep_for(chrono::milliseconds(20));
    cashier->cv.notify_all();
    train->cv.notify_all();
    for (int i = 0; i < numOfSeats; i++) seat[i]->cv.notify_all();
}

void CreateWindow() {

    cashier = new Cashier();

    for (int i = 0; i<numOfSeats; i++) {
        seat[i] = new Seat(i);
        }

    train = new Train(numOfSeats);

}

void LifeCycle(int index, std::atomic<bool>& run){

    while(run) {

        pass[index]->BuyTicket();

        if (pass[index]->HasTicket())
            pass[index]->TakeASeat(seat[pass[index]->GetSeatNum()]);

    }

}

bool IsTrainFullyLoaded() {

    if (train->GetPplCount() == numOfSeats)
        return true;
    else return false;

}

void CreatePassengers() {
    for (int i = 0; i < 10; i++) {

        pass[i] = new Passenger(i, cashier, train, &run);
        passThread[i] = thread(LifeCycle, i, std::ref(run));

    }

}

void DestroyPassengers() {

    for (int i = 0; i < 10; i++) {
        cout<<i<<endl;

        passThread[i].join();

    }

}

void Travel(std::atomic<bool>& run) {

    while(run) {
        if(IsTrainFullyLoaded()) {
            for (int i = 0; i < 3; i++) {
                pass[seat[i]->GetPassId()]->SetState("-----#TRAVELING-----");
            }
            train->Travel();
            for (int i = 0; i < 3; i++) {
                pass[seat[i]->GetPassId()]->SetState("-#LEAVING THE TRAIN-");
            }
            this_thread::sleep_for(chrono::seconds(1));
            train->SetIsBack(false);
            train->SetPplCount(0);


            for (int i = 0; i < 3; i++) {
                seat[i]->SetIsFree(true);
            }

        }
    }
}

int main()
{
    CreateWindow();
    passThread  = new thread[10];
    thread trainTh(Travel, std::ref(run));
    thread exitTh(ExitListener, std::ref(run));
    CreatePassengers();
    Draw draw = Draw(10, pass);
    draw.DrawScene();
    run.store(false);
    cout<<"Zamykanie 1"<<endl;
    trainTh.join();
    cout<<"Zamykanie 2"<<endl;
    DestroyPassengers();
    exitTh.join();
    cout<<"Koniec"<<endl;
    return 0;
}
