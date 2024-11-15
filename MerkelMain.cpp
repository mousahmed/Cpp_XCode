#include <iostream>
#include "MerkelMain.h"
#include <limits>

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
  int input;
  bool running = true;
  while (running)
  {
    printOptions();
    input = getUserOption();
    processUserOption(input, running);
  }
}

void MerkelMain::printOptions() const
{
  std::cout << "1: Print help" << std::endl;
  std::cout << "2: Print exchange stats" << std::endl;
  std::cout << "3: Place an ask" << std::endl;
  std::cout << "4: Place a bid" << std::endl;
  std::cout << "5: Print Wallet" << std::endl;
  std::cout << "6: Continue" << std::endl;
  std::cout << "7: Exit" << std::endl;
  std::cout << "===============================" << std::endl;
  std::cout << std::endl;
}

int MerkelMain::getUserOption() const
{
  int userOption;
  std::cout << "Type in 1-7" << std::endl;
  std::cin >> userOption;
  std::cout << std::endl;
  while (std::cin.fail() || userOption < 1 || userOption > 7)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Please type in 1-7" << std::endl;
    std::cin >> userOption;
    std::cout << std::endl;
  }
  return userOption;
}

void MerkelMain::printHelp() const
{
  std::cout << "Help- choose options from the menu" << std::endl;
  std::cout << "and follow the on screen instructions." << std::endl;
  std::cout << std::endl;
}

void MerkelMain::printMarketStats()
{
  std::string currentTime = "2020/03/17 17:01:24.884492";
  for (const std::string &p : orderBook.getKnownProducts())
  {
    std::cout << "Product: " << p << std::endl;
    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
    std::cout << "Asks seen: " << entries.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
    std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    std::cout << "Average ask: " << OrderBook::getAveragePrice(entries) << std::endl;
    std::cout << "Spread: " << OrderBook::getPriceSpread(entries) << std::endl;
    std::cout << std::endl;
  }
}

void MerkelMain::placeAsk()
{
  std::cout << "Make an offer - enter the amount" << std::endl;
}

void MerkelMain::placeBid()
{
  std::cout << "Make a bid - enter the amount" << std::endl;
}

void MerkelMain::printWallet()
{
  std::cout << "Your wallet is empty" << std::endl;
}

void MerkelMain::continueToNextTimeFrame()
{
  std::cout << "Going to next time frame" << std::endl;
}

void MerkelMain::processUserOption(int userOption, bool &running)
{
  switch (userOption)
  {
  case 1:
    printHelp();
    break;
  case 2:
    printMarketStats();
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
    std::cout << "Invalid input" << std::endl;
  }
}