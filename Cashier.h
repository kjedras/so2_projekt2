#ifndef CASHIER_H
#define CASHIER_H


class Cashier
{
    public:
        Cashier();
        virtual ~Cashier();

        bool free;
        bool isFree();
        int seatNum;

        int SellTicket();

    protected:

    private:
};

#endif // CASHIER_H
