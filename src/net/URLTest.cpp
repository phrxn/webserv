#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "URL.hpp"

#include <cctype>

class URLBuilder {
 public:
  URLBuilder &setProtocol(const std::string &protocol) {
    url.setProtocol(protocol);
    return *this;
  }

  URLBuilder &setDomain(const std::string &domain) {
    url.setDomain(domain);
    return *this;
  }

  URLBuilder &setPort(int port) {
    url.setPort(port);
    return *this;
  }

  URLBuilder &setPath(const std::string &path) {
    url.setPath(path);
    return *this;
  }

  URLBuilder &setQuery(const std::string &query) {
    url.setQuery(query);
    return *this;
  }

  URL build() { return url; }

 private:
  URL url;
};

//--------------------------------------------------------------

TEST(URLTest, extractProtocol_emptyString) {
  URL url;

  std::string urlString("");

  std::string protocol = url.extractProtocol(urlString);

  EXPECT_EQ(protocol, "");
  EXPECT_EQ(urlString, "");
}

TEST(URLTest, extractProtocol_stringWithProtocol) {
  URL url;

  std::string urlString("foo://");

  std::string protocol = url.extractProtocol(urlString);

  EXPECT_EQ(protocol, "foo");
  EXPECT_EQ(urlString, "");
}

TEST(URLTest, extractProtocol_stringWithProtocolAndDomain) {
  URL url;

  std::string urlString("foo://domain.com");

  std::string protocol = url.extractProtocol(urlString);

  EXPECT_EQ(protocol, "foo");
  EXPECT_EQ(urlString, "domain.com");
}

TEST(URLTest, extractProtocol_stringBeginWithSlash) {
  URL url;

  std::string urlString("/aaa/bbb");

  std::string protocol = url.extractProtocol(urlString);

  EXPECT_EQ(protocol, "");
  EXPECT_EQ(urlString, "/aaa/bbb");
}

//--------------------------------------------------------------

TEST(URLTest, extractDomain_domainWithoutPortAndWithoutPath) {
  URL url;

  std::string urlString("www.a.com");

  std::string domain = url.extractDomain(urlString);

  EXPECT_EQ(domain, "www.a.com");
  EXPECT_EQ(urlString, "www.a.com");
}

TEST(URLTest, extractDomain_domainWithPortAndNoPath) {
  URL url;

  std::string urlString("www.a.com:8080");

  std::string domain = url.extractDomain(urlString);

  EXPECT_EQ(domain, "www.a.com");
  EXPECT_EQ(urlString, ":8080");
}

TEST(URLTest, extractDomain_domainWithoutPortAndWithPath) {
  URL url;

  std::string urlString("www.a.com/a/b");

  std::string domain = url.extractDomain(urlString);

  EXPECT_EQ(domain, "www.a.com");
  EXPECT_EQ(urlString, "/a/b");
}

TEST(URLTest, extractDomain_domainWithPortAndPath) {
  URL url;

  std::string urlString("www.a.com:8080/a/b");

  std::string domain = url.extractDomain(urlString);

  EXPECT_EQ(domain, "www.a.com");
  EXPECT_EQ(urlString, ":8080/a/b");
}

TEST(URLTest, extractDomain_stringIsOnlyAPath) {
  URL url;

  std::string urlString("/aaa");

  std::string domain = url.extractDomain(urlString);

  EXPECT_EQ(domain, "");
  EXPECT_EQ(urlString, "/aaa");
}

//--------------------------------------------------------------

TEST(URLTest, extractPort_stringWithoutPort) {
  URL url;

  std::string urlString("www.a.com");

  std::string port = url.extractPort(urlString);

  EXPECT_EQ(port, "www.a.com");
  EXPECT_EQ(urlString, "www.a.com");
}

TEST(URLTest, extractPort_stringWithPort) {
  URL url;

  std::string urlString(":8080");

  std::string port = url.extractPort(urlString);

  EXPECT_EQ(port, "8080");
  EXPECT_EQ(urlString, "");
}

TEST(URLTest, extractPort_stringWithPortAndPath) {
  URL url;

  std::string urlString(":8080/aaaaa");

  std::string port = url.extractPort(urlString);

  EXPECT_EQ(port, "8080");
  EXPECT_EQ(urlString, "/aaaaa");
}

TEST(URLTest, extractPort_stringIsOnlyPath) {
  URL url;

  std::string urlString("/aaaaa");

  std::string port = url.extractPort(urlString);

  EXPECT_EQ(port, "/aaaaa");
  EXPECT_EQ(urlString, "/aaaaa");
}

//--------------------------------------------------------------

TEST(URLTest, extractPath_stringIsOnlyPath) {
  URL url;

  std::string urlString("/aaaaa");

  std::string path = url.extractPath(urlString);

  EXPECT_EQ(path, "/aaaaa");
  EXPECT_EQ(urlString, "");
}

TEST(URLTest, extractPath_stringWithPathAndQueryString) {
  URL url;

  std::string urlString("/aaaaa?a=b");

  std::string path = url.extractPath(urlString);

  EXPECT_EQ(path, "/aaaaa");
  EXPECT_EQ(urlString, "?a=b");
}

//--------------------------------------------------------------

TEST(URLTest, extractPath_stringWithQuery) {
  URL url;

  std::string urlString("?a=b");

  std::string query = url.extractQuery(urlString);

  EXPECT_EQ(query, "a=b");
  EXPECT_EQ(urlString, "");
}

TEST(URLTest, extractPath_stringIsntAQueryString) {
  URL url;

  std::string urlString("foo");

  std::string query = url.extractQuery(urlString);

  EXPECT_EQ(query, "foo");
  EXPECT_EQ(urlString, "foo");
}

TEST(URLTest, extractPath_stringIsntAQueryString2) {
  URL url;

  std::string urlString("a=b");

  std::string query = url.extractQuery(urlString);

  EXPECT_EQ(query, "a=b");
  EXPECT_EQ(urlString, "a=b");
}

//--------------------------------------------------------------

TEST(URLTest, parserStringToURL_FullValidURL) {
  URLBuilder urlBuilder;
  URL urlToCompare = urlBuilder.setProtocol("abcd")
                         .setDomain("www.a.com")
                         .setPort(9090)
                         .setPath("/a/b.php")
                         .setQuery("z=1;x=2")
                         .build();

  URL url;
  url.parserStringToURL("abcd://www.a.com:9090/a/b.php?z=1;x=2");

  EXPECT_EQ(urlToCompare, url);
}

TEST(URLTest, parserStringToURL_PathAndQueryString) {
  URLBuilder urlBuilder;
  URL urlToCompare = urlBuilder.setProtocol("")
                         .setDomain("")
                         .setPort(0)
                         .setPath("/a/b.php")
                         .setQuery("z=1;x=2")
                         .build();

  URL url;
  url.parserStringToURL("/a/b.php?z=1;x=2");

  EXPECT_EQ(urlToCompare, url);
}

TEST(URLTest, parserStringToURL_OnlyPath) {
  URLBuilder urlBuilder;
  URL urlToCompare = urlBuilder.setProtocol("")
                         .setDomain("")
                         .setPort(0)
                         .setPath("/a/b.php")
                         .setQuery("")
                         .build();

  URL url;
  url.parserStringToURL("/a/b.php");

  EXPECT_EQ(urlToCompare, url);
}

//--------------------------------------------------------------

TEST(URLTest, decode_testCaseInsensitive) {

  URL url;

  std::string decodedValue = url.decode("foo%5fbar");
  std::string decodedValue2 = url.decode("foo%5Fbar");

  EXPECT_EQ("foo_bar", decodedValue);
  EXPECT_EQ("foo_bar", decodedValue2);

}

TEST(URLTest, decode_onlyOneCharacterEncoded) {

  URL url;

  std::string decodedValue = url.decode("%5f");

  EXPECT_EQ("_", decodedValue);

}

TEST(URLTest, decode_emptyString) {

  URL url;

  std::string decodedValue = url.decode("");

  EXPECT_EQ("", decodedValue);

}

TEST(URLTest, decode_invalidEncoded) {

  URL url;

  std::string decodedValue = url.decode("%5g");

  EXPECT_EQ("%5g", decodedValue);

}

TEST(URLTest, decode_invalidEncodedOnlyOneChar) {

  URL url;

  std::string decodedValue = url.decode("%5");

  EXPECT_EQ("%5", decodedValue);

}

TEST(URLTest, decode_invalidEncodedOnlyThePercentChar) {

  URL url;

  std::string decodedValue = url.decode("%");

  EXPECT_EQ("%", decodedValue);

}

TEST(URLTest, decode_invalidEncodedTwoPorcentChars) {

  URL url;

  std::string decodedValue = url.decode("%%");

  EXPECT_EQ("%%", decodedValue);

}

TEST(URLTest, decode_decodeSpaceAndQuestionMake) {

  URL url;

  std::string decodedValue = url.decode("cgi_variables.php/aaa%20bbbb%3F;year=2024&month=06");

  EXPECT_EQ("cgi_variables.php/aaa bbbb?;year=2024&month=06", decodedValue);

}
