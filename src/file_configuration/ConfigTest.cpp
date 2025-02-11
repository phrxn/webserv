#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CheckConfiguration.hpp"
#include "../net/URL.hpp"
#include "../net/http/HTTPMethods.hpp"
#include "../net/http/HTTPStatus.hpp"

using ::testing::Return;

class CheckConfigurationMock : public CheckConfiguration {
public:
    MOCK_METHOD(bool, isPathValid, (const URL& url), (const, override));
    MOCK_METHOD(std::string, isPathARedirection, (const URL& url), (const, override));
    MOCK_METHOD(bool, isTheMethodAllowedForThisPath, (const URL& url, HTTPMethods::Method method), (const, override));
    MOCK_METHOD(bool, isUrlAPathToCGI, (const URL& url), (const, override));
    MOCK_METHOD(std::string, getThePhysicalPath, (const URL& url), (const, override));
    MOCK_METHOD(bool, isDirectoryListingAllowedForThisPath, (const URL& url), (const, override));
    MOCK_METHOD(std::string, getThePathToCustomPageForHTTPStatus, (HTTPStatus::Status httpStatus), (const, override));

    virtual ~CheckConfigurationMock() {} // Adiciona um destrutor virtual
};

class URLMock : public URL {
public:
    URLMock(const std::string& url) : URL() {
        // Simula a inicialização do URL com uma string
    }
};

class CheckConfigurationTest : public ::testing::Test {
protected:
    CheckConfigurationMock* configMock;

    void SetUp() override {
        configMock = new CheckConfigurationMock();
    }

    void TearDown() override {
        delete configMock;
    }
};

TEST_F(CheckConfigurationTest, IsPathValid) {
    URLMock url("/valid/path");
    EXPECT_CALL(*configMock, isPathValid(url)).WillOnce(Return(true));
    EXPECT_TRUE(configMock->isPathValid(url));

    URLMock invalidUrl("/invalid/path");
    EXPECT_CALL(*configMock, isPathValid(invalidUrl)).WillOnce(Return(false));
    EXPECT_FALSE(configMock->isPathValid(invalidUrl));
}

TEST_F(CheckConfigurationTest, IsPathARedirection) {
    URLMock url("/redirect/path");
    EXPECT_CALL(*configMock, isPathARedirection(url)).WillOnce(Return("http://www.example.com"));
    EXPECT_EQ(configMock->isPathARedirection(url), "http://www.example.com");

    URLMock noRedirectUrl("/no/redirect/path");
    EXPECT_CALL(*configMock, isPathARedirection(noRedirectUrl)).WillOnce(Return(""));
    EXPECT_EQ(configMock->isPathARedirection(noRedirectUrl), "");
}

TEST_F(CheckConfigurationTest, IsTheMethodAllowedForThisPath) {
    URLMock url("/valid/path");
    EXPECT_CALL(*configMock, isTheMethodAllowedForThisPath(url, HTTPMethods::GET)).WillOnce(Return(true));
    EXPECT_TRUE(configMock->isTheMethodAllowedForThisPath(url, HTTPMethods::GET));

    EXPECT_CALL(*configMock, isTheMethodAllowedForThisPath(url, HTTPMethods::POST)).WillOnce(Return(false));
    EXPECT_FALSE(configMock->isTheMethodAllowedForThisPath(url, HTTPMethods::POST));
}

TEST_F(CheckConfigurationTest, IsUrlAPathToCGI) {
    URLMock url("/cgi/path");
    EXPECT_CALL(*configMock, isUrlAPathToCGI(url)).WillOnce(Return(true));
    EXPECT_TRUE(configMock->isUrlAPathToCGI(url));

    URLMock noCgiUrl("/no/cgi/path");
    EXPECT_CALL(*configMock, isUrlAPathToCGI(noCgiUrl)).WillOnce(Return(false));
    EXPECT_FALSE(configMock->isUrlAPathToCGI(noCgiUrl));
}

TEST_F(CheckConfigurationTest, GetThePhysicalPath) {
    URLMock url("/virtual/path");
    EXPECT_CALL(*configMock, getThePhysicalPath(url)).WillOnce(Return("/real/path"));
    EXPECT_EQ(configMock->getThePhysicalPath(url), "/real/path");

    URLMock physicalUrl("/physical/path");
    EXPECT_CALL(*configMock, getThePhysicalPath(physicalUrl)).WillOnce(Return("/physical/path"));
    EXPECT_EQ(configMock->getThePhysicalPath(physicalUrl), "/physical/path");
}

TEST_F(CheckConfigurationTest, IsDirectoryListingAllowedForThisPath) {
    URLMock url("/directory/listing");
    EXPECT_CALL(*configMock, isDirectoryListingAllowedForThisPath(url)).WillOnce(Return(true));
    EXPECT_TRUE(configMock->isDirectoryListingAllowedForThisPath(url));

    URLMock noListingUrl("/no/directory/listing");
    EXPECT_CALL(*configMock, isDirectoryListingAllowedForThisPath(noListingUrl)).WillOnce(Return(false));
    EXPECT_FALSE(configMock->isDirectoryListingAllowedForThisPath(noListingUrl));
}

TEST_F(CheckConfigurationTest, GetThePathToCustomPageForHTTPStatus) {
    EXPECT_CALL(*configMock, getThePathToCustomPageForHTTPStatus(HTTPStatus::NOT_FOUND)).WillOnce(Return("/custom/404.html"));
    EXPECT_EQ(configMock->getThePathToCustomPageForHTTPStatus(HTTPStatus::NOT_FOUND), "/custom/404.html");

    EXPECT_CALL(*configMock, getThePathToCustomPageForHTTPStatus(HTTPStatus::INTERNAL_SERVER_ERROR)).WillOnce(Return("/custom/500.html"));
    EXPECT_EQ(configMock->getThePathToCustomPageForHTTPStatus(HTTPStatus::INTERNAL_SERVER_ERROR), "/custom/500.html");

    EXPECT_CALL(*configMock, getThePathToCustomPageForHTTPStatus(HTTPStatus::OK)).WillOnce(Return(""));
    EXPECT_EQ(configMock->getThePathToCustomPageForHTTPStatus(HTTPStatus::OK), "");
}