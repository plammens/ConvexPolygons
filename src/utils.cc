
#include <utils.h>


using namespace std;

void _format(string::const_iterator &it, const string::const_iterator &end, ostream &os) {
    for (; it < end; ++it) os << *it;
}


void checkDirectory(const string &dir) {
    system(format("mkdir -p %", dir).c_str());
}


void prefixPath(string &filePath, const string &prefixPath) {
    checkDirectory(prefixPath);
    filePath.insert(0, prefixPath);
}
