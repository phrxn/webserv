#include "Time.hpp"

#include <ctime>
#include <string>

Time::Time() {}

Time::Time(const Time &src) { *this = src; }
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

std::string Time::convertTimeToHTTPHeaderPattern(const time_t &time) const {
  struct tm *gmt = gmtime(&time);

  char formattedDate[100];
  strftime(formattedDate, sizeof(formattedDate), "%a, %d %b %Y %H:%M:%S GMT",
           gmt);

  return formattedDate;
}

std::string Time::convertTimeToItemDirectoryHTML(const time_t &time) const {
  struct tm *gmt = gmtime(&time);

  char formattedDate[100];
  strftime(formattedDate, sizeof(formattedDate), "%d-%b-%Y %H:%M", gmt);

  return formattedDate;
}

std::string Time::getCurrentTimeToStampAHTTPHeader() {
  std::time_t now = std::time(0);
  return convertTimeToHTTPHeaderPattern(now);
}