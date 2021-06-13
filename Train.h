#ifndef TRAIN_H
#define TRAIN_H


class Train
{
    public:
        Train(int capacity);
        virtual ~Train();

        int capacity;

        int GetCapacity();

        void Travel();

    protected:

    private:
};

#endif // TRAIN_H
