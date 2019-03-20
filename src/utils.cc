
#include <utils.h>
#include <boost/format.hpp>


using namespace std;


void checkDirectory(const string &dir) {
    system((boost::format("mkdir -p %s") % dir).str().c_str());
}


void prefixPath(string &filePath, const string &prefixPath) {
    checkDirectory(prefixPath);
    filePath.insert(0, prefixPath);
}
