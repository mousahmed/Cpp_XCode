#include <iostream>
#include "MerkelMain.h"
#include "CSVReader.h"
#include <limits>

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
  orders = CSVReader::readCSV("20200317.csv");
  std::cout << "Loaded " << orders.size() << " orders" << std::endl;
}

std::vector<OrderBookEntry> MerkelMain::getOrders() const
{
  return orders;
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
}

int MerkelMain::getUserOption() const
{
  int userOption;
  std::cout << "Type in 1-7" << std::endl;
  std::cin >> userOption;
  while (std::cin.fail() || userOption < 1 || userOption > 7)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Please type in 1-7" << std::endl;
    std::cin >> userOption;
  }
  return userOption;
}

void MerkelMain::printHelp() const
{
  std::cout << "Help- choose options from the menu" << std::endl;
  std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printExchangeStats() const
{
  std::cout << "Market looks good" << std::endl;
}

void MerkelMain::placeAsk()
{
  std::cout << "Make an offer - enter the amount" << std::endl;
}

void MerkelMain::placeBid()
{
  std::cout << "Make a bid - enter the amount" << std::endl;
}

void MerkelMain::printWallet() const
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
    std::cout << "Invalid input" << std::endl;
  }
}