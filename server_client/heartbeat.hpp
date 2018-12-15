#include <iostream>

#include <stout/os.hpp>

#ifndef __WINDOWS__
#include <stout/os/fork.hpp>
#endif // __WINDOWS__
#include <stout/os/pstree.hpp>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>
#include <process/delay.hpp>

#include <slaveinfo_pro.pb.h>

using namespace process;

using namespace process::http;

#ifndef __WINDOWS__
using os::Exec;
using os::Fork;
#endif // __WINDOWS__
using os::Process;
using os::ProcessTree;

using std::cerr;
using std::cout;
using std::endl;
using std::chrono::seconds;
using std::string;

constexpr Duration DEFAULT_HEARTBEAT_INTERVAL = Seconds(5);

class MyHeartbeater : public process::Process<MyHeartbeater> {

public:

    UPID server;
//    MyHeartbeater(const Duration& interval):process::ProcessBase(process::ID::generate("myheartbeater")), m_interval(interval) {
//    }
//
//    virtual void initialize() {
//        heartbeat();
//    }

private:

//    void heartbeat(){
//        SlaveInfo si;
//        auto ip = process::address().ip;
//        auto port = process::address().port;
//        si.set_ip("ip");
//        si.set_port("port");
//
//        send(server,si);
//        process::delay(m_interval,self(),&Self::heartbeat);
//    }

    const Duration m_interval;


};
