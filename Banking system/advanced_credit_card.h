#ifndef ADVANCED_CREDIT_CARD_H
#define ADVANCED_CREDIT_CARD_H
#include "account.h"
#include "credit_card.h"


    class Advanced_Credit_Card : public Credit_Card
    {
    public:
        Advanced_Credit_Card(Account* _owner);
        Advanced_Credit_Card(Account* _owner, float _max_withdraw_allowed);
        ~Advanced_Credit_Card();

        void withdraw(float _amount);
    };

#endif // ADVANCED_CREDIT_CARD_H
