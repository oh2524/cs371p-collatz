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


int *cache;
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

/*
 * helper method for collatz_eval
 * Takes an int and returns its cycle length
 * if input int x is in cache, return the cached value
 * else processes its cycle length and stores it in the cache[x]
 */
int evalh(int x) {
    // cout << "eval helper" << endl;
    // cout << i << endl;
    if (cache[x] != 0)	// checks if value is cached
    	return cache[x];
    unsigned int i = x;	// converts to unsigned in case of overflow
    int temp_cycle = 1;
    while (i != 1)	// (3n+1)/2 loop 
    {
	if (i%2 == 0)
		i = i/2;
	else 
		i = 3*i + 1;
	temp_cycle++;
    }

    cache[x] = temp_cycle;	// caches new value
    return temp_cycle;
}

// ------------
// collatz_eval
// ------------

/*
 * evaluates the max cycle length between ints i and j
 * initializes cache, and deallocate it before function exits
 * checks for reverse ranges
 * cycle length returned will always be >= 1
 */
int collatz_eval (int i, int j) {
    cache = new int[4194304];
    if (j < i)
    {
    	int temp = i;
    	i = j;
    	j = temp;
    }

    if (i == j)
        return evalh(i);

    int max_cycle = 1;
    int start = (j/2 + 1 > i) ? (j/2 + 1) : i;
    
    for (int x = start; x <= j; x++)
    {
    	int temp_cycle = evalh(x);
    	if (temp_cycle > max_cycle)
    		max_cycle = temp_cycle;
    }

    assert(max_cycle >= 1);
    delete []cache;
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
        collatz_print(w, i, j, v);}
}
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
