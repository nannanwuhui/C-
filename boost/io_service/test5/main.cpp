#include <boost/bind.hpp>
#include <tea/tea.h>
void F1(){
    Debug("*** %s ***",__FUNCTION__);
}
int main()
{
    /**
     * If we run the program, we would see no output.
     * This is because we created a function invocation object, but did not actually call it.
     * To call it, we simply use the () operator of the object.
     */
//    boost::bind(&F1);
    boost::bind(&F1)();
    return 0;
}

