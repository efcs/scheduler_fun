#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <ios>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <memory>

struct Task;
struct Processor;
struct TaskCompletion;

using TaskSet = std::unordered_set<Task*>;
using TaskSetPtr = std::shared_ptr<TaskSet>;
using ProcessorList = std::vector<Processor>;
using TaskList = std::vector<Task>;

struct Task {
  int ID;
  int Kind;
  int Duration;

  const TaskSetPtr Parents = std::make_shared<TaskSet>();
  const TaskSetPtr Children = std::make_shared<TaskSet>();

  TaskCompletion *Completion;

public:
  bool hasParents() const {
    return std::any_of(Parents->begin(), Parents->end(),
                       [](Task const* T) { return T->Completion == nullptr; });
  }
};

struct Processor {
  int ID;
  int Kind;

public:
  bool canSchedule(Task const& T) const {
    return (T.Kind & Kind) != 0;
  }
};

struct ProblemState {
  ProblemState(int D)
      : Deadline(D) {}

  const int Deadline;
  ProcessorList Processors;
  TaskList Tasks;
  std::vector<std::pair<TaskSet, TaskSet>> ParentChildSetCache;
};

struct Solution {
  bool IsInvalid = false;
};

inline Solution SolutionError() {
  Solution S;
  S.IsInvalid = true;
  return S;
}

/// \brief Read the problem specification from 'Input' and return
///        a ProblemState object represeting the specification.
ProblemState readProblemFromInput(std::istream& Input);

/// \brief Return an object represeting a solution, or lack thereof, for the
///        specified problem.
Solution attemptSolution(ProblemState const& Problem);

/// \brief An entry point that acts like the 'main()' function.
int schedule_main();

#endif // SCHEDULE_H
