/*
 * 作者：weiguow
 * 时间：2018-10-17
 * 单位：中国科学院深圳先进技术研究院数字所异构智能中心
 * */

#ifndef STUDENTSMANAGE_CHINESE_H
#define STUDENTSMANAGE_CHINESE_H

#include <iostream>
#include <iomanip>
#include <memory>

using std::cout;
using std::endl;
using std::setw;
using std::ostream;
using std::string;
using std::shared_ptr;

/*
 * 类名：Chinese
 * */
class Chinese {

protected:
    shared_ptr<string> mp_career;
    shared_ptr<string> mp_name;
    unsigned int m_id;

private:
    int m_age;


public:
    //构造函数
    Chinese() = delete;

    //利用类的初始化列表,声明为explicit的构造函数不能在隐式转换中使用
    explicit Chinese(shared_ptr<string> name, unsigned int id, int age);

    //拷贝构造函数
    Chinese(const Chinese &Chinese);

    //赋值运算符构造函数
    Chinese& operator=(const Chinese &Chinese);

    //移动构造函数
    Chinese(Chinese &&Chinese);

    //get,set方法
    shared_ptr<string> get_name();

    void set_name(const shared_ptr<string> name);

    unsigned int get_id();

    void set_id(unsigned int id);

    int get_age();

    void set_age(int age);

    friend ostream &operator<<(ostream &output,const Chinese &c) {
        output << "ID:" << c.m_id << ";Name:" << *c.mp_name << ";;age:" << c.m_age << endl;
        return output;
    };

    //自定义析构函数

    //虚函数
    virtual void set_career(const shared_ptr<string> career) ;

//    virtual ~Chinese();
};

#endif //STUDENTSMANAGE_CHINESE_H
