#include "basic_credit_card.h"
#include "account.h"
#include "error_codes.h"

Basic_Credit_Card::Basic_Credit_Card(Account* _owner):
    Credit_Card(_owner, 1000)
{  }

Basic_Credit_Card::~Basic_Credit_Card()
{  }


