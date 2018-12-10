//
// Created by weiguow on 18-10-17.
//

#ifndef STUDENTSMANAGE_TEACHER_H
#define STUDENTSMANAGE_TEACHER_H

#include <iostream>
#include <vector>
#include <string>


#include <Chinese.h>


using std::vector;
using std::string;
using std::shared_ptr;
using std::function;

typedef function <void(string &,string &)> Fun;

class Teacher : public Chinese {
private:
    vector<string> m_subjects;


public:
    explicit Teacher(shared_ptr<string> name, unsigned int id, int age, vector<string> subjects);

    //拷贝构造函数
    Teacher(const Teacher &teacher);

    //赋值运算符构造函数
    Teacher&operator=(const Chinese &Chinese);

    //移动构造函数
    Teacher(Teacher &&Teacher);

    void set_career(const shared_ptr<string> career) override;

    shared_ptr<string> get_career();

    //虚析构函数
    virtual ~Teacher();

    void set_head(shared_ptr<string> name);

    shared_ptr<string> get_head();
    /*
     *
     */
    /*
     * */
    void call(string a,Fun f){
        string name = *this->mp_name;
        f(a,name);
    }

};

#endif //STUDENTSMANAGE_TEACHER_H
