//
// Created by weiguow on 18-11-12.
//
#include <iostream>
#include <string>

#include <stout/try.hpp>
#include <stout/path.hpp>
#include <stout/uuid.hpp>

#include <stout/os/mkdir.hpp>
#include <stout/os/getcwd.hpp>

#include <process/subprocess.hpp>

using process::Subprocess;
using process::subprocess;

using net::IPNetwork;
using net::links;

using std::string;
using std::list;

using std::cout;
using std::endl;
using std::set;

int main() {
    Try<set<string>> links = net::links();

    //输出所有的网卡信息
    for (auto iter = links.get().begin(); iter != links.get().end(); iter++) {
        cout << *iter << endl;
    }

    auto network_card = links.get().begin();

    //输出变量类型
    //cout << typeid(network_card).name() << endl;
    cout << *network_card << endl;

    //home/weiguow/project/libprocess_mine/cmake-build-debug/resouce_limit
    const string filedir = os::getcwd();

    //输出当前目录下的所有文件
    Try<list<string>> entries = os::ls(filedir);
    for(auto i = entries.get().begin();i != entries.get().end();i++){
        cout << *i << endl;
    }

    auto  testdir = path::join(os::getcwd(), UUID::random().toString());
    cout << testdir << endl;

    Try<Subprocess> t = subprocess("su -");
    Try<Nothing> res = os::mkdir(path::join("/sys/fs/cgroup/net_cls", "test"));
    if (res.isError()) {
        cout << "Can not mkdir" << endl;
        cout << res.error() << endl;
    } else {
        //创建队列规则
        string tc_qdisc = "tc qdisc add dev " + stringify(*network_card) + " root handle 1: htb default 100";
        cout << tc_qdisc << endl;
        Try<Subprocess> limit_net = subprocess(tc_qdisc);

        //在根下创建一个限制带宽为10mbit的类
        string tc_class = "tc class add dev " + stringify(*network_card) + " parent 1: classid 1:1 htb rate 10mbit";
        cout << tc_class << endl;
        limit_net = subprocess(tc_class);

        //将cgroup添加到队列规则的控制中
        string tc_filter = "tc filter add dev " + stringify(*network_card) + " parent 1: protocol ip prio 10 handle 1:1 cgroup";
        cout << tc_filter << endl;
        limit_net = subprocess(tc_filter);
        string net_cls = "echo " + stringify(0x00010001) + " > /sys/fs/cgroup/net_cls/test/net_cls.classid";
        cout << net_cls << endl;
        limit_net = subprocess(net_cls);

        //生成一个5G的空文件
        limit_net = subprocess("sudo dd if=/dev/zero of=/home/weiguow/file bs=1G count=5");

        //使用scp命令传输文件到远程服务端
        //limit_net = subprocess("cgexec -g net_cls:test scp -r /home/weiguo/file lemaker@172.16.101.246:/home/lemaker/weiguow");

    }
    return 0;

}