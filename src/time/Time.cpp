#include "Time.hpp"

#include <ctime>
#include <string>

Time::Time() {}

Time::Time(const Time &src) {
  *this = src;
}
Time::~Time() {}

Time &Time::operator=(const Time &src) {
  (void)src;
  return *this;
}

std::string Time::getTimeToLog() const {
  std::time_t now = std::time(0);
  std::tm *nowTM = std::localtime(&now);
  char buffer[20];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", nowTM);
  return buffer;
}