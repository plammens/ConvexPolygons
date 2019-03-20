
#include <utils.h>
#include <boost/format.hpp>


using namespace std;


int checkDirectory(const string &dir) {
    return system((boost::format("mkdir -p %s") % dir).str().c_str());
}


void prefixPath(string &filePath, const string &prefixPath) {
    if (checkDirectory(prefixPath) != 0) throw IOError("directory " + prefixPath);
    filePath.insert(0, prefixPath);
}
