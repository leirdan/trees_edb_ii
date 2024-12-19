#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <stack>

struct random_list
{
  std::string filename;
  std::string sorted_filename;
  int size;

  random_list(std::string filename, std::string sorted_filename, int size)
  {
    this->filename = filename;
    this->sorted_filename = sorted_filename;
    this->size = size;
  }
};

void generate_random_list(const std::string &filename, int size)
{
  std::ofstream file(filename);
  srand(time(0));
  for (int i = 0; i < size; i++)
  {
    file << rand() % 10001 << "\n"; // Random number between 0 and 10000
  }
  file.close();
}

std::vector<int> load_list(const std::string filename)
{
  std::ifstream file(filename);
  std::vector<int> list;
  int number;
  while (file >> number)
  {
    list.push_back(number);
  }
  file.close();
  return list;
}

void save_list(const std::string &filename, const std::vector<int> &list)
{
  std::ofstream file(filename);
  for (int i : list)
  {
    file << i << "\n";
  }
  file.close();
}

void save_list(const std::string &filename, const node *array, int size)
{
  std::ofstream file(filename);
  for (int i = 0; i < size; i++)
  {
    file << array[i].key << "\n";
  }
  file.close();
}