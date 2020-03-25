#ifndef CREDIT_CARD_H
#define CREDIT_CARD_H
#include <memory>
#include "account.h"

class Account;
    class Credit_Card
    {
    protected:
        Account* owner;
        //Not smart pointer because the Credit Card
        //object does not have ownership of the account object
        float max_withdraw_allowed;
        float withdrawn;
    public:
        Credit_Card(Account* _owner, float _max_withdraw_allowed);
        ~Credit_Card();
        int withdraw(float _amount);
    };

#endif // CREDIT_CARD_H
