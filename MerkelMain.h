#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain
{
public:
  MerkelMain();
  void init();

private:
  OrderBook orderBook{"20200317.csv"};
  std::string currentTime;
  void printOptions() const;
  int getUserOption() const;
  void printHelp() const;
  void printMarketStats();
  void placeAsk();
  void placeBid();
  void printWallet();
  void gotoNextTimeFrame();
  void processUserOption(int userOption, bool &running);
};