// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair


using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}


int evalh(int i) {
    // cout << "eval helper" << endl;
    // cout << i << endl;
    int temp_cycle = 1;
    while (i != 1)
    {
    	// cout << "Temp Cycle: " << temp_cycle << endl;
	// cout << "i: " << i << endl;
        if (i%2 == 0)       // even
            i = i/2;
        else                // odd
            i = 3*i + 1;
        temp_cycle++;
    }
    // cout << "Temp Cycle: " << temp_cycle << endl;
    // cout << "i: " << i << endl;

    // cout << "exit eval helper" << endl;
    return temp_cycle;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    if (j < i)
    {
    	int temp = i;
    	i = j;
    	j = temp;
    }

    assert(i > 0);
    assert(j < 113383);

    if (i == j)
        return evalh(i);

    int max_cycle = 1;
    for (int x = i; x <= j; x++)
    {
        int temp_cycle = evalh(x);

    	if (temp_cycle > max_cycle)
    		max_cycle = temp_cycle;
    }
    assert(max_cycle >= 1);
    return max_cycle;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout

// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}

/*
% g++-4.7 -pedantic -std=c++11 -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz



% cat RunCollatz.in
1 10
100 200
201 210
900 1000



% RunCollatz < RunCollatz.in > RunCollatz.out



% cat RunCollatz.out
1 10 1
100 200 1
201 210 1
900 1000 1



% doxygen -g
// That creates the file Doxyfile.
// Make the following edits to Doxyfile.
// EXTRACT_ALL            = YES
// EXTRACT_PRIVATE        = YES
// EXTRACT_STATIC         = YES
// GENERATE_LATEX         = NO



% doxygen Doxyfile
// That creates the directory html/.
*/