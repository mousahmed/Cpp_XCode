#include "Wallet.h"
#include "CSVReader.h"

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

bool Wallet::canFulfillOrder(OrderBookEntry &order)
{
  const auto currencies = CSVReader::tokenise(order.product, '/');
  if (order.orderType == OrderBookType::ask)
  {
    return containsCurrency(currencies[1], order.amount * order.price);
  }
  return containsCurrency(currencies[0], order.amount);
}

void Wallet::processSale(OrderBookEntry &sale)
{
  const auto currencies = CSVReader::tokenise(sale.product, '/');
  if (sale.orderType == OrderBookType::asksale)
  {
    double outgoingAmount = sale.amount;
    double incomingAmount = sale.amount * sale.price;
    std::string outgoingCurrency = currencies[0];
    std::string incomingCurrency = currencies[1];
    removeCurrency(outgoingCurrency, outgoingAmount);
    insertCurrency(incomingCurrency, incomingAmount);
  }
  else if (sale.orderType == OrderBookType::bidsale)
  {
    double outgoingAmount = sale.amount * sale.price;
    double incomingAmount = sale.amount;
    std::string outgoingCurrency = currencies[1];
    std::string incomingCurrency = currencies[0];
    removeCurrency(outgoingCurrency, outgoingAmount);
    insertCurrency(incomingCurrency, incomingAmount);
  }
}