// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License

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

    MyHeartbeater(const Duration& interval):process::ProcessBase(process::ID::generate("myheartbeater")), m_interval(interval) {
    }

    virtual void initialize() {
        heartbeat();
//        install<Offer>(&Master::report_from_client, &Offer::key,&Offer::value);
    }

private:

    void heartbeat(){
        cout<<"5 seconds"<<endl;
        //  delays 5 seconds to invoke the function "heartbeat " of self.
        // it's cyclical because "heartbeat invoke heartbeat"
        process::delay(m_interval,self(),&Self::heartbeat);
    }

   const Duration m_interval;


};

int main() {

    Option<process::Owned<MyHeartbeater>> heartbeater = new MyHeartbeater(DEFAULT_HEARTBEAT_INTERVAL);
    process::spawn(heartbeater.get().get());

//    process::terminate(heartbeater.get().get());
    process::wait(heartbeater.get().get());

    return 0;
}