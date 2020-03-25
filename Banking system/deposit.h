#ifndef DEPOSIT_H
#define DEPOSIT_H
#include "saving.h"


    class Deposit : public Saving
    {
    public:
        Deposit(float _balance, std::string _owner);
        ~Deposit();

        int withdraw(float);
        int deposit(float);

        void add_interest();

    };

#endif // DEPOSIT_H
