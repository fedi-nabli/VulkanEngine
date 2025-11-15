#include <iostream>

#include <cmath>
#include <cstdint>
#include <gsl/gsl>

int main(std::int32_t argc, gsl::zstring* argv)
{
  gsl::span<gsl::zstring> arguments(argv, argc);
  std::sort(arguments.begin(), arguments.end());

  std::cout << "Hello World!" << std::endl;
  return 0;
}
