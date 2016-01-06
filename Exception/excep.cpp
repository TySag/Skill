#include "excep.h"

//class ExceptionYX;
//class string;

ExceptionYX::ExceptionYX(const string& msg) throw()
    : mMsg(msg),
      mFile("<unknown file>"),
      mFunc("<unknow func>"),
      mLine(-1),
      mStackTraceSize(0)
{}

ExceptionYX::~ExceptionYX() throw()
{}

void ExceptionYX::Init(const char* file, const char* func, int line)
{
    mFile = file;
    mFunc = func;
    mLine = line;
    mStackTraceSize = backtrace(mStackTrace, MAX_STACK_TRACE_SIZE);
}

string ExceptionYX::GetClassName() const
{
    return "ExceptionYX";
}

string ExceptionYX::GetMessage() const
{
    return mMsg;
}
   
const char* ExceptionYX::what() const throw()
{
    return ToString().c_str();
}

const string& ExceptionYX::ToString() const
{
    if(mWhat.empty()){
        stringstream sstr("");
        if(mLine > 0) sstr << mFile <<"(" << mLine << ")";
        sstr << ": " << GetClassName();
        if(!GetMessage().empty()) sstr << ": " << GetMessage();
        sstr << "\nStack Trace:\n";
        sstr << GetStackTrace();
        mWhat = sstr.str();
    }
    return mWhat;
}
    
string ExceptionYX::GetStackTrace() const
{
    if(mStackTraceSize == 0) return "<No stack trace>\n";
    char ** strings = backtrace_symbols(mStackTrace, 10);
    if(strings == NULL) return "<Unknown error: backtrace_symbols returned NULL>";
    
    string result;
    for(size_t i=0; i < mStackTraceSize; i++)
    {
       string mangledName = strings[i];
       string::size_type begin = mangledName.find('(');
       string::size_type end = mangledName.find('+', begin);
       if(begin == string::npos || end == string::npos)
       {
          result += mangledName;
          result += "\n";
          continue;
       }
       ++begin;
       int status;
       char* s = abi::__cxa_demangle(mangledName.substr(begin, end - begin).c_str(),
                                    NULL, 0, &status);
       if(status != 0)
       {
          result += mangledName;
          result += "\n";
          continue;
       }
       string demangledName(s);
       free(s);
       
       result += mangledName.substr(0, begin);
       result += demangledName;
       result += mangledName.substr(end);
       result += "\n";
    }
    free(strings);
    return result;
}



