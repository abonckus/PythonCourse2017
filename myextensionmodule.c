#include <Python.h>

static PyObject * myextensionError;

static PyObject * myextension_isprime(PyObject *self, PyObject *args){
    int flag = 0;
    int i = 0;
    int n = 0;

    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    if(n <= 0){
        PyErr_SetString(myextensionError, "The number must be a non 0 positive integer!");
    }
    
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
    {"isprime", myextension_isprime, METH_VARARGS, "Check if number is prime."}
};

static struct PyModuleDef myextensionmodule = {
    PyModuleDef_HEAD_INIT,
    "myextension",
    NULL,
    -1,
    myextension_methods
};

PyMODINIT_FUNC PyInit_myextension(void){
    PyObject *m;
    m = PyModule_Create(&myextensionmodule);
    if(m == NULL)
        return NULL;
    
    myextensionError = PyErr_NewException("myextension.error", NULL, NULL);
    Py_INCREF(myextensionError);
    PyModule_AddObject(m, "error", myextensionError);
    return m;
}