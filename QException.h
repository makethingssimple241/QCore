#ifndef QEXCEPTION_H
#define QEXCEPTION_H

#include "QLog.h"

#ifdef QTRACEBACK
#define throw(m_exception, m_message) QLog("Traceback (most recent call last):\n"); \
                                      QLog_traceback(); \
                                      QLog("%s: %s\n", #m_exception, m_message); \
                                      QLog_deinit(); \
                                      exit(EXIT_FAILURE)
#else
#define throw(m_exception, m_message) QLog("%s: %s\n", #m_exception, m_message); \
                                      QLog_deinit(); \
                                      exit(EXIT_FAILURE)
#endif


#endif /* QEXCEPTION_H */
