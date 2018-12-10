//
// Created by weiguow on 18-11-11.
//
#include <iostream>

#include <stout/try.hpp>
#include <stout/os/mkdir.hpp>

#include <process/subprocess.hpp>

using process::Subprocess;
using process::subprocess;

using std::cout;
using std::endl;

int main(){
    Try<Subprocess> t = subprocess("su -");
    Try<Nothing> res = os::mkdir(path::join("/sys/fs/cgroup/blkio","foo"));
    if(res.isError()){
        cout << "Can not mkdir" << endl;
        cout << res.error() << endl;
    } else {
        Try<Subprocess> limit_blkio = subprocess("dd if=/dev/zero of=/tmp/file_1 bs=1G count=10");
        sleep(20);
        limit_blkio = subprocess("echo 100 >/sys/fs/cgroup/blkio/foo/blkio.weight ");
        limit_blkio = subprocess("sync");
        limit_blkio = subprocess("echo 3 > /proc/sys/vm/drop_caches");
        limit_blkio = subprocess("cgexec -g blkio:foo dd if=/tmp/file_1 of=/dev/null");
        sleep(20);
    }
    return 0;
}

