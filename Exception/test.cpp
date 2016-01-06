#include "excep.h"

class MyException : public ExceptionYX
{
public:
    YX_DEFINE_EXCEPTION(MyException, ExceptionYX);
};

void foo(){
   try
   {
      YX_THROW(MyException, "foo -> MyException");
   }
   catch(MyException& e)
   {
      printf("%s\n", e.what());
   }
}

int main()
{
   foo();
   return 0;
}

