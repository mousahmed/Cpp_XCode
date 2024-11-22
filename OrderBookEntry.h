#pragma once
#include <string>

enum class OrderBookType
{
  bid,
  ask,
  unknown
};

class OrderBookEntry
{
public:
  double price;
  double amount;
  std::string timestamp;
  std::string product;
  OrderBookType orderType;

  OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OrderBookType orderType);
  static OrderBookType stringToOrderBookType(const std::string &s);
  static bool compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2);
};
