#include <cstring>
#include <iomanip>
#include <iostream>

const int kNameLimit = 32;

void Deposit(int& money) {
  int amount = 0;
  std::cin >> amount;
  if (amount <= 0) {
    std::cout << "error\n";
    return;
  }
  money += amount;
}

void Withdraw(int& money) {
  int amount = 0;
  std::cin >> amount;
  if (amount <= 0 || amount > money) {
    std::cout << "error\n";
    return;
  }
  money -= amount;
}

void Balance(int& money) { std::cout << money << '\n'; }

void Reset(int& money) { money = 0; }

void DoubleMoney(int& money) { money *= 2; }

struct Command {
  const char* name;
  void (*run)(int& money);
};

const Command kCommands[] = {
    {"deposit", Deposit}, {"withdraw", Withdraw},  {"balance", Balance},
    {"reset", Reset},     {"double", DoubleMoney},
};
const int kCommandCount = sizeof(kCommands) / sizeof(kCommands[0]);

int FindCommand(const char* name) {
  for (int i = 0; i < kCommandCount; ++i) {
    if (std::strcmp(name, kCommands[i].name) == 0) {
      return i;
    }
  }
  return -1;
}

int main() {
  int money = 0;
  char name[kNameLimit];

  while (std::cin >> std::setw(kNameLimit) >> name) {
    if (std::strcmp(name, "stop") == 0) {
      break;
    }
    int index = FindCommand(name);
    if (index < 0) {
      std::cout << "error\n";
      continue;
    }
    kCommands[index].run(money);
  }

  return 0;
}
