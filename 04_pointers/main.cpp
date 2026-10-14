// Архив метеостанций. У станции есть подпись и несколько дней наблюдений,
// в каждом дне свой набор замеров; список станций читается до слова end.
// Архив упаковывается в один байтовый буфер (как перед записью в файл),
// потом читается обратно: по станции печатается подпись, число замеров и сумма.
//
// int*** нужен потому, что уровней ровно три (станции, дни, замеры) и длины
// у них разные: archive[s][d][m] это замер m дня d станции s, прямоугольным
// массивом так не выйдет. Сколько будет станций, заранее неизвестно, и когда
// место кончается, массив станций выделяется заново, то есть меняется сам
// указатель archive.
//
// void* нужен потому, что в буфере вперемешку лежат символы подписи и числа.
// Курсор по нему не может быть ни char*, ни int*: перед каждой записью он
// приводится к тому типу, который пишется прямо сейчас.

#include <cstring>
#include <iomanip>
#include <iostream>

int main() {
  const int kLabelSize = 8;
  const int kIntSize = static_cast<int>(sizeof(int));

  int capacity = 2;
  int stations = 0;
  int*** archive = new int**[capacity];  // станции -> дни -> замеры
  int** day_size = new int*[capacity];   // число замеров в каждом дне
  int* day_count = new int[capacity];    // число дней у станции
  char** label = new char*[capacity];    // подпись станции

  char name[kLabelSize];
  while (std::cin >> std::setw(kLabelSize) >> name) {
    if (std::strcmp(name, "end") == 0) {
      break;
    }

    if (stations == capacity) {
      capacity *= 2;
      int*** bigger_archive = new int**[capacity];
      int** bigger_day_size = new int*[capacity];
      int* bigger_day_count = new int[capacity];
      char** bigger_label = new char*[capacity];
      for (int s = 0; s < stations; ++s) {
        bigger_archive[s] = archive[s];
        bigger_day_size[s] = day_size[s];
        bigger_day_count[s] = day_count[s];
        bigger_label[s] = label[s];
      }
      delete[] archive;
      delete[] day_size;
      delete[] day_count;
      delete[] label;
      archive = bigger_archive;
      day_size = bigger_day_size;
      day_count = bigger_day_count;
      label = bigger_label;
    }

    label[stations] = new char[kLabelSize];
    std::memset(label[stations], 0, kLabelSize);
    std::strcpy(label[stations], name);

    int days = 0;
    std::cin >> days;
    if (days < 0) {
      days = 0;
    }
    day_count[stations] = days;
    archive[stations] = new int*[days];
    day_size[stations] = new int[days];
    for (int d = 0; d < days; ++d) {
      int measurements = 0;
      std::cin >> measurements;
      if (measurements < 0) {
        measurements = 0;
      }
      day_size[stations][d] = measurements;
      archive[stations][d] = new int[measurements];
      for (int m = 0; m < measurements; ++m) {
        std::cin >> archive[stations][d][m];
      }
    }
    ++stations;
  }

  int bytes = 0;
  for (int s = 0; s < stations; ++s) {
    bytes += kLabelSize + kIntSize;
    for (int d = 0; d < day_count[s]; ++d) {
      bytes += kIntSize * (1 + day_size[s][d]);
    }
  }

  char* blob = new char[bytes];
  void* cursor = blob;
  for (int s = 0; s < stations; ++s) {
    char* text = static_cast<char*>(cursor);
    std::memcpy(text, label[s], kLabelSize);
    cursor = text + kLabelSize;

    int* numbers = static_cast<int*>(cursor);
    numbers[0] = day_count[s];
    cursor = numbers + 1;

    for (int d = 0; d < day_count[s]; ++d) {
      numbers = static_cast<int*>(cursor);
      numbers[0] = day_size[s][d];
      for (int m = 0; m < day_size[s][d]; ++m) {
        numbers[1 + m] = archive[s][d][m];
      }
      cursor = numbers + 1 + day_size[s][d];
    }
  }

  cursor = blob;
  for (int s = 0; s < stations; ++s) {
    char* text = static_cast<char*>(cursor);
    cursor = text + kLabelSize;

    int* numbers = static_cast<int*>(cursor);
    int days = numbers[0];
    cursor = numbers + 1;

    long long sum = 0;
    int total = 0;
    for (int d = 0; d < days; ++d) {
      numbers = static_cast<int*>(cursor);
      int measurements = numbers[0];
      for (int m = 0; m < measurements; ++m) {
        sum += numbers[1 + m];
      }
      total += measurements;
      cursor = numbers + 1 + measurements;
    }
    std::cout << text << ' ' << total << ' ' << sum << '\n';
  }

  delete[] blob;
  for (int s = 0; s < stations; ++s) {
    for (int d = 0; d < day_count[s]; ++d) {
      delete[] archive[s][d];
    }
    delete[] archive[s];
    delete[] day_size[s];
    delete[] label[s];
  }
  delete[] archive;
  delete[] day_size;
  delete[] day_count;
  delete[] label;

  return 0;
}
