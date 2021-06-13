#ifndef PASSENGER_H
#define PASSENGER_H


class Passenger
{
    public:
        Passenger(int index);
        virtual ~Passenger();

        int index;
        bool ticket;
        int seatNum;

        bool HasTicket();
        void TicketAquired(bool t);

        int GetSeatNum();
        void SetSeatNum(int seatNum);

    protected:

    private:
};

#endif // PASSENGER_H
