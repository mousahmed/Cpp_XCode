#pragma once
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain
{
public:
  MerkelMain();
  void init();
  std::vector<OrderBookEntry> getOrders() const;

private:
  std::vector<OrderBookEntry> orders;
  void printOptions() const;
  int getUserOption() const;
  void printHelp() const;
  void printExchangeStats() const;
  void placeAsk();
  void placeBid();
  void printWallet() const;
  void continueToNextTimeFrame();
  void processUserOption(int userOption, bool &running);
  void loadOrderBook();
};