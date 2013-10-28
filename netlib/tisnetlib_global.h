#ifndef TISNETLIB_GLOBAL_H
#define TISNETLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TISNETLIB_LIBRARY)
#  define TISNETLIB_EXPORT Q_DECL_EXPORT
#else
#  define TISNETLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // TISNETLIB_GLOBAL_H
