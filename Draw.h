#ifndef DRAW_H
#define DRAW_H

#include "Train.h"
#include "Passenger.h"
#include "Cashier.h"
#include <ncurses.h>

class Draw
{
    public:
        Draw(int numb, Passenger **pass);
        virtual ~Draw();

        int numb;
        Passenger **pass;

        void DrawPassenger();
        void DrawScene();
        void init_colors();
        void DrawFrame();
    protected:

    private:
};

#endif // DRAW_H
