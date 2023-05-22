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
    static const QString Admin_MAC; // = "Admin_MAC";
    static const QString Ip; // = "ip";
    static const QString Port; // = "port";
    static const QString Path; // = "path";
    static const QString StrategyFilePath; // = "strategyFilePath";

};

class FuncType : public noncopyable
{
public:
    static const QString Settings; // = "Settings";
    static const QString Log; // = "Log";
    static const QString AddTrader; // = "addTrader";
    static const QString DeleteTrader; // = "deleteTrader";
    static const QString AddFundAccount; // = "addFundAccount";
    static const QString DeleteFundAccount; // = "deleteFundAccount";
    static const QString ReadTraderMsg; // = "readTraderMsg";
    static const QString ModifiTraderMsg; // = "modifiTraderMsg";
    static const QString StartStrategy; // = "StartStrategy";
    static const QString StopStrategy; // = "StopStrategy";
};

class MasterFileds : public noncopyable
{
public:
    static const QString ret; // = "10008";
    static const QString textDescribe; // = "58";
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

    class LogInfo: public noncopyable{
    public:
        static const QString beginRow; // = "10001";
        static const QString endRow; // = "10002";
        static const QString totalRow; // = "10003";
        static const QString currentPos; // = "10004";
        static const QString pathFileName; // = "10005";
        static const QString content; // = "10006";
        static const QString key; // = "10007";
    };

};

#endif // DEFINEFIELDS_H
