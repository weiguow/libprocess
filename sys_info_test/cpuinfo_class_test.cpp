//
// Created by weiguow on 18-11-26.
//
#include <unistd.h> // For getpid, getppid.

#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <set>
#include <string>
#include <thread>

#include <gmock/gmock.h>

#include <stout/abort.hpp>
#include <stout/gtest.hpp>
#include <stout/numify.hpp>
#include <stout/os.hpp>
#include <stout/proc.hpp>
#include <stout/synchronized.hpp>

#include <stout/try.hpp>

#include <cpu_info_class.hpp>

using std::set;
using std::string;
using std::list;

int main() {
    cpu_collector *cpus;

//    vector<SingleCpuInfo> cpu11 = cpus->get_cpu_info();
//
//    for (auto i = cpu11.begin(); i != cpu11.end(); i++) {
//        cout << i->cpuid() << i->coreid() << i->physicalid() <<
//             i->cpucores() <<
//             i->modelname() <<
//             i->cpumhz() <<
//             i->l1dcache() <<
//             i->l1icache() <<
//             i->l2cache() <<
//             i->l3cache() << endl;
//        }


}
