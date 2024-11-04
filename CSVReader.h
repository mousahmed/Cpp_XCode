#include "OrderBookEntry.h"
#include <vector>
#include <string>
#include <optional>

class CSVReader
{
public:
  CSVReader();
  static std::vector<OrderBookEntry> readCSV(std::string csvFile);

private:
  static std::vector<std::string> tokenise(std::string csvLine, char separator);
  static std::optional<OrderBookEntry> stringsToOBE(std::vector<std::string> strings);
};