#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <memory>
#include "credit_card.h"

class Credit_Card;

    class Account
    {
        int id;
    protected:
        float balance;
        std::string owner;
        bool is_active;
    public:
        Account();
        Account(float _amount, std::string _owner);
        ~Account();

        int get_id() { return id; }

        virtual int deposit(float) = 0;
        virtual int withdraw(float) = 0;

        virtual void add_interest() = 0;

        virtual const std::unique_ptr<Credit_Card>& get_credit(int _index) = 0;

        bool get_active() { return is_active; }
        void set_active(bool _v) { is_active = _v; }

        float get_balance() { return balance; }

    };

#endif // ACCOUNT_H
