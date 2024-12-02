#pragma once
#include <string>

enum class OrderBookType
{
  bid,
  ask,
  unknown,
  bidsale,
  asksale
};

class OrderBookEntry
{
public:
  double price;
  double amount;
  std::string timestamp;
  std::string product;
  OrderBookType orderType;
  std::string username;

  OrderBookEntry(double price,
                 double amount,
                 std::string timestamp,
                 std::string product,
                 OrderBookType orderType,
                 std::string username = "dataset");
  static OrderBookType stringToOrderBookType(const std::string &s);
  static bool compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2);
  static bool compareByPriceAsc(const OrderBookEntry &e1, const OrderBookEntry &e2);
  static bool compareByPriceDesc(const OrderBookEntry &e1, const OrderBookEntry &e2);
};
