#include "CGIHTMLDocument.hpp"

#include "../cgi/ExecuteCGIProgram.hpp"

CGIHTMLDocument::CGIHTMLDocument(HTTPResponse &response) : _logger(LogDefault::loggerGlobal), _createCGIHTMLDocument(response){}

CGIHTMLDocument::~CGIHTMLDocument(){}

CGIHTMLDocument::CGIHTMLDocument(const CGIHTMLDocument &src) : _createCGIHTMLDocument(src._createCGIHTMLDocument){
	(void)src;
}

CGIHTMLDocument &CGIHTMLDocument::operator=(const CGIHTMLDocument &src){
	(void)src;
	return *this;
}

std::string CGIHTMLDocument::getData() const{
	return _createCGIHTMLDocument.getData();
}

std::size_t CGIHTMLDocument::getSize() const{
	return _createCGIHTMLDocument.getSize();
}

std::string CGIHTMLDocument::getMimeType() const{
	return _createCGIHTMLDocument.getMimeType();
}

std::string CGIHTMLDocument::getLastModified() const{
	return _createCGIHTMLDocument.getLastModified();
}

HTTPStatus::Status CGIHTMLDocument::getStatus() const{
	return HTTPStatus::INTERNAL_SERVER_ERROR;
}

HTMLDocument* CGIHTMLDocument::clone() const{
	return new CGIHTMLDocument(*this);
}

#include <sstream>
HTTPStatus::Status CGIHTMLDocument::createPage(const std::string &virtualHostRootPath,
    const std::string &physicalPathToResource, HTTPRequest &request){

	FilesToCGI _filesToCGI;

	if (!_filesToCGI.createFileDescriptors(request)){
		_logger->log(Log::ERROR, "CGIHTMLDocument", "createPage", "Could not create files for CGI file descriptors", "");
		return HTTPStatus::INTERNAL_SERVER_ERROR;
	}

	ProcessCGI::ExitStatus exitStatus = ExecuteCGIProgram().execute(virtualHostRootPath, physicalPathToResource, request, _filesToCGI);

	if (exitStatus == ProcessCGI::PARENT_ERROR){
		_logger->log(Log::ERROR, "CGIHTMLDocument", "createPage", "Could not execute the CGI binary", "");
		return HTTPStatus::INTERNAL_SERVER_ERROR;
	}
	if (exitStatus == ProcessCGI::CHILD_FINISHED_BY_SIGNAL){
		_logger->log(Log::ERROR, "CGIHTMLDocument", "createPage", "CGI child process terminated by timeout", "");
		return HTTPStatus::INTERNAL_SERVER_ERROR;
	}

	std::ifstream &outputFile = _filesToCGI.getOutputFile();
	std::ifstream &stderrFile = _filesToCGI.getStderrFile();

    std::stringstream ssOutput;
	std::stringstream ssStdErr;

	ssOutput << outputFile.rdbuf();
	ssStdErr << stderrFile.rdbuf();

	std::string outputStream = ssOutput.str();
	std::string stderrStream = ssStdErr.str();

	if (exitStatus == ProcessCGI::CHILD_EXIT_WITH_ERROR){
		_logger->log(Log::ERROR, "CGIHTMLDocument", "createPage", "the CGI child process was executed but returned an error status. Output produced:\n", ssStdErr.str());
		return HTTPStatus::INTERNAL_SERVER_ERROR;
	}

	if (!stderrStream.empty()){
		_logger->log(Log::WARNING, "CGIHTMLDocument", "createPage", "The child process ran normally, but produced some output on stderr:\n", stderrStream);
	}

	if(outputStream.empty()){
		_logger->log(Log::DEBUG, "CGIHTMLDocument", "createPage", "CGI output: **empty**", outputStream);
	}else{
		_logger->log(Log::DEBUG, "CGIHTMLDocument", "createPage", "CGI output:\n", outputStream);
	}

	if(stderrStream.empty()){
		_logger->log(Log::DEBUG, "CGIHTMLDocument", "createPage", "CGI stderr: **empty**", "");
	}else{
		_logger->log(Log::DEBUG, "CGIHTMLDocument", "createPage", "CGI stderr:\n", stderrStream);
	}

	// ProcessCGI::CHILD_EXIT_OK
	return _createCGIHTMLDocument.createTheCGIResponse(outputStream);
}