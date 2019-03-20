
#include <utils.h>
#include <boost/format.hpp>
#include "consts.h"


using namespace std;


int checkDirectory(const string &dir) {
    return system((boost::format("mkdir -p %s") % dir).str().c_str());
}


void prefixPath(string &filePath, const string &prefixPath) {
    if (checkDirectory(prefixPath) != 0) throw IOError("directory " + prefixPath);
    filePath.insert(0, prefixPath);
}


bool numericEquals(const double a, const double b) {
    return abs(a - b) < NUM::EPSILON;
}
