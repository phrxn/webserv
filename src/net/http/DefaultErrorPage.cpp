#include "DefaultErrorPage.hpp"

DefaultErrorPage::DefaultErrorPage() : _data(""), _size(_data.size()) {

}
DefaultErrorPage::DefaultErrorPage(const std::string &data) {
	_data = data;
	_size = data.size();
}
DefaultErrorPage::~DefaultErrorPage() {}

DefaultErrorPage::DefaultErrorPage(const DefaultErrorPage &src) {
	*this = src;
}

DefaultErrorPage &DefaultErrorPage::operator=(const DefaultErrorPage &src) {
	if (this == &src) return *this;
	_data = src._data;
	_size = src._size;
	return *this;
}

std::string DefaultErrorPage::getData() const {
	return _data;
}
std::string::size_type DefaultErrorPage::getSize() const {
	return _size;
}