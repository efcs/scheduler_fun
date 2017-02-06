#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <unordered_set>

struct Task;
struct Processor;

using TaskSet = std::unordered_set<Task*>;
using ProcessorList = std::vector<Processor>;
using TaskList = std::vector<Task>;

struct Task {
  int id;
  int type;
  int length;
  TaskSet Parents;
  TaskSet Children;
};

struct Processor {
  int id;
  int type;
};

struct ProblemState {
  ProblemState(ProcessorList PL, TaskList TL, int D)
      : Procs(PL), Tasks(TL), Deadline(D) {}

  ProcessorList Procs;
  TaskList Tasks;
  const int Deadline;
};

template <class Iter>
void assignIDs(Iter begin, Iter end) {
  int ID = 0;
  while (begin != end)
    begin->id = ID++;
}

ProblemState readProblemFromInput(std::istream& Input) {
  int NumProcT1, NumProcT2;
  Input >> NumProcT1 >> NumProcT2;
  assert(Input.good());

  ProcessorList PL;
  std::fill_n(std::back_inserter(PL), NumProcT1, Processor{-1, 1});
  std::fill_n(std::back_inserter(PL), NumProcT2, Processor{-1, 2});
  assignIDs(PL.begin(), PL.end());

  int NumTaskT1, NumTaskT2, NumTaskT3;
  Input >> NumTaskT1 >> NumTaskT2 >> NumTaskT3;
  assert(Input.good());

  // Start building the task lists:
  TaskList TL;
  std::fill_n(std::back_inserter(TL), NumTaskT1, Task{-1, 1});
  std::fill_n(std::back_inserter(TL), NumTaskT2, Task{-1, 2});
  std::fill_n(std::back_inserter(TL), NumTaskT3, Task{-1, 3});
  assignIDs(TL.begin(), TL.end());

  int Deadline;
  Input >> Deadline;
  assert(Input.good());

  for (auto& CurTask : TL) {
    Input >> CurTask.length;
    assert(Input.good());
  }

  int NumDeps;
  Input >> NumDeps;
  assert(Input.good());

  for (int i=0; i < NumDeps; ++i) {
    int ChildID, ParentID;
    Input >> ChildID >> ParentID;
    assert(Input.good());

    TL[ChildID].Parents.insert(&TL[ParentID]);
    TL[ParentID].Children.insert(&TL[ChildID]);
  }

  return {PL, TL, Deadline};
}



int schedule_main() {
  ProblemState State = readProblemFromInput(std::cin);

  return 0;
}
