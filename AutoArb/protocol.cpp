#include "protocol.h"
#include <QJsonDocument>
#include <cstring>

/**
 * @brief 构造函数
 * @variable type -> 类型
*/
Protocol::Protocol(Type type)
    : type(type)
{

}

/**
 * @brief 打包
*/
QByteArray Protocol::pack() const
{
    /** @note 1. 生成变长部分 */
    QByteArray body = QJsonDocument(object).toJson();

    /** @note 2. 生成定长部分 */
    QByteArray head(8, 0);
    int len = body.size();
    memcpy(head.data(), &len, 4);
    memcpy(head.data() + 4, &type, 4);

    return head + body;
}

/**
 * @brief 拆包
*/
int Protocol::unpack(const QByteArray &buffer)
{
    /** @note 1. 判断缓存长度，是否大于定长 */
    if(buffer.size() < 8)   return 0;

    QByteArray head = buffer.left(8);
    int len;
    memcpy(&len, head.data(), 4);

    /** @note 2. 判断缓存长度，是否大于定长+变长 */
    if(buffer.size() < (8 + len))   return 0;

    /** @note 3. 拆包 */
    memcpy(&type, head.data() + 4, 4);
    object = QJsonDocument::fromJson(buffer.mid(8, len)).object();

    return 8 + len;
}
