#pragma once
#include <string>
using namespace std;

enum class OrderBookType
{
  bid,
  ask
};

class OrderBookEntry
{
public:
  double price;
  double amount;
  string timestamp;
  string product;
  OrderBookType orderType;

  OrderBookEntry(double price, double amount, string timestamp, string product, OrderBookType orderType);
};
