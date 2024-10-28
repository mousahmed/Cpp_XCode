#include <string>
#include "OrderBookEntry.h"
using namespace std;

OrderBookEntry::OrderBookEntry(double price, double amount, string timestamp, string product, OrderBookType orderType)
    : price(price), amount(amount), timestamp(timestamp), product(product), orderType(orderType)
{
}