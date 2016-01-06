#ifndef __EXCEP_YX_HH__
#define __EXCEP_YX_HH__

#include <execinfo.h>
#include <stdlib.h>
#include <cxxabi.h>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <sstream>
#include <exception>
#include <string>

using namespace std;

#define YX_THROW(ExClass, args, ...)                   \
   do                                                 \
   {                                                  \
     ExClass e(args);                                 \
     e.Init(__FILE__, __PRETTY_FUNCTION__, __LINE__); \
     throw e;                                         \
   }                                                  \
   while(false)

#define YX_DEFINE_EXCEPTION(ExClass, Base)           \
   ExClass(const string& msg = "") throw()      \
       : Base(msg)                                   \
   {}                                                \
   ~ExClass() throw() {}                             \
   string GetClassName() const                  \
   {                                                 \
       return #ExClass;                               \
   }                                    

class ExceptionYX : public exception
{
public:
    ExceptionYX(const string& msg = "") throw();
    virtual ~ExceptionYX() throw();
    void Init(const char* file, const char* func, int line);
    virtual string GetClassName() const;
    virtual string GetMessage() const;
    const char* what() const throw();
    const string& ToString() const;
    string GetStackTrace() const;

protected:
    string mMsg;
    const char* mFile;
    const char* mFunc;
    int mLine;

private:
    enum {MAX_STACK_TRACE_SIZE = 50};
    void *mStackTrace[MAX_STACK_TRACE_SIZE];
    size_t mStackTraceSize;
    mutable string mWhat;

};

#endif
