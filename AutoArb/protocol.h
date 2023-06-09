#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QJsonObject>

/**
 * @class Protocol
 * @brief 应用层协议包
 * @details 定长部分8字节，存长度以及类型，变长部分为json格式
*/
class Protocol
{
public:
    enum Type{
        none = 0,
        regist = 1,
        login = 2,
        addTrader = 3,
        deleteTrader = 4,
        addAccount = 5,
        deleteAccount,
        readTraderMsg,
        modifiTraderMsg,
        log,
        settingFile,
        startStrategy,
        stopStrategy,
    };
    Protocol(Type type = none);

    inline QJsonValue operator[](const QString& key)const{return object[key];}
    inline QJsonValueRef operator[](const QString& key){return object[key];}

    void setData(const QVariantMap& data);

    QVariantMap getData();

    inline Type getType()const{return this->type;}
    inline void setType(Type type){this->type = type;}

    QByteArray pack()const;
    int unpack(const QByteArray& buffer);

private:
    Type type;
    QJsonObject object;
};

#endif // PROTOCOL_H
