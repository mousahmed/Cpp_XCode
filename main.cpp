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

void proccessUserOption(int userOption)
{
  switch (userOption)
  {
  case 1:
    cout << "Help- choose options from the menu" << endl;
    cout << "and follow the on screen instructions." << endl;
    break;
  case 2:
    cout << "Market looks good" << endl;
    break;
  case 3:
    cout << "Make an offer - enter the amount" << endl;
    break;
  case 4:
    cout << "Make a bid - enter the amount" << endl;
    break;
  case 5:
    cout << "Your wallet is empty" << endl;
    break;
  case 6:
    cout << "Going to next time frame" << endl;
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