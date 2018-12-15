//
// Created by weiguow on 18-11-22.
//
#include <fstream>
#include <iostream>
#include <stout/strings.hpp>

#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){
    std::ifstream port("/proc/sys/net/ipv4/ip_local_port_range");

    string line;
    std::getline(port,line);

    vector<string> port_split = strings::split(line,"\t");

    for(auto i= port_split.begin();i!=port_split.end();i++){
        cout << *i << endl;
    }

}