#include <string>
#include "OrderBookEntry.h"
using namespace std;

OrderBookEntry::OrderBookEntry(double price,
                               double amount,
                               string timestamp,
                               string product,
                               OrderBookType orderType,
                               string username)
    : price(price),
      amount(amount),
      timestamp(timestamp),
      product(product),
      orderType(orderType),
      username(username)
{
}

OrderBookType OrderBookEntry::stringToOrderBookType(const std::string &s)
{
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    if (s == "bid")
    {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2)
{
    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(const OrderBookEntry &e1, const OrderBookEntry &e2)
{
    return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(const OrderBookEntry &e1, const OrderBookEntry &e2)
{
    return e1.price > e2.price;
}
