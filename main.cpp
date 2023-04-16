#include <_types/_uint8_t.h>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

std::chrono::milliseconds
time_func(std::function<uint(uint8_t **, size_t, size_t)> func, uint8_t **param,
          size_t x, size_t y) {
  std::chrono::high_resolution_clock clock;
  auto tp1 = clock.now();
  auto r = func(param, x, y);
  auto tp2 = clock.now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1);
}

uint sum_matrix(uint8_t **matrix, size_t x, size_t y) {
  uint sum = 0;
  for (size_t i = 0; i < x; ++i) {
    for (size_t j = 0; j < y; ++j) {
      sum += matrix[i][j];
    }
  }
  return sum;
}

void time_size(size_t x, size_t y, size_t numb_of_times) {
  std::cout << "Creating a " << x << "x" << y << " matrix and running code "
            << numb_of_times << " times" << std::endl;

  uint8_t **matrix;
  matrix = new uint8_t *[x];
  for (auto i = 0; i < x; ++i) {
    matrix[i] = new uint8_t[y];
    for (auto j = 0; j < y; ++j) {
      matrix[i][j] = 1;
    }
  }
  auto ms_avg = std::chrono::milliseconds::zero();
  auto ms_min = std::chrono::milliseconds::zero();
  auto ms_max = std::chrono::milliseconds::zero();
  std::cout << "Running...." << std::endl;
  for (auto i = 0; i < numb_of_times; ++i) {
    auto d = time_func(sum_matrix, matrix, x, y);
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
  std::cout << "**********" << std::endl;
  std::cout << "Total time: " << ms_avg.count() << "ms" << std::endl
            << "\tfastest: " << ms_min.count() << "ms" << std::endl
            << "\tslowest: " << ms_max.count() << "ms" << std::endl
            << "\tavg: " << ms_avg.count() / numb_of_times << "ms" << std::endl;
  std::cout << "**********" << std::endl << std::endl;
  for (auto i = 0; i < x; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int main() {

  time_size(100, 100, 1000);
  time_size(100, 1000, 1000);
  time_size(100, 10000, 1000);
  time_size(100, 100000, 1000);
  time_size(100, 1000000, 100);
  return 0;
}
