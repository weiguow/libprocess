//
// Created by weiguow on 18-11-19.
//
#include <iostream>
#include <list>
#include <set>

#include <stout/proc.hpp>

using std::cout;
using std::endl;
using std::set;
using std::list;

using proc::CPU;

int main() {
    Try<list<CPU>> cpus = proc::cpus();
    for (auto i = cpus.get().begin(); i != cpus.get().end(); i++) {
        cout << *i << endl;
    }
}

