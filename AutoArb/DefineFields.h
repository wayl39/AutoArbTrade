#ifndef DEFINEFIELDS_H
#define DEFINEFIELDS_H
#include <QString>

class noncopyable{
protected:
    noncopyable(){}
private:
    noncopyable(const noncopyable&);
    noncopyable& operator=(const noncopyable&);
};

class DefineFields : public noncopyable
{
public:
    static const QString UserId; // = "USER_ID";
    static const QString PassWord; // = "PASSWORD";
    static const QString Mac; // = "MAC";
    static const QString FundListStr; // = "USER_ID_LIST";
};

#endif // DEFINEFIELDS_H
