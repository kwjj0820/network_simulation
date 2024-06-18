#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip> // 추가

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
    return a->time() > b->time();
  }
};

class Simulator {
private:
  static double time_;

public:
  static void prepare() { srand(RANDOM_SEED); }
  static double now() { return time_; } // time을 반환하도록 수정
  static std::priority_queue<Schedule*, std::vector<Schedule*>, cmp> schedules;

  static void schedule(double time, std::function<void()> function) {
    // 스케줄 큐에 스케줄을 추가한다.
    Schedule* s = new Schedule(time, function);
    schedules.push(s);
  }

  static void run() {
    // 모든 스케줄을 실행한다.
    while (!schedules.empty())
    {
      Schedule* s = schedules.top();
      schedules.pop();
      time_ = s->time(); // 현재 시간을 스케줄의 시간으로 업데이트
      std::cout << std::fixed << std::setprecision(2) << time_ << "s\t"; // 수정된 부분
      s->call();
      delete s;
    }
  }
};

#endif
