#include "Shape.h"
using namespace std;


int main()
{
    typedef pair<int, int> IntPair;
    typedef pair<double, double> DoublePair;
    IntPair a, b, c, d;

    a = make_pair(4, 9);
    b = make_pair(-2, 4);
    c = make_pair(-1, -2);

    tuple<IntPair, IntPair, IntPair> TriArgs (a,b,c);
    print(cout, TriArgs);

    a = make_pair(0, -2);
    b = make_pair(5, 3);
    c = make_pair(-7, 15);
    d = make_pair(-12, 10);
    tuple<IntPair, IntPair, IntPair, IntPair> RecArgs (a,b,c,d);
    print(cout, RecArgs);

    a = make_pair(-6, 10);
    b = make_pair(-5, 6);
    c = make_pair(-9, 5);
    d = make_pair(-10, 9);
    tuple<IntPair, IntPair, IntPair, IntPair> SqrArgs(a,b,c,d);
    print(cout, SqrArgs);

    DoublePair e, f, g, h;
    
    e = make_pair(4.25, 9.25);
    f = make_pair(-1.75, 4.25);
    g = make_pair(-0.75, -1.75);
    
    tuple<DoublePair, DoublePair, DoublePair> TriArgsDouble(e, f, g);
    print(cout, TriArgsDouble);

    e = make_pair(-0.5, -2.5);
    f = make_pair(4.5, 2.5);
    g = make_pair(-7.5, 14.5);
    h = make_pair(-12.5, 9.5);
    tuple<DoublePair, DoublePair, DoublePair, DoublePair> RecArgsDouble(e, f, g, h);
    print(cout, RecArgsDouble);

    e = make_pair(-5.5, 10.5);
    f = make_pair(-4.5, 6.5);
    g = make_pair(-8.5, 5.5);
    h = make_pair(-9.5, 9.5);
    tuple<DoublePair, DoublePair, DoublePair, DoublePair> SqrArgsDouble(e, f, g, h);
    print(cout, SqrArgsDouble);

}
