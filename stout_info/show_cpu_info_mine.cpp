//
// Created by weiguow on 18-11-19.
//
#include <iostream>
#include <list>
#include <set>
#include <hwloc.h>
#include <string.h>
#include <stdio.h>

#include <process/subprocess.hpp>
#include "cpu_info.hpp"

using std::cout;
using std::endl;
using std::set;
using std::list;
using std::string;

using weiguo_proc::CPU;

using process::Subprocess;
using process::subprocess;


int main() {
    Try<list<CPU>> cpus = weiguo_proc::cpus();
    for(auto i = cpus.get().begin(); i!= cpus.get().end();i++){
//        auto m = cpus.get().front();
//        cout << m.modelname << endl;
//          cout << *i << endl;
          cout << *i << endl;
    }


//    for (auto i = cpus.get().begin(); i != cpus.get().end(); i++) {
//        cout << *i << endl;
//    }
}

