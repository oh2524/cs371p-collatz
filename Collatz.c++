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
int* cache;
// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}


int evalh(int x) {
    // cout << "eval helper" << endl;
    // cout << i << endl;
    unsigned int i = x;
    int temp_cycle = 1;
    while (i != 1)
    {
    	// cout << "Temp Cycle: " << temp_cycle << endl;
	// cout << "i: " << i << endl;
	if (i%2 == 0)
		i = i/2;
	else 
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

    if (i == j)
        return evalh(i);

    int max_cycle = 1;
    int start = (j/2 + 1 > i) ? (j/2 + 1) : i;
    
    for (int x = start; x <= j; x++)
    {
    	if (cache[x] != 0)
		max_cycle = (cache[x] > max_cycle) ? cache[x] : max_cycle;
	else {
    		int temp_cycle = evalh(x);
		cache[x] = temp_cycle;
    		if (temp_cycle > max_cycle)
    			max_cycle = temp_cycle;
	}
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
    cache = new int[4194304];
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}
    delete[] cache;
}
