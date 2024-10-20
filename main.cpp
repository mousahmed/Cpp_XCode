#include <iostream>
using namespace std;

void printOptions()
{
  cout << "1: Print help" << endl;
  cout << "2: Print exchange stats" << endl;
  cout << "3: Place an ask" << endl;
  cout << "4: Place a bid" << endl;
  cout << "5: Print Wallet" << endl;
  cout << "6: Continue" << endl;
  cout << "===============================" << endl;
}

int getUserOption()
{
  int userOption;
  cout << "Type in 1-6" << endl;
  cin >> userOption;
  return userOption;
}

void printHelp()
{
  cout << "Help- choose options from the menu" << endl;
  cout << "and follow the on screen instructions." << endl;
}

void printExchangeStats()
{
  cout << "Market looks good" << endl;
}

void placeAsk()
{
  cout << "Make an offer - enter the amount" << endl;
}

void placeBid()
{
  cout << "Make a bid - enter the amount" << endl;
}

void printWallet()
{
  cout << "Your wallet is empty" << endl;
}

void continueToNextTimeFrame()
{
  cout << "Going to next time frame" << endl;
}

void proccessUserOption(int userOption)
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
  default:
    cout << "Invalid input" << endl;
  }
}

int main()
{
  int userOption;
  while (true)
  {
    printOptions();
    userOption = getUserOption();
    proccessUserOption(userOption);
  }
  return 0;
}