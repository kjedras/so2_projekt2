#include <iostream>
#include "Passenger.h"
#include "Train.h"
#include "Draw.h"
#include "Seat.h"
#include <thread>
#include <mutex>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <ctime>
#include <ncurses.h>
#inlcude <queue>
#include <condition_variable>

#define numOfSeats 3

using namespace std;

std::atomic<bool> runningLoop;
int trainLoad;

condition_variable cashierOccupiedSignal;
condition_variable trainAwaySignal;

mutex cashierMutex;
mutex travelingMutex;
mutex boardMutex;
mutex queueMutex;

vector<Passenger*> pass;
vector<thread> passThread;

bool isTrainFull;
bool isCashierOccupied;

Draw *draw;
Train *train;
Cashier *cashier;
Seat *seat[numOfSeats];

void Finish() {

    while(runningLoop) {

        cbreak();
        noecho();
        char key = getch();
        if (key == 'q') {

            runningLoop = false;
            cashierOccupiedSignal.notify_all();
            trainAwaySignal.notify_all();

        } else this_thread::sleep_for(chrono::milliseconds(50));

    }
}

void Render() {

    while(runningLoop) {

        //TODO

    }
}

void CreateWindow() {

    draw = new Draw();
    cashier = new Cashier();

    for (int i = 0; i<numOfSeats; i++) {
        seat[i] = new Seat();

    train = new Train(numOfSeats);

}

void LifeCycle(int index){

    while(runningLoop) {
        while(!pass[index]->HasTicket()){
            if (isCashierOccupied) {

                unique_lock<mutex> queueLock(queueMutex);
                cashierOccupiedSignal.wait(queueLock)
                buyTicket(index);
                queueLock.unlock();

            } else buyTicket(index);}
        while(pass[index]->HasTicket()){

            unique_lock<mutex> boardLock(boardMutex);

            while(isTrainFull) trainAwaySignal.wait(boardLock);

            if (seat[pass[index]->GetSeatNum()].TryTake()){
                trainLoad++;
            }
            //boardLock.unlock()

    }
}

bool IsTrainFullyLoaded() {

    return (trainLoad == train->GetCapacity());

}

void CreatePassengers() {

    for (int i = 0; i < 10; i++) {

        pass.push_back(new Passenger());
        passThread.push_back(thread(LifeCycle, i));

    }

}

void DestroyPassengers() {

    for (int i = 0; i < passThread.size(); i++) {

        passThread[i].join();

    }

}

void buyTicket(int i) {

    unique_lock<mutex> lockCashier(cashierMutex);

    isCashierOccupied = true;

    lockCashier.unlock();

    pass[i]->SetSeatNum() = cashier->SellTicket();

    pass[i]->TicketAquired(true);

    isCashierOccupied = false;

    cashierOccupiedSignal.notify_one();

}

void boardTrain(int i) {


    /*
    unique_lock<mutex> lockPass(boardMutex);
    trainLoad++;
    trainAwaySignal.wait(lockPass);
    lockPass.unlock();
    pass[i]->TicketAquired(false);
    */
}

void Travel() {

    while(runningLoop) {

        if(IsTrainFullyLoaded()) {

            //unique_lock<mutex> lockTrain(travelingMutex);

            isTrainFull = true;

            //lockTrain.unlock();

            train->Travel();
            trainLoad = 0;
            isTrainFull = false;
            for (int i = 0; i < numOfSeats; i++){
                seat[i]->Release();
                pass[seat[i]->GetPassId()]->TicketAquired(false);
            }
            trainAwaySignal.notify_all();
        }
    }
}

int main(int argc, char *argv[])
{
    initscr();
    CreateWindow();
    thread scene(Render);
    thread train(Travel);
    CreatePassengers();
    thread exitProgram(Exit);
    scene.join();
    train.join();
    exitProgram.join();
    DestroyPassengers();

    return 0;
}
