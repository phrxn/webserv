#ifndef START_LOADER_OF_PROGRAM_FILES_HPP
#define START_LOADER_OF_PROGRAM_FILES_HPP

#include "../error/Log.hpp"

class LoaderOfProgramFiles{

public:
	LoaderOfProgramFiles(Log *logger);
	~LoaderOfProgramFiles();
	LoaderOfProgramFiles(const LoaderOfProgramFiles &src);
	LoaderOfProgramFiles &operator=(const LoaderOfProgramFiles &src);

	bool loaderAllProgramThings(int argc, char **argv) const;

	bool checkParameters(int argc) const;

	bool loadMimetypeListFromFile(Log *logger) const;

	void setLogger(Log *logger);

private:
	Log *_logger;

};

#endif