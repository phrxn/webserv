/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:56:46 by igenial           #+#    #+#             */
/*   Updated: 2024/11/07 20:17:04 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/HTTPHeader.hpp"

HttpHeader::HttpHeader() {};
HttpHeader::~HttpHeader() {};
    
std::map<std::string, std::string>  HttpHeader::getHeaders()
{
    return headers;
}

std::string                         HttpHeader::getMethod()
{ 
    return method;
}

std::string                         HttpHeader::getUrl()
{
    return url;
}

std::string                         HttpHeader::getHeader(std::string key)
{
    return headers[key];
}

std::string                         HttpHeader::toString()
{
    return method + " " + url;
}

void                                HttpHeader::setMethod(std::string method)
{
    this->method = method;
}
void                                HttpHeader::setUrl(std::string url)
{
    this->url = url;
}

void                                HttpHeader::addHeader(std::string key, std::string value)
{
    headers[key] = value;
}

void                                HttpHeader::removeHeader(std::string key)
{
    headers.erase(key);
}

bool                                HttpHeader::isReady()
{
    return  isReady
}

void                                HttpHeader::setReady(bool ready)
{
    isReady = ready;
}

void HttpHeader::createTheHeader()
{
    if (method == "GET")
    {
        state = Criado;
    }
    else
    {
        state = BadRequest;
    }
}