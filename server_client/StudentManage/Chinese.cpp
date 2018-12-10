//
// Created by weiguow on 18-10-17.
//
#include <iostream>
#include <cstdio>
#include <cstring>

//引入头文件
#include <Chinese.h>

using std::cout;
using std::cin;
using std::endl;
using std::make_shared;

/*
 * 类名：Chinese
 * 作者：weiguow
 * 作用：带参构造函数
 * */
Chinese::Chinese(shared_ptr<string> name, unsigned int id, int age) :m_id(id), m_age(age) {  //初始化列表
    mp_career = nullptr;
    mp_name = name;
}

/*
 * 作者;weiguow
 * 作用：拷贝构造函数
 * */
Chinese::Chinese(const Chinese &chinese){
    this->m_id=chinese.m_id;
    this->m_age=chinese.m_age;
    mp_name = chinese.mp_name;
}

/*
 * 作者：weiguow
 * 作用：赋值构造函数
 * */
Chinese& Chinese::operator=(const Chinese& chinese) {
    this->m_id=m_id;
    this->m_age=m_age;
    mp_name = chinese.mp_name;
}

/*
 * 作者:weiguow
 * 作用：移动构造函数
 * */
Chinese::Chinese(Chinese &&chinese):mp_name(chinese.mp_name),m_id(chinese.m_id),m_age(chinese.m_age) {
    this->m_id=m_id;
    this->m_age=m_age;
    mp_name = chinese.mp_name;
}

shared_ptr<string> Chinese::get_name() {
    return mp_name;
}

void Chinese::set_name(const shared_ptr<string> name) {
    mp_name = name;
}

unsigned int Chinese::get_id() {
    return m_id;
}


void Chinese::set_id(unsigned int id) {
    this->m_id = id;
}

int Chinese::get_age() {
    return m_age;
}

void Chinese::set_age(int age) {
    this->m_age = age;
}
void Chinese::set_career(const shared_ptr<string> career) {
    mp_career = nullptr;
}

//Chinese::~Chinese() {
//    cout << "Destruct Chinese"<<endl;
//    delete mp_name;
//    delete mp_career;
//}






