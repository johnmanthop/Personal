#ifndef BANK_H
#define BANK_H
#include <vector>
#include <memory>
#include <conio.h>

#include "account.h"


class Bank
{
    std::vector<std::unique_ptr<Account>> customer_list;
    void add_customer(Account* _acc)
    {
        customer_list.push_back(std::unique_ptr<Account>(_acc));
    }

    void pause() { _getch(); }
    std::string parse_result(int _result);
public:
    Bank();
    ~Bank();

    Account& operator[](int _index);


    void new_customer_screen();
    void manage_customer_screen();
    void delete_customer_screen();

    void start_screen();
};

#endif // BANK_H
