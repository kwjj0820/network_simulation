#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>

class Simulator;

class Schedule {
private:
  double time_;
  std::function<void()> function_;

public:
  double time() { return time_; }
  void call() { function_(); }

  Schedule(double time, std::function<void()> function)
      : time_(time), function_(function) {}
};

struct cmp
{
	bool operator()(Schedule* a, Schedule* b)
  {
    return a->time() < b->time();
  }
};

class Simulator {
private:
  static double time_;

public:
  static double now() { return time_; }
  static std::priority_queue<Schedule*, std::vector<Schedule*>, cmp> schedules;

  static void schedule(double time, std::function<void()> function) {
    // 스케줄 큐에 스케줄을 추가한다.
    // TODO: 구현
    Schedule* s = new Schedule(time, function);
    schedules.push(s);
  }

  static void run() {
    srand(RANDOM_SEED);

    // 모든 스케줄을 실행한다.
    // TODO: 구현
  }
};

#endif