#ifndef BASIC_CREDIT_CARD_H
#define BASIC_CREDIT_CARD_H
#include "credit_card.h"
#include "account.h"
#include "error_codes.h"


    class Basic_Credit_Card : public Credit_Card
    {
    public:
        Basic_Credit_Card(Account* _owner);
        ~Basic_Credit_Card();
    };

#endif // BASIC_CREDIT_CARD_H
