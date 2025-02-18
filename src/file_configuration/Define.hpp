#ifndef FILE_CONFIGURATION_DEFINES_HPP
#define FILE_CONFIGURATION_DEFINES_HPP

/* Config File Formatting Error */
# define ERROR_INVALID_SERVER "Invalid Server Block!"
# define ERROR_INVALID_LOCATION "Invalid Location Block!"
# define ERROR_INVALID_LINE "Line Must End With a Semicolon ';' !"
# define ERROR_INVALID_KEY "Invalid Key in Configuration File!"
# define ERROR_MISSING_VALUE "Missing Value In Configuration File!"
# define ERROR_DUPLICATE_KEY "Duplicate Key In Configuration File!"

/* Server Extraction Error */
# define ERROR_INVALID_PORT "Server: Invalid Port Number!"
# define ERROR_INVALID_LIMIT_BODY_SIZE "Server: Invalid Limit Body Size!"
# define ERROR_INVALID_ERROR_PAGE "Server: Invalid Error Page!"

/* Location Extraction Error */
# define ERROR_INVALID_METHOD "Location: Invalid HTTP Method!"
# define ERROR_INVALID_LOCATION_PATH "Location: Invalid Location Path!"
# define ERROR_INVALID_LOCATION_PATH_WITHOUT_END_SLASH "Location: Invalid Location Path. Location Path must ends with a slash!"
# define ERROR_INVALID_ROOT "Location: Invalid Root Path!"
# define ERROR_INVALID_ROOT_WITHOUT_END_SLASH "Location: Invalid Root Path. Root Path must ends with a slash!"
# define ERROR_INVALID_UPLOAD_PATH "Location: Invalid Upload Path!"
# define ERROR_INVALID_AUTOINDEX "Location: Invalid Autoindex Value!"
# define ERROR_INVALID_UPLOAD_ENABLED "Location: Invalid Upload Enabled Value!"
# define ERROR_INVALID_CGI_PATH "Location: Invalid CGI Path!"
# define ERROR_INVALID_CGI_ENABLE_OPTION "Location: Invalid CGI Enabled Value!"

/* Default Location Configs */
# define DEFAULT_ROOT "./static"

/* CGI Macros enable */
# define ENABLE "on"
# define DISENABLE "off"

/* File Error Macros */
# define ERROR_OPEN_CONFIG_FILE "Could Not Opening Config File!"

#endif
