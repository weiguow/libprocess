//
// Created by weiguow on 18-11-2.
//
#include <iostream>

#include <stout/try.hpp>
#include <stout/os/mkdir.hpp>
#include <process/subprocess.hpp>

using process::Subprocess;
using process::subprocess;

using std::cout;
using std::endl;

int main() {
    Try<Subprocess> t = subprocess("su -");
//    Try<Subprocess> t = subprocess(
//            "sudo -S",
//            Subprocess::FD(STDIN_FILENO),
//            Subprocess::PIPE(),
//            Subprocess::FD(STDERR_FILENO));
    Try<Nothing> res = os::mkdir(path::join("/sys/fs/cgroup/cpu/", "cpu_test"));
    if (res.isError()) {
        cout << "error occured when mkdir." << endl;
        cout << res.error() << endl;
    } else {
        Try<Subprocess> limit_cpu = subprocess("echo 100000 > /sys/fs/cgroup/cpu/cpu_test/cpu.cfs_period_us");
        limit_cpu = subprocess("echo 10000 > /sys/fs/cgroup/cpu/cpu_test/cpu.cfs_quota_us");
        limit_cpu = subprocess("gcc ./cputime.c -o cputime");
        limit_cpu = subprocess("time ./cputime");
        sleep(4);
        limit_cpu = subprocess("time cgexec -g cpu:cpu_test ./cputime");
        sleep(20);
    }
    return 0;

}
