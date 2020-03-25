#include <iostream>
#include <cstdlib>
#include <string>

#include "bank.h"
#include "basic_personal.h"
#include "saving.h"
#include "advanced_interest.h"

#include "error_codes.h"

Bank::Bank()
{  }

Bank::~Bank()
{  }

Account& Bank::operator[](int _index)
{
    return *(customer_list[_index]);
}

void Bank::new_customer_screen()
{
    system("cls");

    std::string fname, lname, owner;
    std::cout << "Enter owner's name(first last) :";
    std::cin >> fname >> lname;
    owner = fname + " " +lname;

    float balance;
    std::cout << "Enter starting balance :";
    std::cin >> balance;
    if (balance < 0)
    {
        std::cout << "Negative value entered\n";
        pause();
        return;
    }
    std::cout << "Choose an account type:\n";
    std::cout << "1>Basic personal account\n";
    std::cout << "2>Savings account\n";
    std::cout << "3>Deposit account\n";
    std::cout << "4>Advanced interest account\n";
    int choice;
    std::cin >> choice;
    Account* acc = nullptr;
    if (choice == 1)
    {
        acc = new Basic_Personal(balance, owner);
    }
    else if (choice == 2)
    {
        if (!balance)
        {
            std::cout << "Can't start a saving account with zero starting balance\n";
            pause();
            return;
        }
        acc = new Saving(balance, owner);
    }
    else if (choice == 3)
    {
        if (!balance)
        {
            std::cout << "Can't start a deposit account with zero starting balance\n";
            pause();
            return;
        }
        acc = new Deposit(balance, owner);
    }
    else if (choice == 4)
    {
        if (!balance)
        {
            std::cout << "Can't start an advanced interest account with zero starting balance\n";
            pause();
            return;
        }
        acc = new Advanced_Interest(balance, owner);
    }
    else
    {
        std::cout << "Invalid choice\n";
        pause();
        return;
    }
    std::cout << "Account ID :" << acc->get_id() << std::endl;
    pause();
    add_customer(acc);
}

void Bank::start_screen()
{
    system("cls");
    std::cout << "Welcome to The Banking System\n";
    std::cout << "1>Add account\n";
    std::cout << "2>Manage account\n";
    std::cout << "3>Delete account\n";

    int choice;
    std::cin >> choice;
    if (choice == 1)
        new_customer_screen();
    else if (choice == 2)
        manage_customer_screen();
    else if (choice == 3)
        delete_customer_screen();
    else
    {
        std::cout << "Invalid choice\n";
        pause();
    }
    start_screen();
}

void Bank::delete_customer_screen()
{
    system("cls");
    std::cout << "ID :";
    int id;
    std::cin >> id;
    for (int i = 0; i < customer_list.size(); i++)
    {
        if (customer_list[i]->get_id() == id)
        {
            customer_list.erase(customer_list.begin() + i);
            return;
        }
    }
    std::cout << "Could not find ID\n";
    pause();
    return;
}

void Bank::manage_customer_screen()
{//Headache inducing if-else statement following
//Beware
    system("cls");
    std::cout << "ID :";
    int id;
    std::cin >> id;
    for (int i = 0; i < customer_list.size(); i++)
    {
        if (customer_list[i]->get_id() == id)
        {
            std::cout << "Current Balance :" << customer_list[i]->get_balance() << std::endl;
            std::cout << "1>Deposit\n";
            std::cout << "2>Withdraw\n";
            std::cout << "3>Withdraw from credit card\n";
            std::cout << "4>Add credit card\n";

            int choice;
            std::cin >> choice;

            if (choice == 1)
            {
                float amount;
                std::cout << "Amount :";
                std::cin >> amount;

                int res = customer_list[i]->deposit(amount);
                std::cout << parse_result(res) << std::endl;
            }
            else if (choice == 2)
            {
                float amount;
                std::cout << "Amount :";
                std::cin >> amount;
                int res = customer_list[i]->withdraw(amount);
                std::cout << parse_result(res) << std::endl;
            }
            else if (choice == 3)
            {
                std::cout << "Credit card number :";
                int number;
                std::cin >> number;

                float amount;
                std::cout << "Amount :";
                std::cin >> amount;
                int res = customer_list[i]->get_credit(number)->withdraw(amount);
                std::cout << parse_result(res) << std::endl;
            }
            else if (choice == 4)
            {
                std::cout << "\n";
                std::cout << "1>Basic Credit Card\n";
                std::cout << "2>Advanced Credit Card\n";

                int choice;
                std::cin >> choice;
                if (choice == 1)
                {
                    static_cast<Basic_Personal*>(customer_list[i].get())->add_basic_credit_card();
                }
                else if (choice == 2)
                {
                    std::cout << "Enter max withdraw limit :";
                    float amount;
                    std::cin >> amount;
                    static_cast<Basic_Personal*>(customer_list[i].get())->add_advanced_credit_card(amount);
                }
            }
            return;
        }
    }
}


std::string Bank::parse_result(int _result)
{
    if (_result == SUCCESS)
        return std::string("Success");
    else if (_result == NEGATIVE_VALUE)
        return std::string("Negative value entered");
    else if (_result == NEGATIVE_BALANCE_WITHDRAW)
        return std::string("Balance not enough");
    else if (_result == INACTIVE_ACCOUNT)
        return std::string("Inactive account");
    else if (_result == ACCOUNT_WITHDRAW_LIMIT_REACHED)
        return std::string("Account withdraw limit reached");
    else if (_result == CREDIT_CARD_LIMIT_REACHED)
        return std::string("Credit card limit reached");
}
