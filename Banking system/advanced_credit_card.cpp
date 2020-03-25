#include "advanced_credit_card.h"

Advanced_Credit_Card::Advanced_Credit_Card(Account* _owner):
   Credit_Card(_owner, 5000)
{  }

Advanced_Credit_Card::Advanced_Credit_Card(Account* _owner, float _max_withdraw_allowed):
   Credit_Card(_owner, _max_withdraw_allowed)
{  }

Advanced_Credit_Card::~Advanced_Credit_Card()
{  }
