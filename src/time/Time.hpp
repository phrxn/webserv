#ifndef TIME_TIME_HPP
#define TIME_TIME_HPP

#include <string>

class Time {
 public:
  Time();
  Time(const Time &src);
  virtual ~Time();

  Time &operator=(const Time &src);

  virtual std::string getTimeToLog() const;
};

#endif