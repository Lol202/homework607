#include <cstring>
#include <iomanip>
#include <iostream>

const int kRows = 5;
const int kCols = 10;
const int kWordLimit = 64;

void Clear(char board[kRows][kCols]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kCols; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool Put(char board[kRows][kCols], int x, int y, char symbol) {
  if (x < 0 || x >= kCols || y < 0 || y >= kRows) {
    return false;
  }
  board[y][x] = symbol;
  return true;
}

bool Text(char board[kRows][kCols], int x, int y, const char* word) {
  int length = static_cast<int>(std::strlen(word));
  if (y < 0 || y >= kRows || x < 0 || x + length - 1 >= kCols) {
    return false;
  }
  for (int i = 0; i < length; ++i) {
    Put(board, x + i, y, word[i]);
  }
  return true;
}

void Print(const char board[kRows][kCols]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kCols; ++x) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

int main() {
  char board[kRows][kCols];
  Clear(board);

  char command[kWordLimit];
  while (std::cin >> std::setw(kWordLimit) >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }
    if (std::strcmp(command, "clear") == 0) {
      Clear(board);
    } else if (std::strcmp(command, "print") == 0) {
      Print(board);
    } else if (std::strcmp(command, "put") == 0) {
      int x = 0;
      int y = 0;
      char symbol = ' ';
      std::cin >> x >> y >> symbol;
      if (!Put(board, x, y, symbol)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x = 0;
      int y = 0;
      char word[kWordLimit];
      std::cin >> x >> y >> std::setw(kWordLimit) >> word;
      if (!Text(board, x, y, word)) {
        std::cout << "error\n";
      }
    } else {
      std::cout << "error\n";
    }
  }

  return 0;
}
