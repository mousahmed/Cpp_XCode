#include <map>
#include <string>
#include <iostream>
#include "OrderBookEntry.h"
class Wallet
{
public:
  /** insert currency to the wallet */
  void insertCurrency(std::string type, double amount);
  /** remove currency from the wallet */
  bool removeCurrency(std::string type, double amount);
  /** check if the wallet contains this much currency or more */
  bool containsCurrency(std::string type, double amount);
  /** generate a string representation of the wallet */
  std::string toString() const;
  /** output the wallet to the ostream */
  friend std::ostream &operator<<(std::ostream &os,const Wallet &wallet);
  /** check if the wallet can fulfill an order */
  bool canFulfillOrder(OrderBookEntry& order);
  /** process a sale */
  void processSale(OrderBookEntry &sale);

private:
  std::map<std::string, double> currencies;
};