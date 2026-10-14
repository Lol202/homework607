#include <iomanip>
#include <iostream>

double AverageTemperature(const int* temperatures, int count) {
  long long sum = 0;
  for (int i = 0; i < count; ++i) {
    sum += temperatures[i];
  }
  return static_cast<double>(sum) / count;
}

void MinMaxTemperature(const int* temperatures, int count, int& min_value,
                       int& max_value) {
  min_value = temperatures[0];
  max_value = temperatures[0];
  for (int i = 1; i < count; ++i) {
    if (temperatures[i] < min_value) {
      min_value = temperatures[i];
    }
    if (temperatures[i] > max_value) {
      max_value = temperatures[i];
    }
  }
}

int CountFrostyDays(const int* temperatures, int count) {
  int frosty = 0;
  for (int i = 0; i < count; ++i) {
    if (temperatures[i] < 0) {
      ++frosty;
    }
  }
  return frosty;
}

int main() {
  int count = 0;
  std::cin >> count;
  if (count <= 0) {
    return 0;
  }

  int* temperatures = new int[count];
  for (int i = 0; i < count; ++i) {
    std::cin >> temperatures[i];
  }

  int min_value = 0;
  int max_value = 0;
  MinMaxTemperature(temperatures, count, min_value, max_value);

  std::cout << std::fixed << std::setprecision(1)
            << AverageTemperature(temperatures, count) << '\n';
  std::cout << min_value << ' ' << max_value << '\n';
  std::cout << CountFrostyDays(temperatures, count) << '\n';

  delete[] temperatures;
  return 0;
}
