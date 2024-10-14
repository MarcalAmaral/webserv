#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include "ParserValidations.hpp"

using namespace Master;
using namespace std;

void	Parser::Validation::validateFile(const char *pathname) {
	struct stat buf;
	ifstream	file;

	if (stat(pathname, &buf) == ERROR)
		throw (runtime_error("Configuration file error:\n\tfilename: " +
		string(pathname) + "\n\terror: " + string(strerror(errno))));
	if (S_ISREG(buf.st_mode) == false)
		throw (InvalidFileException());
	file.open(pathname);
	if (file.fail()) {
		file.close();
		throw (runtime_error("Configuration file error:\n\tfilename: "
			+ string(pathname) + "\n\terror: can't open file"));
	}
	file.close();
}