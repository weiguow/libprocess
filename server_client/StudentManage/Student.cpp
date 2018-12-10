/*
 * 版权所有：中国科学院深圳先进技术研究院
 * 作者：weiguow
 * 编写日期：2018-10-18
 * */

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <Student.h>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;

Student::Student(shared_ptr<string> name, unsigned int id, int age) : Chinese(name, id, age) {

}

Student::Student(shared_ptr<string> name, unsigned int id, int age, vector<string> compulsory_subjects,
                 vector<string> elective_subjects) : Chinese(name, id, age),
                                                     m_compulsory_subjects(compulsory_subjects),
                                                     m_elective_subjects(elective_subjects) {

}

Student::Student(const Student &s) : Chinese(s) {
    m_compulsory_subjects = s.m_compulsory_subjects;
    m_elective_subjects = s.m_compulsory_subjects;
}

Student::~Student() {
    m_compulsory_subjects.clear();
    m_elective_subjects.clear();
}

void Student::set_career(shared_ptr<string> career) {
    mp_career = career;
}

void Teacher::set_head(shared_ptr<string> name) {
    mp_name = name;
}

shared_ptr<string> Student::get_career() {
    return mp_career;
}

const shared_ptr<Teacher> &Student::getHead() const {
    return head;
}

void Student::setHead(const shared_ptr<Teacher> &head) {
    Student::head = head;
}





