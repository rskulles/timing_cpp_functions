#include <bits/chrono.h>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

template <typename T, typename P, typename D>
D time_func(std::function<T(P &)> func, P &param) {
  std::chrono::high_resolution_clock clock;
  auto tp1 = clock.now();
  auto r = func(param);
  auto tp2 = clock.now();
  return std::chrono::duration_cast<D>(tp2 - tp1);
}

uint sum_matrix(std::vector<std::vector<uint8_t> *> *matrix) {
  uint sum = 0;
  for (size_t i = 0; i < matrix->size(); ++i) {
    for (size_t j = 0; j < (*matrix)[0]->size(); ++j) {
      sum += (*matrix)[i]->at(j);
    }
  }
  return sum;
}

void time_size(size_t x, size_t y, size_t numb_of_times) {
  std::cout << "Creating a " << x << "x" << y << " matrix and running code "
            << numb_of_times << " times" << std::endl;
  std::vector<std::vector<uint8_t> *> *matrix =
      new std::vector<std::vector<uint8_t> *>();

  for (auto i = 0; i < x; ++i) {
    (*matrix).push_back(new std::vector<uint8_t>(y, 1));
  }

  auto ms_avg = std::chrono::nanoseconds::zero();
  auto ms_min = std::chrono::nanoseconds::zero();
  auto ms_max = std::chrono::nanoseconds::zero();
  std::cout << "Running...." << std::endl;
  for (auto i = 0; i < numb_of_times; ++i) {
    auto d = time_func<uint, std::vector<std::vector<uint8_t> *> *,
                       std::chrono::nanoseconds>(sum_matrix, matrix);
    if (i == 0) {
      ms_avg = d;
      ms_min = d;
      ms_max = d;
    } else {
      ms_avg += d;

      if (d < ms_min) {
        ms_min = d;
      }

      if (d > ms_max) {
        ms_max = d;
      }
    }
  }
  for (auto i = 0; i < x; ++i) {
    delete (*matrix)[i];
  }
  delete matrix;
  std::cout << "**********" << std::endl;
  std::cout << "Total time: " << ms_avg.count() << "ns" << std::endl
            << "\tfastest: " << ms_min.count() << "ns" << std::endl
            << "\tslowest: " << ms_max.count() << "ns" << std::endl
            << "\tavg: " << ms_avg.count() / numb_of_times << "ns" << std::endl;
  std::cout << "**********" << std::endl << std::endl;
}

int main() {

  time_size(100, 100, 1000);
  time_size(100, 1000, 1000);
  time_size(100, 10000, 1000);
  time_size(100, 100000, 1000);
  time_size(100, 1000000, 1000); // Times should be the same starting here
  time_size(1000, 100000, 1000);
  time_size(10000, 10000, 1000);
  return 0;
}
