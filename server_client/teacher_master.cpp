//
// Created by weiguow on 18-10-31.
//
#include <iostream>
#include <list>
#include <string>

#include <sstream>   //文件的输入与输出
#include <fstream>

#include <memory>
#include <map>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>
#include <process/subprocess.hpp>

#include <stout/os.hpp>

#include <stout/duration.hpp>
#include <stout/flags.hpp>
#include <stout/foreach.hpp>
#include <stout/gtest.hpp>
#include <stout/json.hpp>
#include <stout/none.hpp>
#include <stout/nothing.hpp>
#include <stout/option.hpp>
#include <stout/path.hpp>
#include <stout/some.hpp>
#include <stout/utils.hpp>
#include <stout/os/write.hpp>
#include <stout/tests/utils.hpp>

#include <student_pro.pb.h>
#include <transfile.pb.h>
#include <cpuinfo_pro.pb.h>
#include <singleinfo_pro.pb.h>
#include <slaveinfo_pro.pb.h>\

#include <flags.h>
//#include <cpu_info_struct.hpp>
#include <cpu_info_class.hpp>

using namespace process;
using namespace process::http;

using os::Process;
using os::ProcessTree;
using os::Exec;
using os::Fork;
using process::subprocess;

using std::cerr;
using std::cout;
using std::endl;
using std::map;
using std::list;
using std::string;
using std::vector;
using std::shared_ptr;
using std::chrono::seconds;

using std::ifstream;
using std::ios_base;
using std::fstream;

using process::Future;
using process::Promise;
using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;

using flags::Flag;
using flags::FlagsBase;
using flags::Warnings;

using utils::arraySize;

//using weiguo_proc::CPU;

class Teacher_Master : public ProtobufProcess<Teacher_Master> {

public:
    Teacher_Master() : ProcessBase("Teacher_master") {
    }

    UPID client;

    virtual void initialize() {
        //返回教师信息
        route(
                "/find",
                "Adds the two query arguments",
                [](Request request) {
                    int a = 3;
                    int b = 4;
                    std::ostringstream result;
                    result << "{ \"result\": " << a + b << "}";
                    JSON::Value body = JSON::parse(result.str()).get();
                    return OK(body);
                });

        route(
                "/add",
                "Adds the two query arguments",
                [](Request request) {
                    string request_method = request.method;
                    cout << request_method << endl;

                    string &tpath = request.url.path;
                    cout << tpath << endl;

                    int param_size = request.url.query.size();
                    cout << param_size << endl;

//                    map<int,Employee> mapEmployee;

                    for (string key:request.url.query.keys()) {
                        cout << "key:" << key << endl;
                        cout << "value:" << request.url.query[key] << endl;
                    }

                    int a = 3;
                    int b = 4;
                    std::ostringstream result;
                    result << "{ \"result\": " << a + b << "}";
                    JSON::Value body = JSON::parse(result.str()).get();
                    return OK(body);
                });

        //route只有request
        route(
                "/addd",
                "Adds the two query arguments",
                [](Request request) {
                    int a = 3;
                    int b = 4;
                    std::ostringstream result;
                    result << "{ \"result\": " << a + b << "}";
                    JSON::Value body = JSON::parse(result.str()).get();
                    return OK(body);
                });

        install("stop", [=](const UPID &from, const string &body) {
            terminate(self());
        });

        //想要监听什么消息就在本身定义一个含有想要监听到的参数的方法，方法名是自己来定义的
        install<Student_pro>(&Teacher_Master::report_from_client, &Student_pro::name);

        install<Transfile>(&Teacher_Master::report_from_client_python_file, &Transfile::key, &Transfile::value);

//        install<SingleInfo>(&Teacher_Master::report_all_cpuinfo_to_client,&SingleInfo::address);

        install<AllCpuInfo>(&Teacher_Master::report_all_cpuinfo_to_client_2,&AllCpuInfo::key_cpu);

//        install<SingleCpuInfo>(&Teacher_Master::get_client_cpu_request, &SingleCpuInfo::cpu);   //test for single cpu information
    }

/*****************1.report student message to client*************************/
    void report_from_client(const string &name) {
        cout << "你的学生是" << endl;
        cout << name << endl;
    }
/****************************************************************************/



/*****************2.report cpu information***************************************/
//    void get_client_cpu_request(const string &address){
//
//        SingleCpuInfo sci;
//        UPID clientUPID(address);
//        Try<list<CPU>> cpus = weiguo_proc::cpus();
//        auto cpuinfo = cpus.get().front();
//
//        string cpuID = cpuinfo.cpuID;
//        string coreID = cpuinfo.coreID;
//
//        sci.set_cpu("1");
//        sci.set_cpuid(cpuID);
//        sci.set_coreid(coreID);
//
//        send(clientUPID,sci);
//    }

//    void report_all_cpuinfo_to_client(const string &address){
//
//        cout << address << endl;
//        int j = 0;
//        SingleInfo as;
//
//        UPID clientUPID(address);
//        Try<list<CPU>> cpus = weiguo_proc::cpus();
//        for(auto i = cpus.get().begin();i!=cpus.get().end();i++){
//            as.set_cpuid(i->cpuID);
//            as.set_coreid(i->coreID);
//            as.set_physicalid(i->physicalID);
//            as.set_cpucores(i->cpucores);
//            as.set_modelname(i->modelname);
//            as.set_cpumhz(i->cpuMHz);
//            as.set_l1dcache(i->L1dcache);
//            as.set_l1icache(i->L1icache);
//            as.set_l2cache(i->L2cache);
//            as.set_l3cache(i->L3cache);
//            send(clientUPID,as);
//            as.Clear();
//        }
//    }

    void report_all_cpuinfo_to_client_2(const string &address){
        AllCpuInfo ac;
        UPID clientUPID(address);
//        Try<list<CPU>> cpus = weiguo_proc::cpus();

        cpu_collector *cpus;
        list<cpu_collector> cpu_info = cpus->get_cpu_info();
        for(auto i= cpu_info.begin();i!=cpu_info.end();i++){
            ac.add_sci()->set_cpuid(i->getCpuID());
            ac.add_sci()->set_coreid(i->getCoreID());
            ac.add_sci()->set_physicalid(i->getPhysicalID());
            ac.add_sci()->set_cpucores(i->getCpucores());
            ac.add_sci()->set_modelname(i->getModelname());
            ac.add_sci()->set_cpumhz(i->getCpuMHz());
            ac.add_sci()->set_l1dcache(i->getL1dcache());
            ac.add_sci()->set_l1icache(i->getL1icache());
            ac.add_sci()->set_l2cache(i->getL2cache());
            ac.add_sci()->set_l3cache(i->getL3cache());
        }

        send(clientUPID,ac);
    }

/*********************************************************************************/



/*******************************3.send a file ***********************************/
    void report_from_client_python_file(const string &key, const string &value) {
        cout << "entering into report" << endl;
        StringImage(value, "./hello.py");
        Try<ProcessTree> res = Fork(None(), Exec("python ./hello.py"))();

        //接收到文件的同时返回信息给client
        UPID clientUPID(key);
        Transfile messa;

        //传递的消息体要保持完整？Yes,否则会出现missing required fields 的问题 ？？ 是否把字段换成option就不会出现这种问题？？
        messa.set_key("weiguow");
        messa.set_value("server_value");
        send(clientUPID, messa);
    }

    void StringImage(string binFile, const char *outImage) {
        fstream imgFile(outImage, std::ios::binary | std::ios::out);
        for (int i = 0; i < binFile.length(); ++i) {
            imgFile << binFile[i];
        }
        imgFile.close();
    }
/*********************************************************************************/




/******************************4.dispatch*********************************************/

    void dispatch1() {
        process::dispatch(self(), &Teacher_Master::dispatch2);
        process::dispatch(self(), &Teacher_Master::dispatch3, "dispatch1");
    }

    void dispatch2() {
        cout << "dispatch2" << endl;
    }

    void dispatch3(string recv_str) {
        cout << "dispatch3" << endl;
        process::dispatch(self(), &Teacher_Master::dispatch1);
    }

    void dispatch4() {
        Student_pro stu;
        stu.set_name("weiguow");
        stu.set_age(23);
        process::dispatch(self(), &Teacher_Master::dispatch5, stu);

    }

    void dispatch5(Student_pro stu) {
        cout << stu.name() << endl;
        cout << stu.age() << endl;
        process::dispatch(self(), &Teacher_Master::dispatch4);
    }
/********************************************************************************/


/*****************************5.test flags***************************************/
    void TestFlags() {
        TestFlagsBase flags;
        const char *argv[] = {
                "/path/to/program",
                "--name = weiguow",
                "--age = 43",
                "--id = 3"
        };
        Try<flags::Warnings> load = flags.load("FLAGTEST_", arraySize(argv), argv);
//        const map<string, Option<string>> values = {
//                {"name",Some("weiguow")},
//                {"age",Some("23")},
//                {"id",Some("1")},
//        };
//        flags.load(values);

//        cout << load->warnings.size() << endl;
        cout << flags.name << endl;
        cout << flags.age << endl;
        cout << flags.id << endl;
        cout << flags.usage() << endl;
    }
/*********************************************************************************/


/*********************************************************************************/


/*********************************************************************************/
};

int main() {
    //Bind ip and port
//    net::IP ip = process::address().ip;
//    os::setenv("LIBPROCESS_IP", strings::trim("172.20.110.81"));

    os::setenv("LIBPROCESS_PORT", stringify(2573));

    process::initialize("master");  //初始化一个名为master的进程
    Teacher_Master master;  //创建类Master的对象master
    PID<Teacher_Master> cur_master = process::spawn(master);  //启动master


    //dispatch的循环调度
//    master.dispatch1();
//    master.dispatch4();

//flags测试
//    master.TestFlags();



    cout << "Running server on " << process::address().ip << ":" << process::address().port << endl;
    const PID<Teacher_Master> masterPid = master.self();

    cout << masterPid << endl;

    process::wait(master.self());
    return 0;
}
