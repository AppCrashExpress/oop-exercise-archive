#include "Shape.h"
using namespace std;


int main()
{
    typedef pair<int, int> IntPair;
    typedef pair<double, double> DoublePair;
    IntPair a, b, c, d;

    a = make_pair(0, 0);
    b = make_pair(0, 1);
    c = make_pair(0, 2);

    tuple<IntPair, IntPair, IntPair> TriArgs (a,b,c);
    print(cout, TriArgs);

    a = make_pair(0, 0);
    b = make_pair(0, 0);
    c = make_pair(0, 0);
    d = make_pair(0, 0);
    tuple<IntPair, IntPair, IntPair, IntPair> RecArgs (a,b,c,d);
    print(cout, RecArgs);
}
