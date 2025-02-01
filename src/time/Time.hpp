#ifndef TIME_TIME_HPP
#define TIME_TIME_HPP

#include <ctime>
#include <string>

class Time {
 public:
  Time();
  Time(const Time &src);
  virtual ~Time();

  Time &operator=(const Time &src);

  virtual std::string getTimeToLog() const;

 std::string convertTimeToHTTPHeaderPattern(const time_t &time) const;
 std::string convertTimeToItemDirectoryHTML(const time_t &time) const;
 std::string getCurrentTimeToStampAHTTPHeader();

};

#endif