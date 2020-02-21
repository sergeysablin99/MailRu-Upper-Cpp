#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

struct Row {
  Row() = default;
  Row(std::vector<std::string>&& cells);
  std::vector<std::string> cells;
};

Row::Row(std::vector<std::string>&& cells) : cells(cells)
{
}

struct Table {
  std::vector<Row> data;
  Table() = default;
  void run();
  void input();
  void modify();
  void output();
};


void Table::input() {
  std::string input_data("");
  // Input data
  while (true) {
    std::cout << "Enter new line or q to finish input\n";
    std::getline(std::cin, input_data);
    if (input_data == "q")
      break;
    // C++20
    // if (!input_data.ends_with("\t"))
      // input_data.push_back("\t");
    if (input_data.back() != '\t')
      input_data.push_back('\t');
    size_t position = 0;
    std::vector<std::string> cells;
    while (!input_data.empty()) {
      position = input_data.find("\t");
      cells.push_back(input_data.substr(0, position));
      input_data.erase(0, ++position);
    }
    this->data.emplace_back(std::move(cells));
  }
}

void Table::modify() {
 // Edit data
  std::string input_data;
  size_t string_num = 0;
  size_t cell_num = 0;
  
  std::cout << "Enter string's number or q to exit\n";
  std::cin >> input_data;
  if (input_data == "q")
    return;
    
  try {
    string_num = std::stoi(input_data);
  }
  catch (std::invalid_argument) {
    std::cout << "Incorrect input!\n";
    return;
  }
  if (string_num > this->data.size()) {
    std::cout << "Incorrect input";
    string_num = 0;
  }

  std::cout << "Enter cell's number or q to exit\n";
  std::cin >> input_data;
  if (input_data == "q")
    return;

  try {
    cell_num = std::stoi(input_data);
  }
  catch (std::invalid_argument) {
    std::cout << "Incorrect input!\n";
    return;
  }
  if (cell_num > this->data[string_num].cells.size()) {
    std::cout << "Incorrect input";
    cell_num = 0;      
  }

  std::cout << "Enter new cell's data or q to exit\n";
  std::cin >> input_data;   
  if (input_data == "q")
    return;
  else 
    this->data[string_num].cells[cell_num] = input_data;
}

void Table::output() {
  for (auto& string:this->data) {
    for (auto& cell:string.cells) {
      std::cout << cell << "\t";
    }
    std::cout << "\n";
  }
}

void Table::run() {
  input();
  std::string input_data;
  while (true) {
    std::cout << "Enter m for modify, o for output or q for exit\n";
    std::cin >> input_data;   
    if (input_data == "q")
      break;
    else if (input_data == "m")
      modify();
    else if (input_data == "o")
      output();
    else 
      std::cout << "Command not found";
  }
}

int main() {
  Table table;
  table.run();
}
