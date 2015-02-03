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

#include "Collatz.h"

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

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    if(j < i)
    {
	int temp = i;
	i = j;
	j = temp;
    }
    assert(i > 0);
    assert(j < 1000000);
    assert(i != j);

    int max_cycle = 1;
    for (int x = i; x <= j; x++)
    {
    	int temp_cycle = 1;
	while (x != 1)
	{
		if (x%2 == 0)		// even
			x = x/2;
		else			// odd
			x = 3*x + 1;
		temp_cycle++;
	}

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
