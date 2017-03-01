#include <Python.h>
int main(int argc, char *argv[]){
    Py_Initialize();
    PyRun_SimpleString(
    "import myextension as ex\n"
    "n = 3\n"
    "if ex.isprime(n):\n"
    "\tprint(str(n) + ' is not prime')\n"
    "else:\n"
    "\tprint(str(n) + ' is prime')");
    Py_Finalize();
    return 0;
}