#include <Python.h>

static PyObject * myextention_isprime(PyObject *self, PyObject *args){
    int flag = 0;
    int i = 0;
    int n = 0;

    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    for(i=2; i<=n/2; ++i)
    {
        if(n%i==0)
        {
            flag=1;
            break;
        }
    }
    return Py_BuildValue("i", flag);
}

static PyMethodDef myextension_methods[] = {
    {"isprime", myextention_isprime, METH_VARARGS, "Check if number is prime."}
};

static struct PyModuleDef myextensionmodule = {
    PyModuleDef_HEAD_INIT,
    "myextention",
    NULL,
    -1,
    myextension_methods
};

PyMODINIT_FUNC PyInit_myextention(void){
    return PyModule_Create(&myextensionmodule);
}