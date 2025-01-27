#ifndef START_LOADER_OF_PROGRAM_FILES_HPP
#define START_LOADER_OF_PROGRAM_FILES_HPP

#include <list>

#include "../error/Log.hpp"

class LoaderOfProgramFiles{

public:
	LoaderOfProgramFiles(Log *logger);
	~LoaderOfProgramFiles();
	LoaderOfProgramFiles(const LoaderOfProgramFiles &src);
	LoaderOfProgramFiles &operator=(const LoaderOfProgramFiles &src);

	bool loaderAllProgramThings(int argc, char **argv);

	bool checkParameters(int argc) const;

	bool loadMimetypeListFromFile(Log *logger) const;

	bool loadConfigurarionFile(char **argv);

	void setLogger(Log *logger);

	const std::list<int> &getListOfAllVirtualHostPorts() const;


private:
	Log *_logger;
	std::list<int> _allVirtualHostPorts;

};

#endif