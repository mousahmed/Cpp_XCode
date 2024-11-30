#include "Wallet.h"

void Wallet::insertCurrency(std::string type, double amount)
{
  if (amount < 0)
  {
    throw std::invalid_argument("Amount cannot be negative");
  }
  if (currencies.find(type) == currencies.end())
  {
    currencies[type] = 0;
  }
  currencies[type] += amount;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
  if (amount < 0)
  {
    throw std::invalid_argument("Amount cannot be negative");
  }
  if (currencies[type] < amount)
  {
    return false;
  }
  currencies[type] -= amount;
  return true;
}

bool Wallet::containsCurrency(std::string type, double amount)
{
  return currencies[type] >= amount;
}

std::string Wallet::toString() const
{
  std::string s;
  for (const auto &currency : currencies)
  {
    s += currency.first + ": " + std::to_string(currency.second) + "\n";
  }
  return s;
}

std::ostream &operator<<(std::ostream &os, const Wallet &wallet)
{
  os << wallet.toString();
  return os;
}