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


TEST(ProcTest, Cpuinfo) {
    cpu_collector *cpus;
    list<cpu_collector> cpu_test = cpus->get_cpu_info();
    ASSERT_SOME_TRUE(cpu_test);
    EXPECT_LE(1u, cpus->get_cpu_info().size());
}

int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}