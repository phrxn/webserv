/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestHandler.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:39 by igenial           #+#    #+#             */
/*   Updated: 2024/11/07 19:54:45 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/HTTPRequest.hpp"

#include <cstdlib>

HttpRequest::HttpRequest() {
    this->state = HttpRequest::HEADERS_NOT_FINISHED;
    this->contentLength = 0;
    this->chunked = false;
}

HttpRequest::~HttpRequest() {

}

HttpRequest::HttpRequest(const HttpRequest & src) {
    *this = src;
}

void HttpRequest::parseHeadersKeyValue(size_t first_pos, size_t last_pos)
{
    size_t second_pos;
    std::string key, value;

    second_pos = this->full_request.find(": ", first_pos);
    if (second_pos == std::string::npos) {
        this->state = HttpRequest::ERROR;
        return ;
    } else {
        key = this->full_request.substr(first_pos, second_pos - first_pos);
        value = this->full_request.substr(second_pos + 2, last_pos - second_pos - 2);
        if (value == "") {
            this->state = HttpRequest::ERROR;
        } else if ((key == "Transfer-Encoding" || key == "transfer-encoding") && value == "chunked") {
            this->chunked = true;
        } else if (key == "Content-Length" || key == "content-length") {
            this->contentLength = atoi(value.c_str());
        } else {
            this->headers[key] = value;
        }
    }
}

void HttpRequest::parseHeaders()
{
    size_t first_pos = 0, second_pos;

    second_pos = this->full_request.find(' ', 0);
    if (second_pos == std::string::npos) {
        this->state = HttpRequest::ERROR;
        return ;
    } else {
        this->method =  this->full_request.substr(first_pos, second_pos - first_pos);
    }
    first_pos = second_pos + 1;
    second_pos = this->full_request.find(' ', first_pos);
    if (second_pos == std::string::npos) {
        this->state = HttpRequest::ERROR;
        return ;
    } else {
        this->route = this->full_request.substr(first_pos, second_pos - first_pos);
    }
    first_pos = second_pos + 1;
    second_pos = this->full_request.find("\r\n", first_pos);
    if (second_pos == std::string::npos) {
        this->state = HttpRequest::ERROR;
        return ;
    } else {
        this->httpVersion =  this->full_request.substr(first_pos, second_pos - first_pos);
    }

    while (this->crlfcrlf != second_pos)
    {
        first_pos = second_pos + 2;
        second_pos = this->full_request.find("\r\n", first_pos);
        this->parseHeadersKeyValue(first_pos, second_pos);
        if (second_pos == std::string::npos)
            this->state = HttpRequest::ERROR;
        if (this->state == HttpRequest::ERROR)
            break;
    }

}

void HttpRequest::append(std::string & str)
{
    this->full_request.append(str);
    if (this->state == HttpRequest::HEADERS_NOT_FINISHED) {
        this->crlfcrlf = this->full_request.find("\r\n\r\n");
        if (this->crlfcrlf != std::string::npos) {
            if (this->full_request.find("GET", 0, 3) != std::string::npos) {
                this->state = HttpRequest::FINISHED;
                this->parseHeaders();
            } else if (this->full_request.find("POST", 0, 4) != std::string::npos
                || this->full_request.find("PUT", 0, 3) != std::string::npos
                || this->full_request.find("DELETE", 0, 6) != std::string::npos)
            {
                this->state = HttpRequest::BODY_NOT_FINISHED;
                this->parseHeaders();
            } else if (this->full_request.find("HEAD", 0, 4) != std::string::npos) {
                this->state = HttpRequest::FINISHED;
                this->parseHeaders();
            } else {
                this->state = HttpRequest::ERROR; // Unrecognized metod
            }
        }
    }
    if (this->state == HttpRequest::BODY_NOT_FINISHED) {
        // Count the length of the body according to the content length
        if (this->chunked) {
            if (this->full_request.find("\r\n\r\n", this->crlfcrlf + 4) != std::string::npos)
            {
                this->state = HttpRequest::FINISHED;
                // unchunk the body. Interpret the hexa numbers and remove the \r\n
                std::string chunkedBody = this->full_request.substr(this->crlfcrlf + 4);
                std::string unchunkedBody = "";
                size_t chunkSize;
                size_t chunkStart = 0;
                size_t chunkEnd;

                while (chunkStart < chunkedBody.size())
                {
                    chunkSize = strtol(chunkedBody.substr(chunkStart, chunkedBody.find("\r\n", chunkStart) - chunkStart).c_str(), NULL, 16);
                    chunkEnd = chunkedBody.find("\r\n", chunkStart) + 2 + chunkSize;
                    unchunkedBody += chunkedBody.substr(chunkedBody.find("\r\n", chunkStart) + 2, chunkSize);
                    chunkStart = chunkEnd;
                }
                this->body = unchunkedBody;

                // set content length
                this->contentLength = this->body.size();
            }
        }
        else if (this->full_request.size() == this->contentLength + this->crlfcrlf + 4)
        {
            this->state = HttpRequest::FINISHED;
            this->body = this->full_request.substr(this->crlfcrlf + 4);
        }
        else if (this->full_request.size() > this->contentLength + this->crlfcrlf + 4) {
            this->state = HttpRequest::ERROR; // Content length larger
        }
    }
}

bool HttpRequest::isFinished() const
{
    return this->error() || this->state == HttpRequest::FINISHED;
}

bool HttpRequest::error() const
{
	return this->state == HttpRequest::ERROR;
}

const std::string & HttpRequest::getHost()
{
    return this->headers["Host"];
}

const std::string & HttpRequest::getMethod()
{
    return this->method;
}

const std::string & HttpRequest::getRoute()
{
    return this->route;
}

const std::string & HttpRequest::getBody()
{
    return this->body;
}

void HttpRequest::setRoute(std::string route)
{
    this->route = route;
}

size_t HttpRequest::getContentLength()
{
    return this->contentLength;
}

std::map<std::string, std::string> & HttpRequest::getHeaders()
{
    return this->headers;
}

HttpRequest & HttpRequest::operator=(HttpRequest const&src) {
    if (this != &src)
    {
        this->full_request = src.full_request;
        this->method = src.method;
        this->route = src.route;
        this->httpVersion = src.httpVersion;
        this->headers = src.headers;
        this->body = src.body;
        this->crlfcrlf = src.crlfcrlf;
        this->contentLength = src.contentLength;
        this->state = src.state;
        this->chunked = src.chunked;
    }
    return (*this);
}