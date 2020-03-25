#ifndef SAVING_H
#define SAVING_H
#include "account.h"


    class Saving : public Account
    {
    protected:
        const float interest;
        int count;//Can't withdraw more than 3 times
    public:
        Saving(float _balance, std::string _owner);
        //Difference being that this can not be initialized without a starting balance
        ~Saving();

        virtual int withdraw(float);
        virtual int deposit(float);

        virtual void add_interest();

        const std::unique_ptr<Credit_Card>& get_credit(int _index) { return std::unique_ptr<Credit_Card>(nullptr); }
    };

#endif // SAVING_H
