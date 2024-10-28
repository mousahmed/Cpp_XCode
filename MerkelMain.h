#pragma once
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain
{
public:
  MerkelMain();
  void init();
  vector<OrderBookEntry> getOrders();

private:
  vector<OrderBookEntry> orders;
  void printOptions();
  int getUserOption();
  void printHelp();
  void printExchangeStats();
  void placeAsk();
  void placeBid();
  void printWallet();
  void continueToNextTimeFrame();
  void processUserOption(int userOption, bool &running);
  void loadOrderBook();
};
