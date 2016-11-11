
#pragma once

#include <QtCore/qglobal.h>

#if defined(CAREMULATOR_LIBRARY)
#  define CAREMULATOR_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define CAREMULATOR_SHARED_EXPORT Q_DECL_IMPORT
#endif
