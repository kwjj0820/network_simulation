#include "simulator.h"

// 정적 변수 정의
double Simulator::time_ = 0;
std::priority_queue<Schedule*, std::vector<Schedule*>, cmp> Simulator::schedules;
