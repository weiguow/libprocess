//
// Created by weiguow on 18-12-11.
//

#ifndef LIBPROCESS_START_ERROR_H
#define LIBPROCESS_START_ERROR_H

#include <string>
using namespace std;
bool isInteger(const string &str);
bool isFloat(const string &str);
string convertToString(const double x);
long long convertToInteger(const string& str);
double convertToDouble(const string & str);
#endif // MYCCTYPE_H


//mycctype.cpp
#include "mycctype.h"
#include <string>
#include <sstream>
using namespace std;
bool isInteger(const string &str)
{
    for(string::size_type i = 0 ; i != str.length(); ++i)
    {
        if(str[i] <= '0' || str[i] >= '9')
        {
            return false;
        }

    }
    return true;
}

bool isFloat(const string &str)
{
    int numOfDot = 0;
    for(string::size_type i = 0; i != str.length(); ++i)
    {

        if(str[i] >= '0' && str[i] <= '9')
            continue;
        else if (str[i] == '.')
        {
            numOfDot++;
            if (numOfDot > 1)
            {
                return false;
            }
        }
        else
            return false;
    }
    return true;
}
string convertToString(const double x)
{
    ostringstream o;
    if(o << x)
        return o.str();
    return "conversion error.";
}
long long convertToInteger(const string & str)
{

    istringstream i(str);
    double x;
    if(i >> x)
        return x;
    return 0;

}
double convertToDouble(const string &str)
{
    istringstream i(str);
    double x;
    if(i >> x)
        return x;
    return 0.0;
}

#endif //LIBPROCESS_START_ERROR_H
