#ifndef ADVANCED_INTEREST_H
#define ADVANCED_INTEREST_H
#include "deposit.h"

    class Advanced_Interest : public Deposit
    {
    public:
        Advanced_Interest(float _balance, std::string _owner);
        ~Advanced_Interest();

        int withdraw(float);
        int deposit(float);

        void add_interest();
    };

#endif // ADVANCED_INTEREST_H
