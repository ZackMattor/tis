#ifndef CRYPTO_H
#define CRYPTO_H

#include <QtCore/QByteArray>

#include "tisnetlib_global.h"

class TISNETLIB_EXPORT Crypto
{
public:
    static QByteArray sessionId(const QString &ip);
    static QByteArray passwordHash(const QString &password);

private:
    Crypto();
};

#endif // CRYPTO_H
