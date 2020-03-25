#ifndef BASIC_PERSONAL_H
#define BASIC_PERSONAL_H
#include "account.h"
#include "credit_card.h"
#include <vector>



    class Basic_Personal : public Account
    {
        std::vector<std::unique_ptr<Credit_Card>> cr_card_list;
    public:
        Basic_Personal();
        Basic_Personal(float _balance, std::string _owner);
        ~Basic_Personal();

        int withdraw(float);
        int deposit(float);

        void add_interest();

        std::unique_ptr<Credit_Card>& get_credit(int _index) { return cr_card_list[_index]; }

        void add_basic_credit_card();
        void add_advanced_credit_card(float _amount);
        Credit_Card& get_credit_card(int _index);

    };

#endif // BASIC_PERSONAL_H
