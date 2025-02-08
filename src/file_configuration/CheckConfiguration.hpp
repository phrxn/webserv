#ifndef CHECKCONFIGURATION_HPP
#define CHECKCONFIGURATION_HPP

#include <string>
#include "URL.hpp"
#include "HTTPMethods.hpp"
#include "HTTPStatus.hpp"

class CheckConfiguration {
public:
    virtual bool isPathValid(const URL& url) const = 0;
    virtual std::string isPathARedirection(const URL& url) const = 0;
    virtual bool isTheMethodAllowedForThisPath(const URL& url, HTTPMethods::Method method) const = 0;
    virtual bool isUrlAPathToCGI(const URL& url) const = 0;
    virtual std::string getThePhysicalPath(const URL& url) const = 0;
    virtual bool isDirectoryListingAllowedForThisPath(const URL& url) const = 0;
    virtual std::string getThePathToCustomPageForHTTPStatus(HTTPStatus::Status httpStatus) const = 0;
};

#endif // CHECKCONFIGURATION_HPP