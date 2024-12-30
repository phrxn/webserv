/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:39 by igenial           #+#    #+#             */
/*   Updated: 2024/11/07 19:54:45 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <map>
# include <iostream>
# include <cstdlib>
# include <fstream>

# include "ErrorCode.hpp"

class HttpResponse
{
	private:
		std::map<std::string, std::string> headers;
		std::string response;
		std::string statusMessage;

	public:
		HttpResponse();
		HttpResponse & operator=(const HttpResponse &);
		~HttpResponse();

		void addHeader(std::string key, std::string value);
		const char * c_str();
		size_t size() const;
		void setStatusMessage(std::string statusMessage);
		std::string getResponse() const;
		void setResponse(std::string response);
		void buildResponse(std::map<int, std::string> errorNumberToLocation);

};

#endif