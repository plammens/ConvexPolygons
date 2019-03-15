#include "utils.h"

using namespace std;

void format(string::const_iterator &it, const string::const_iterator &end, ostream &os) {
    for (; it < end; ++it) os << *it;
}
