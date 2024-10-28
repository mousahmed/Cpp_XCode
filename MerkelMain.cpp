#include <iostream>
#include "MerkelMain.h"
#include <vector>
using namespace std;

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
  loadOrderBook();
  int input;
  bool running = true;
  while (running)
  {
    printOptions();
    input = getUserOption();
    processUserOption(input, running);
  }
}

void MerkelMain::loadOrderBook()
{
  orders.push_back(OrderBookEntry(10000, 0.002, "2021/01/01 10:00:00", "BTC/USDT", OrderBookType::bid));
  orders.push_back(OrderBookEntry(10100, 0.004, "2021/01/01 10:01:00", "BTC/USDT", OrderBookType::ask));
  orders.push_back(OrderBookEntry(9900, 0.003, "2021/01/01 10:02:00", "BTC/USDT", OrderBookType::bid));
  orders.push_back(OrderBookEntry(10200, 0.001, "2021/01/01 10:03:00", "BTC/USDT", OrderBookType::ask));
}

vector<OrderBookEntry> MerkelMain::getOrders()
{
  return orders;
}

void MerkelMain::printOptions()
{
  cout << "1: Print help" << endl;
  cout << "2: Print exchange stats" << endl;
  cout << "3: Place an ask" << endl;
  cout << "4: Place a bid" << endl;
  cout << "5: Print Wallet" << endl;
  cout << "6: Continue" << endl;
  cout << "7: Exit" << endl;
  cout << "===============================" << endl;
}

int MerkelMain::getUserOption()
{
  int userOption;
  cout << "Type in 1-7" << endl;
  cin >> userOption;
  return userOption;
}

void MerkelMain::printHelp()
{
  cout << "Help- choose options from the menu" << endl;
  cout << "and follow the on screen instructions." << endl;
}

void MerkelMain::printExchangeStats()
{
  cout << "Market looks good" << endl;
}

void MerkelMain::placeAsk()
{
  cout << "Make an offer - enter the amount" << endl;
}

void MerkelMain::placeBid()
{
  cout << "Make a bid - enter the amount" << endl;
}

void MerkelMain::printWallet()
{
  cout << "Your wallet is empty" << endl;
}

void MerkelMain::continueToNextTimeFrame()
{
  cout << "Going to next time frame" << endl;
}

void MerkelMain::processUserOption(int userOption, bool &running)
{
  switch (userOption)
  {
  case 1:
    printHelp();
    break;
  case 2:
    printExchangeStats();
    break;
  case 3:
    placeAsk();
    break;
  case 4:
    placeBid();
    break;
  case 5:
    printWallet();
    break;
  case 6:
    continueToNextTimeFrame();
    break;
  case 7:
    running = false;
    break;
  default:
    cout << "Invalid input" << endl;
  }
}
