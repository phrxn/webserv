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

  URLBuilder &setPathFull(const std::string &path) {
    url.setPathFull(path);
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

TEST(URLTest, getPathFull_decoded){

	URL url("https://exemplo.com/pasta%20com%20espaço%3Bcom%20ponto%20e%20vírgula");

	EXPECT_EQ(url.getPathFull(true), "/pasta com espaço;com ponto e vírgula");
}

TEST(URLTest, getPathFull_NotDecoded){

	URL url("https://exemplo.com/pasta%20com%20espaço%3Bcom%20ponto%20e%20vírgula");

	EXPECT_EQ(url.getPathFull(false), "/pasta%20com%20espaço%3Bcom%20ponto%20e%20vírgula");
}

TEST(URLTest, getPathFullButPathWasQueryString_decoded){

	URL url("https://exemplo.com/pasta%20com%20espaço%3Bcom%20ponto%20e%20vírgula?query=1");

	EXPECT_EQ(url.getPathFull(true), "/pasta com espaço;com ponto e vírgula");
}

TEST(URLTest, getPathFullButPathWasQueryString_NotDecoded){

	URL url("https://exemplo.com/pasta%20com%20espaço%3Bcom%20ponto%20e%20vírgula?query=1");

	EXPECT_EQ(url.getPathFull(false), "/pasta%20com%20espaço%3Bcom%20ponto%20e%20vírgula");
}

//--------------------------------------------------------------

TEST(URLTest, getPath_emptyPath){

	URL url("https://exemplo.com");

	EXPECT_EQ(url.getPath(true), "");
}

TEST(URLTest, getPath_pathDoesntHaveExtraPath){

	URL url("https://exemplo.com/foo");

	EXPECT_EQ(url.getPath(true), "/foo");

}

TEST(URLTest, getPath_pathHaveACGIAndItDoesntHaveAnExtraPath){

	URL url("https://exemplo.com/file.php");

	EXPECT_EQ(url.getPath(false), "/file.php");

}

TEST(URLTest, getPath_pathHaveACGIAndItHaveAnExtraPath){

	URL url("https://exemplo.com/file.php/");

	EXPECT_EQ(url.getPath(false), "/file.php");

}

TEST(URLTest, getPath_pathHaveACGIAndItHaveAnExtraPath2){

	URL url("https://exemplo.com/file.php/extra.php/foo");

	EXPECT_EQ(url.getPath(false), "/file.php");

}

//--------------------------------------------------------------

TEST(URLTest, getExtraPathFromFullPath_emptyPath){

	URL url("https://exemplo.com");

	EXPECT_EQ(url.getExtraPathFromFullPath(), "");
}

TEST(URLTest, getExtraPathFromFullPath_pathHaveACGIAndItDoesntHaveAnExtraPath){

	URL url("https://exemplo.com/file.php");

	EXPECT_EQ(url.getExtraPathFromFullPath(), "");

}

TEST(URLTest, getExtraPathFromFullPath_pathHaveACGIAndItHaveAnExtraPath){

	URL url("https://exemplo.com/file.php/");

	EXPECT_EQ(url.getExtraPathFromFullPath(), "/");

}

TEST(URLTest, ggetExtraPathFromFullPath_pathHaveACGIAndItHaveAnExtraPath2){

	URL url("https://exemplo.com/file.php/extra.php/foo");

	EXPECT_EQ(url.getExtraPathFromFullPath(), "/extra.php/foo");

}

TEST(URLTest, ggetExtraPathFromFullPath_pathHaveACGIAndItHaveAnExtraPath3){

	URL url("https://exemplo.com/file.php/extra.php");

	EXPECT_EQ(url.getExtraPathFromFullPath(), "/extra.php");

}

//--------------------------------------------------------------


TEST(URLTest, parserStringToURL_FullValidURL) {
  URLBuilder urlBuilder;
  URL urlToCompare = urlBuilder.setProtocol("abcd")
                         .setDomain("www.a.com")
                         .setPort(9090)
                         .setPathFull("/a/b.php")
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
                         .setPathFull("/a/b.php")
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
                         .setPathFull("/a/b.php")
                         .setQuery("")
                         .build();

  URL url;
  url.parserStringToURL("/a/b.php");

  EXPECT_EQ(urlToCompare, url);
}


TEST(URLTest, parserStringToURL_OnlyPathWithPHPTextAndExtraPath) {
  URLBuilder urlBuilder;
  URL urlToCompare = urlBuilder.setProtocol("")
                         .setDomain("")
                         .setPort(0)
                         .setPathFull("/a/b.php/more/path")
                         .setQuery("")
                         .build();

  URL url;
  url.parserStringToURL("/a/b.php/more/path");

  EXPECT_EQ(urlToCompare, url);
}

TEST(URLTest, parserStringToURL_OnlyPathWithDomainAndPath) {
  URLBuilder urlBuilder;
  URL urlToCompare = urlBuilder.setProtocol("https")
                         .setDomain("www.exemple.com")
                         .setPort(0)
                         .setPathFull("")
                         .setQuery("")
                         .build();

  URL url;
  url.parserStringToURL("https://www.exemple.com");

  EXPECT_EQ(urlToCompare, url);

}

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
  EXPECT_EQ(urlString, "");
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

TEST(URLTest, extractQuery_stringWithQuery) {
  URL url;

  std::string urlString("?a=b");

  std::string query = url.extractQuery(urlString);

  EXPECT_EQ(query, "a=b");
  EXPECT_EQ(urlString, "");
}

TEST(URLTest, extractQuery_stringIsntAQueryString) {
  URL url;

  std::string urlString("foo");

  std::string query = url.extractQuery(urlString);

  EXPECT_EQ(query, "foo");
  EXPECT_EQ(urlString, "foo");
}

TEST(URLTest, extractQuery_stringIsntAQueryString2) {
  URL url;

  std::string urlString("a=b");

  std::string query = url.extractQuery(urlString);

  EXPECT_EQ(query, "a=b");
  EXPECT_EQ(urlString, "a=b");
}

//-------------------------------------------------------------

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

// ---------------------------------------------------------------

TEST(URLTest, removePathToExtraPath_emptyPath){

	URL url;

	std::string pathFull = "";

	std::string extraPath = url.removePathToExtraPath(pathFull, HTTPTypeOfPages::TypeOfPage::STATIC);

	EXPECT_EQ("", extraPath);
}

TEST(URLTest, removePathToExtraPath_emptyPathCGI){

	URL url;

	std::string pathFull = "";

	std::string extraPath = url.removePathToExtraPath(pathFull, HTTPTypeOfPages::TypeOfPage::PHP);

	EXPECT_EQ("", extraPath);
}

TEST(URLTest, removePathToExtraPath_pathIsOnlyCGI){

	URL url;

	std::string pathFull = ".php";

	std::string extraPath = url.removePathToExtraPath(pathFull, HTTPTypeOfPages::TypeOfPage::PHP);

	EXPECT_EQ("", extraPath);
}

TEST(URLTest, removePathToExtraPath_pathEndsWithCGI){

	URL url;

	std::string pathFull = "/foo/a.php";

	std::string extraPath = url.removePathToExtraPath(pathFull, HTTPTypeOfPages::TypeOfPage::PHP);

	EXPECT_EQ("", extraPath);
}

TEST(URLTest, removePathToExtraPath_pathIsACGIAndEndsWithSlash){

	URL url;

	std::string pathFull = "/foo/a.php/";

	std::string extraPath = url.removePathToExtraPath(pathFull, HTTPTypeOfPages::TypeOfPage::PHP);

	EXPECT_EQ("/", extraPath);
}

TEST(URLTest, removePathToExtraPath_pathIsACGIAndEndsWithAExtraPathWithSameExtension){

	URL url;

	std::string pathFull = "/foo/a.php/delete.php";

	std::string extraPath = url.removePathToExtraPath(pathFull, HTTPTypeOfPages::TypeOfPage::PHP);

	EXPECT_EQ("/delete.php", extraPath);
}