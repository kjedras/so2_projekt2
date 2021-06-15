#include "Draw.h"

Draw::Draw(int numb, Passenger **pass)
{
    this->numb = numb;
    this->pass = pass;

    initscr();
    init_colors();
    noecho();
    curs_set(0);
    //ctor
}

Draw::~Draw()
{
    //dtor
}

void Draw::init_colors(){
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_CYAN);
    init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
}

void Draw::DrawScene() {
    int c;
    nodelay(stdscr, TRUE);
    while ((c = getch()) != 'q') {
        DrawFrame();
        DrawPassenger();
        refresh();
    }
    endwin();
}

void Draw::DrawFrame(){

    move(1,36);
    printw("Pasazerowie");


    for (int i = 0; i < numb; i++) {
        move(3 + i*2, 17);
        addch(i + '0');
        attron(COLOR_PAIR(1));
        move(3 + i * 2, 20);
        addch('[');
        move(3 + i * 2, 41);
        addch(']');
        attroff(COLOR_PAIR(1));
    }
}

void Draw::DrawPassenger(){

    for (int i = 0; i < numb; i++) {

        attron(COLOR_PAIR(6));
        std::string state = pass[i]->GetState();
        std::string tix = std::to_string(pass[i]->GetTixCount());
        std::string travel = std::to_string(pass[i]->GetTravelCount());

        move(3 + i * 2, 21);
        printw(state.c_str());
        move(3 + i * 2, 44);
        printw("Kupionych biletow: ");
        move(3 + i * 2, 65);
        printw(tix.c_str());
        move(3 + i * 2, 70);
        printw("Podrozy: ");
        move(3 + i * 2, 81);
        printw(travel.c_str());
    }
}