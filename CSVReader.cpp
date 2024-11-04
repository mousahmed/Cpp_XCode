#include "CSVReader.h"
#include <fstream>
#include <iostream>

CSVReader::CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
  std::string csvFileName = "20200317.csv";
  std::ifstream file(csvFileName);
  if (!file.is_open())
  {
    std::cerr << "Could not open the file - '" << csvFileName << "'" << std::endl;
  }
  std::vector<OrderBookEntry> entries;
  while (file.good())
  {
    std::string line;
    std::getline(file, line);
    std::cout << line << std::endl;
    std::vector<std::string> tokens = tokenise(line, ',');
    auto entryOpt = stringsToOBE(tokens);
    if (entryOpt.has_value())
    {
      entries.push_back(entryOpt.value());
    }
  }
  file.close();
  return entries;
}

/**
 * Tokenises a given CSV line into a vector of strings based on the specified separator.
 *
 * @param csvLine The string containing the CSV line to be tokenised.
 * @param separator The character used to separate tokens in the CSV line.
 * @return A vector of strings containing the tokens.
 */
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
  std::vector<std::string> tokens;
  std::string token;
  for (const char &c : csvLine)
  {
    if (c == separator)
    {
      if (!token.empty())
      {
        tokens.push_back(token);
        token.clear();
      }
    }
    else
    {
      token += c;
    }
  }
  if (!token.empty())
  {
    tokens.push_back(token);
  }
  return tokens;
}

/**
 * @brief Creates an OrderBookEntry from a vector of strings.
 *
 * This function takes a vector of strings as input and attempts to create an OrderBookEntry object.
 * The vector must contain exactly 5 elements: timestamp, product, order type (either "bid" or "ask"),
 * price, and amount. If the vector does not contain exactly 5 elements, or if there is an error
 * converting the price or amount to a double, the function will return an empty optional.
 *
 * @param tokens A vector of strings containing the necessary data to create an OrderBookEntry.
 * @return An optional OrderBookEntry. If the input is invalid or an error occurs, returns nullopt.
 */
std::optional<OrderBookEntry> CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
  if (tokens.size() != 5)
  {
    std::cerr << "Invalid number of tokens: " << tokens.size() << std::endl;
    return std::nullopt;
  }

  try
  {
    std::string timestamp = tokens[0];
    std::string product = tokens[1];
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(tokens[2]);
    double price = stod(tokens[3]);
    double amount = stod(tokens[4]);
    return OrderBookEntry(price, amount, timestamp, product, orderType);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error creating OrderBookEntry: " << e.what() << std::endl;
    return std::nullopt;
  }
}