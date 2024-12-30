/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestHandler.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:57 by igenial           #+#    #+#             */
/*   Updated: 2024/11/07 19:49:18 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <iostream>
# include <map>
# include <string>


class HttpRequest {
	enum HttpRequestState {
		HEADERS_NOT_FINISHED,
		CHUNKS_NOT_FINISHED, // Transfer Encoding chunks requests
		BODY_NOT_FINISHED, // Post requests
		FINISHED,
		ERROR
	};
	private:
		std::string method;
		std::string route;
		std::string httpVersion;
		std::map<std::string, std::string> headers;
		std::string body;
		std::string full_request;
		size_t crlfcrlf;
		size_t contentLength;
		bool chunked;
		HttpRequestState state;
		void parseHeadersKeyValue(size_t first_pos, size_t second_pos);

	public:
		HttpRequest();
		HttpRequest(const HttpRequest &);
		HttpRequest & operator=(const HttpRequest &);
		~HttpRequest();
		void append(std::string & str);
		void parseHeaders();
		const std::string & getMethod();
		const std::string & getRoute();
		const std::string & getHost();
		const std::string & getBody();
		void setRoute(std::string route);
		bool isFinished() const;
		bool error() const;
		size_t getContentLength();
		std::map<std::string, std::string> & getHeaders();

};
# endif