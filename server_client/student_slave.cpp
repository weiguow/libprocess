//
// Created by weiguow on 18-10-31.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>

#include <student_pro.pb.h>
#include <transfile.pb.h>
#include <cpuinfo_pro.pb.h>
#include <singleinfo_pro.pb.h>
#include <slaveinfo_pro.pb.h>

#include <heartbeat.hpp>

#ifndef __WINDOWS__
using os::Exec;
using os::Fork;
#endif // __WINDOWS__
using os::Process;
using os::ProcessTree;

using namespace process;
using namespace process::http;

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::chrono::seconds;
using std::ifstream;
using std::ios_base;
using std::vector;
using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;

//constexpr Duration DEFAULT_HEARTBEAT_INTERVAL = Seconds(5);

class Student_Client : public ProtobufProcess<Student_Client> {
public:

    Student_Client() : ProcessBase("Student_Client") {}

    Student_Client(const Duration& interval):process::ProcessBase(process::ID::generate("SlaveHeartBeat")),m_interval(interval){}

    UPID server;

    virtual void initialize() {
        install("stop", [=](const UPID &from, const string &body) {
            terminate(self());
        });

//        slaveheartbeat();

        /**
         * 函数名：install
         * 参数类型：<想要监听的message名字>
         * 注册的方法名字，以及该方法用到message参数
         * install引入的名字是定义的message中的名字,而不是message本身文件的名字
         * */
        install<Transfile>(&Student_Client::report_from_server, &Transfile::key);

        //获取cpu信息
        install<SingleCpuInfo>(&Student_Client::report_cpuinfo_from_server, &SingleCpuInfo::cpuid,
                               &SingleCpuInfo::coreid);

        //获取cpu信息
        install<SingleCpuInfo>(&Student_Client::report_cpuinfo_from_server_all, &SingleCpuInfo::cpuid,
                                       &SingleCpuInfo::coreid, &SingleCpuInfo::physicalid,
                                       &SingleCpuInfo::cpucores, &SingleCpuInfo::modelname,
                                       &SingleCpuInfo::cpumhz, &SingleCpuInfo::l1dcache);


        //获取cpu信息
        install<AllCpuInfo>(&Student_Client::report_cpuinfo_from_server_all_test, &AllCpuInfo::sci);

    }

//    void slaveheartbeat(){
//        SlaveInfo si;
//        si.set_ip("1");
//        si.set_port("2");
//        send(server,si);
//        process::delay(m_interval,self(),&Self::Student_Client);
//    }

    const Duration m_interval;
/************************************1.CPU information***************************************/

    /*
     * 1.send_request_cpuinfo:test for send message*/
    void send_request_cpuinfo() {
        SingleInfo si;
        string client_id = this->self();

        si.set_cpu(client_id);
        si.set_cpuid("1");
        si.set_coreid("2");

        send(server, si);
    }

    /**
     * 2.to get all cpu information from master
     * */
    void send_request_cpuinfo_all() {
        SingleCpuInfo sci;
        string client_id = this->self();

        //although we just send the address,but we need to fix all the message
        sci.set_address(client_id);
        send(server, sci);
    }

    /**
     * 3.get information from server
     * */
    void report_cpuinfo_from_server(const string &cpuid, const string &coreid) {
        cout << "cpuID:" << coreid << " coreID:" << coreid << endl;
    }

    /**
     * 4.get all information from server
     * */
    void report_cpuinfo_from_server_all(const string &cpuid, const string &coreid, const string &physicalid,
                                        const string &cpucores, const string &modelname, const string &cpumhz,
                                        const string &l1dcache) {
        cout << "CPU information" << endl;
        cout << "cpuID:" << cpuid << "   coreID:" << coreid << "   Physical ID:" << physicalid
             << "   cpu cores:" << cpucores << "   model name:" << modelname << "   cpu MHz:"
             << cpumhz << "   L1d cache:" << l1dcache << endl;
    }

    /**
     * 5.send for all information
     * */
    void send_server_a_key_cpu() {
        AllCpuInfo ac;
        string client_ID = this->self();
        ac.set_key_cpu(client_ID);
        send(server, ac);
    }

    /**
    * 6.for get all information
     * take 40 messages
     * */
    void report_cpuinfo_from_server_all_test(vector<SingleCpuInfo> sci) {

        for (auto i = sci.begin(); i != sci.end(); i++) {

            cout << i->cpuid() << i->coreid() << i->physicalid() <<
                 i->cpucores() <<
                 i->modelname() <<
                 i->cpumhz() <<
                 i->l1dcache() <<
                 i->l1icache() <<
                 i->l2cache() <<
                 i->l3cache() << endl;
        }
    }

/***************************************************************************************/




/*****************************2.send student message************************************/
    void report_from_server(const string &key) {
        cout << "report from server" << endl;
        cout << key << endl;
    }

    void send_server_a_message() {
        cout << "学生信息是" << endl;

        //按照消息体的形式定义消息,自带set_name方法？？是的
        Student_pro s;
        s.set_name("weiguo");
        s.set_id(2);
        s.set_age(23);

        cout << "name:" << s.name() << " 学号：" << s.id() << " 年龄：" << s.age() << endl;
        send(server, s);
    }

    void send_server_a_file() {
        Transfile t;
        string client_id = this->self();
        string str_file = read_a_python_file();
        t.set_key(client_id);
        t.set_value(str_file);
        send(server, t);
    }
/*****************************************************************************/





/*******************************3.send a file ***********************************/
    //从服务端传输一个python文件到客户端
    /*ios::app：　　　以追加的方式打开文件
　　   ios::ate：　　　文件打开后定位到文件尾，ios:app就包含有此属性
　　   ios::binary：　以二进制方式打开文件，缺省的方式是文本方式。两种方式的区别见前文
　　   ios::in：　　　 文件以输入方式打开(文件数据输入到内存)
　　   ios::out：　　　文件以输出方式打开(内存数据输出到文件)
　　   ios::nocreate： 不建立文件，所以文件不存在时打开失败
　　   ios::noreplace：不覆盖文件，所以打开文件时如果文件存在失败
　　   ios::trunc：　　如果文件存在，把文件长度设为0
     */
    string read_a_python_file() {
        string str_f;
        ifstream myfile("/home/weiguow/hello.py", ios_base::in);
        if (myfile.fail()) {
            cout << "读取文件失败" << endl;
        } else {
            char ch;
            while (myfile.get(ch)) {
                str_f += ch;
            }
            if (myfile.eof()) {
                cout << "文件已经全部读取完成" << endl;
                cout << "文件内容为:" << str_f << endl;
                myfile.close();
            }
        }
        return str_f;
    }
/*********************************************************************/

};

int main() {
    process::initialize("slave");  //只有初始化才会开始监听消息体
    Student_Client client;
    PID<Student_Client> cur_client = process::spawn(client);

    cout << "Running client on " << process::address().ip << ":" << process::address().port << endl;  //显示ip地址和端口
    cout << "please input the master UPID:" << endl;

//    Option<process::Owned<MyHeartbeater>> heartbeater = new MyHeartbeater(DEFAULT_HEARTBEAT_INTERVAL);
//    process::spawn(heartbeater.get().get());

    //输入服务端的ip地址和端口号
    string master_str;  //
    std::cin >> master_str;

    //调用UPID构造方法,输入参数mater_str
    UPID masterUPID(master_str);
    client.server = masterUPID;  //声明client的服务器是masterUPID


    //向服务器发送消息请求
    client.send_server_a_message();  //client向server发送消息
    client.send_server_a_file();  //传输python文件
//    client.send_request_cpuinfo_all();
    client.send_server_a_key_cpu();

//    client.send_request_cpuinfo();  //请求cpu中某个信息,测试用
//    client.read_a_python_file();
    process::wait(client.self());
//    process::wait(heartbeater.get().get());

    return 0;
}


