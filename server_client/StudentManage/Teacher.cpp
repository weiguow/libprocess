//
// Created by weiguow on 18-10-17.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

#include <Teacher.h>
#include <Chinese.h>

using std::cout;
using std::endl;
using std::vector;


/*
 * 类名：Teacher
 * 作用：带参构造函数
 * */
Teacher::Teacher(shared_ptr<string> name, unsigned int id,int age,vector<string> subjects)
    :Chinese(name,id,age),m_subjects(subjects){
    cout<<"Teacher construct" <<endl;
    int count = m_subjects.size();
    for(int i=0;i<count;i++){
        cout << m_subjects[i] << endl;
    }
}

/*
 * 作者：weiguow
 * 作用：拷贝构造函数
 * */
Teacher::Teacher(const Teacher &teacher):Chinese(teacher) {}

/*
 * 作者：weiguow
 * 作用：类的移动构造函数
 * */
Teacher::Teacher(Teacher &&teacher):Chinese(teacher),m_subjects(teacher.m_subjects){}

void Teacher::set_career(const shared_ptr<string> career) {
    mp_career = career;
}

shared_ptr<string> Teacher::get_career(){
    return mp_career;
}

Teacher::~Teacher(){
    cout<<"Teacher destruct" <<endl;
}

