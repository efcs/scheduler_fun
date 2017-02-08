#include "schedule.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <unordered_set>

#if 0
# define PV(X) std::cout << #X " = " << X << std::endl
# define PM(M) std::cout << "Note: " << M << std::endl
#else
# define PV(X) ((void)0)
# define PM(M) ((void)0)
#endif

template <class ValueType>
bool readValueImp(std::istream& Input, ValueType& Output) {
  while (true) {
    Input >> Output;
    if (Input.eof() || Input.bad())
      return false;
    assert(!Input.fail());
    assert(Input.good());
    return true;
  }
}

template <class ...ValueTypes>
bool readValuesImp(std::istream& Input, ValueTypes&... Outputs) {
  return (readValueImp(Input, Outputs) && ...);
}

template <class ValueType>
auto readValue(std::istream& Input, bool& OK) {
  ValueType Result;
  OK = readValueImp(Input, Result);
  return Result;
}

template <class ...ValueTypes>
auto readValues(std::istream& Input, bool &OK) {
  std::tuple<ValueTypes...> Results;
  OK = std::apply(
      [&](auto&... Args) { return readValuesImp(Input, Args...); },
      Results);
  return Results;
}

template <class Iter>
void assignIDs(Iter begin, Iter end) {
  int ID = 0;
  for (; begin != end; ++begin) {
    begin->ID = ID++;
  }
}

ProblemState readProblemFromInput(std::istream& Input) {
  bool OK = false;
  auto [NumProcT1, NumProcT2, NumTaskT1, NumTaskT2, NumTaskT3, Deadline]
     = readValues<int, int, int, int, int, int>(Input, OK); // Read 6 ints from Input.
  assert(OK && "Failed to read the number of processors, tasks, or deadline");
  PV(NumProcT1); PV(NumProcT2); PV(NumTaskT1); PV(NumTaskT2); PV(NumTaskT3); PV(Deadline);

  ProblemState State((Deadline));

  const int InvalidID = -1;
  std::fill_n(std::back_inserter(State.Processors), NumProcT1, Processor{InvalidID, 1});
  std::fill_n(std::back_inserter(State.Processors), NumProcT2, Processor{InvalidID, 2});
  assignIDs(State.Processors.begin(), State.Processors.end());

  std::fill_n(std::back_inserter(State.Tasks), NumTaskT1, Task{InvalidID, 1});
  std::fill_n(std::back_inserter(State.Tasks), NumTaskT2, Task{InvalidID, 2});
  std::fill_n(std::back_inserter(State.Tasks), NumTaskT3, Task{InvalidID, 3});
  assignIDs(State.Tasks.begin(), State.Tasks.end());

  for (auto& CurTask : State.Tasks) {
    CurTask.Duration = readValue<int>(Input, OK);
    assert(OK && "Failed to read the length of a task");
    PV(CurTask.ID); PV(CurTask.Duration);
  }

  int NumDeps = readValue<int>(Input, OK);
  assert(OK && "Failed to read the number of dependencies");
  PV(NumDeps);

  for (int i=0; i < NumDeps; ++i) {
    auto [ChildID, ParentID] = readValues<int, int>(Input, OK);
    assert(OK && "Failed to read dependancy pair");
    PV(ChildID); PV(ParentID);

    // Unlike the crazy spec I use zero based indexing for the types and
    // processors. So ajust for that now.
    assert(ChildID >= 1 && ParentID >= 1&& "Task ID's are supposed to start at 1");
    ChildID--;
    ParentID--;

    auto& TL = State.Tasks;
    TL.at(ChildID).Parents->emplace(&TL.at(ParentID));
    TL.at(ParentID).Children->emplace(&TL.at(ChildID));
  }

  return State;
}

static bool isProblemInsane(ProblemState const& ) {
  return false;
}

Solution attemptSolution(ProblemState const& Problem) {
  if (isProblemInsane(Problem))
    return SolutionError();
  return SolutionError();
}

int schedule_main() {
  ProblemState State = readProblemFromInput(std::cin);
  Solution S = attemptSolution(State);
  assert(S.IsInvalid); // FIXME
  return 0;
}
