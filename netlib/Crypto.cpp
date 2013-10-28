#include "Crypto.h"

#include <QtCore/QCryptographicHash>
#include <QtCore/QDateTime>

QByteArray Crypto::sessionId(const QString &ip)
{
    QCryptographicHash hash(QCryptographicHash::Md5);

    hash.addData(ip.toAscii());
    hash.addData(QByteArray::number(QDateTime::currentDateTime().toTime_t()));

    return hash.result();
}

QByteArray Crypto::passwordHash(const QString &password)
{
    QCryptographicHash hash(QCryptographicHash::Md5);

    hash.addData(password.toAscii());
    QByteArray salt = hash.result();
    hash.addData(salt.toHex());

    return hash.result().toHex();
}
