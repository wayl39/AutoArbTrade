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
    static const QString funcType; // = "FUNC_TYPE";
    static const QString UserId; // = "USER_ID";
    static const QString PassWord; // = "PASSWORD";
    static const QString Mac; // = "MAC";
    static const QString FundListStr; // = "USER_ID_LIST";
    static const QString FundAccount; // = "fund_account";
    static const QString Admin_Account; //= "Admin_Account";
    static const QString Admin_Password; // = "Admin_Password";
    static const QString Ip; // = "ip";
    static const QString Port; // = "port";
    static const QString Admin; // = "Admin";
};

class FuncType : public noncopyable
{
public:
    static const QString Log; // = "Log";
    static const QString AddTrader; // = "addTrader";
    static const QString DeleteTrader; // = "deleteTrader";
    static const QString AddFundAccount; // = "addFundAccount";
    static const QString DeleteFundAccount; // = "deleteFundAccount";
    static const QString ModifiTraderMsg; // = "modifiTraderMsg";
};

class MasterFileds : public noncopyable
{
public:
    static const QString ret; // = "10008";
    static const QString textDescribe; // = "58";

//    static const QString DeleteTrader; // = "deleteTrader";
//    static const QString AddFundAccount; // = "addFundAccount";
//    static const QString DeleteFundAccount; // = "deleteFundAccount";
//    static const QString ModifiTraderMsg; // = "modifiTraderMsg";
};

class MasterValues : public noncopyable
{
public:
    class ResponseResult : public noncopyable
    {
    public:
        static const QString success; // = "0";
        static const QString fail; // = "1";
        static const QString timeOut; // = "2";
    };

};

#endif // DEFINEFIELDS_H
