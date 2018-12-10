//
// Created by weiguow on 18-10-17.
//
#ifndef STUDENTSMANAGE_STUDENT_H
#define STUDENTSMANAGE_STUDENT_H

#include <iostream>
#include <vector>
#include <boost/bind.hpp>

#include <Chinese.h>
#include <Teacher.h>

using std::string;
using std::vector;
using std::function;

typedef function<void(string &,string &)> fun;


class Student : public Chinese {
private:
    shared_ptr<Teacher> head;

    vector<string> m_compulsory_subjects;

    vector<string> m_elective_subjects;

    void transfer_subjects();

public:
    explicit Student(shared_ptr<string> name, unsigned int id, int age);

    explicit Student(shared_ptr<string> name, unsigned int id, int age, vector<string> compulsory_subjects,
                     vector<string> elective_subjects);

    Student(const Student &s);

    shared_ptr<string> get_career();

    //虚函数重写
    void set_career(const shared_ptr<string> career) override;

//    void set_head(Teacher &t){
//        mp_name = t.mp_name;
//    }

    const shared_ptr<Teacher> &getHead() const;

    void setHead(const shared_ptr<Teacher> &head);

    virtual ~Student();

    void print_callback(string& s,string& t){
        cout<<s<<" is a student of teacher "<<t<<endl;
    }

    void print_student_and_head_relationship(){
        Fun fun=bind(&Student::print_callback,this,_1,_2);
        head->call(*this->get_name(),fun);
    }
};


#endif //STUDENTSMANAGE_STUDENT_H
