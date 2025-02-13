#ifndef DEFINES_HPP
#define DEFINES_HPP

// Color macros
# define RESET		"\033[0m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define DARKBLUE	"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define GREY		"\033[1;90m"

// Default Routes Configurations
#define DEFAULT_EMPTY ""
#define DEFAULT_LOCATION_PATH "/"
#define DEFAULT_ROOT_DIR "./static"
#define DEFAULT_INDEX_FILE "index.html"
#define DEFAULT_UPLOAD_PATH "./static/uploads"

// Default Server Configurations
#define DEFAULT_PORT 8080
#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_SERVER_NAME "localhost"
#define DEFAULT_LIMIT_BODY_SIZE 1000000 // 1MB

// Default Error pages
#define DEFAULT_ERROR_PAGE_400 "./static/error_pages/400.html" // Bad Request
#define DEFAULT_ERROR_PAGE_401 "./static/error_pages/401.html" // Unauthorized
#define DEFAULT_ERROR_PAGE_403 "./static/error_pages/403.html" // Forbidden
#define DEFAULT_ERROR_PAGE_404 "./static/error_pages/404.html" // Not Found
#define DEFAULT_ERROR_PAGE_405 "./static/error_pages/405.html" // Method Not Allowed
#define DEFAULT_ERROR_PAGE_500 "./static/error_pages/500.html" // Internal Server Error
#define DEFAULT_ERROR_PAGE_501 "./static/error_pages/501.html" // Not Implemented
#define DEFAULT_ERROR_PAGE_505 "./static/error_pages/505.html" // HTTP Version Not Supported

/* Config File Formatting Error */
# define ERROR_INVALID_SERVER "Invalid Server Block!"
# define ERROR_INVALID_LOCATION "Invalid Location Block!"
# define ERROR_INVALID_LINE "Line Must End With a Semicolon ';' !"
# define ERROR_INVALID_KEY "Invalid Key in Configuration File!"
# define ERROR_MISSING_VALUE "Missing Value In Configuration File!"
# define ERROR_DUPLICATE_KEY "Duplicate Key In Configuration File!"

/* Server Extraction Error */
# define ERROR_INVALID_PORT "Server: Invalid Port Number!"
# define ERROR_INVALID_HOST "Server: Invalid Host Address!"
# define ERROR_INVALID_LIMIT_BODY_SIZE "Server: Invalid Limit Body Size!"
# define ERROR_INVALID_ERROR_PAGE "Server: Invalid Error Page!"

/* Location Extraction Error */
# define ERROR_INVALID_METHOD "Location: Invalid HTTP Method!"
# define ERROR_INVALID_LOCATION_PATH "Location: Invalid Location Path!"
# define ERROR_INVALID_ROOT "Location: Invalid Root Path!"
# define ERROR_INVALID_UPLOAD_PATH "Location: Invalid Upload Path!"
# define ERROR_INVALID_AUTOINDEX "Location: Invalid Autoindex Value!"
# define ERROR_INVALID_UPLOAD_ENABLED "Location: Invalid Upload Enabled Value!"
# define ERROR_INVALID_CGI_PATH "Location: Invalid CGI Path!"
# define ERROR_INVALID_CGI_EXTENSION "Location: Invalid CGI Extension!"

/* Default Location Configs */
# define DEFAULT_EMPTY ""
# define DEFAULT_LOCATION_PATH "/"
# define DEFAULT_ROOT "./static"
# define DEFAULT_INDEX "index.html"
# define DEFAULT_UPLOAD_PATH "./static/uploads"

/* CGI Macros */
# define EXTENSION_PHP ".php"
# define EXTENSION_PY ".py"

/* File Error Macros */
# define ERROR_OPEN_LOG_FILE "Could Not Open Log File!"
# define ERROR_NOT_CONFIG_FILE "Config File Not Provided!"
# define ERROR_OPEN_CONFIG_FILE "Could Not Opening Config File!"
# define ERROR_EMPTY_CONFIG_FILE "Config File Is Empty!"

#endif
