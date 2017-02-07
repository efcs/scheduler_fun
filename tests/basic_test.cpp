#include "schedule.h"
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

int main() {
  const auto Prefix = "tests/Inputs/";
  std::vector<std::string> TestCases = {
      "basic_input.txt"
  };
  for (auto TC : TestCases) {
    auto InputFile = Prefix + TC;
    std::ifstream Input;
    Input.open(InputFile);
    assert(Input.good());
    auto State = readProblemFromInput(Input);
    ((void)State);
  }
}
