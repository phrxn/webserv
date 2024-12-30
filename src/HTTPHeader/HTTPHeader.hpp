/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:48 by igenial           #+#    #+#             */
/*   Updated: 2024/11/07 20:15:47 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADER_HPP
#define HTTPHEADER_HPP

#include <iostream>
#include <map>
#include <string>

class HttpHeader
{
    private:
        std::string                         method;
		std::string                         route;
		std::string                         httpVersion;
		std::map<std::string, std::string>  headers;
        size_t                              contentLength;
        bool                                isReady = 0;
        Version                             version;
        State                               state;

    public:

    // contructors and destructors
        HttpHeader();
        ~HttpHeader();
    
    // methods
    const std::string & getMethod();
	const std::string & getRoute();
	const std::string & getHost();
    size_t getContentLength();
	std::map<std::string, std::string> & getHeaders();
    void createTheHeader()
        
}

#endif