#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
class MerkelMain
{
public:
  MerkelMain();
  void init();

private:
  OrderBook orderBook{"data.csv"};
  Wallet wallet;
  std::string currentTime;
  std::string currentUsername;
  void printOptions() const;
  int getUserOption() const;
  void printHelp() const;
  void printMarketStats();
  void placeAsk();
  void placeBid();
  void printWallet();
  void gotoNextTimeFrame();
  void processUserOption(int userOption, bool &running);
  void processSales();
};