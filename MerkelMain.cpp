#include <iostream>
#include "MerkelMain.h"
#include <limits>
#include <string>

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
  int input;
  bool running = true;
  currentTime = orderBook.getEarliestTime();
  wallet.insertCurrency("BTC", 10);
  wallet.insertCurrency("ETH", 100);
  currentUsername = "simuser";
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
  int userOption = 0;
  std::string input;
  std::cout << "Type in 1-7" << std::endl;
  std::getline(std::cin, input);
  std::cout << std::endl;
  try
  {
    userOption = std::stoi(input);
  }
  catch (const std::exception &e)
  {
    std::cerr << "MerkelMain::getUserOption(): Invalid choice" + input << std::endl;
    std::cout << std::endl;
  }
  std::cout << "You chose: " << userOption << std::endl;
  std::cout << std::endl;
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
  std::cout << "Make an ask - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
  std::string input;
  std::getline(std::cin, input);
  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3)
  {
    std::cerr << "MerkelMain::placeAsk(): invalid ask input" << std::endl;
    std::cout << std::endl;
    return;
  }
  try
  {
    std::cout << "Your input is: " << input << std::endl;
    std::cout << std::endl;
    OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                 tokens[2],
                                                 currentTime,
                                                 tokens[0],
                                                 OrderBookType::ask,
                                                 currentUsername);
    if (wallet.canFulfillOrder(obe))
    {
      std::cout << "Wallet looks good. " << std::endl;
      orderBook.insertOrder(obe);
    }
    else
    {
      std::cout << "Wallet has insufficient funds . " << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "MerkelMain::placeAsk(): Error placing ask:" << std::endl;
    std::cout << std::endl;
  }
}

void MerkelMain::placeBid()
{
  std::cout << "Make an bid - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
  std::string input;
  std::getline(std::cin, input);
  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3)
  {
    std::cerr << "MerkelMain::placeBid(): invalid bid input" << std::endl;
    std::cout << std::endl;
    return;
  }
  try
  {
    OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                 tokens[2],
                                                 currentTime,
                                                 tokens[0],
                                                 OrderBookType::bid,
                                                 currentUsername);
    if (wallet.canFulfillOrder(obe))
    {
      std::cout << "Wallet looks good. " << std::endl;
      orderBook.insertOrder(obe);
    }
    else
    {
      std::cout << "Wallet has insufficient funds . " << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error placing bid: " << e.what() << std::endl;
    std::cout << std::endl;
  }
}

void MerkelMain::printWallet()
{
  std::cout << "Wallet: " << std::endl;
  std::cout << wallet << std::endl;
  std::cout << std::endl;
}

void MerkelMain::processSales()
{
  for (std::string &p : orderBook.getKnownProducts())
  {
    std::cout << "matching " << p << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime, currentUsername);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry &sale : sales)
    {
      wallet.processSale(sale);
      std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
    }
    std::cout << std::endl;
  }
}
void MerkelMain::gotoNextTimeFrame()
{
  processSales();
  std::cout << "Going to next time frame. " << std::endl;
  currentTime = orderBook.getNextTime(currentTime);
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
    gotoNextTimeFrame();
    break;
  case 7:
    running = false;
    break;
  default:
    std::cout << "Invalid input" << std::endl;
  }
}
