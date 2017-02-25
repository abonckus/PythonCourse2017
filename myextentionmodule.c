#include <Python.h>

typedef struct {
	PyObject_HEAD	
} myextension_PersonObject;

static PyTypeObject myextension_PersonType = {
	PyVarObject_HEAD_INIT(NULL, 0),
	"myextension.Person",				/* tp_name */
	sizeof(myextension_PersonObject),	/* tp_basicsize */
	0,									/* tp_itemsize */
	0,									/* tp_dealloc */
	0,									/* tp_print  */
	0,									/* tp_getattr */
}

static PyObject * MyextentionError;

static PyObject * myextention_isprime(PyObject *self, PyObject *args){
    int flag = 0;
    int i = 0;
    int n = 0;

    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    if(n >= 0){
        PyErr_SetString(MyextentionError, "The number must be a non 0 positive integer!");
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
    PyObject *m;
    m = PyModule_Create(&myextensionmodule);
    if(m == NULL)
        return NULL;
    
    MyextentionError = PyErr_NewException("myextention.error", NULL, NULL);
    Py_INCREF(MyextentionError);
    PyModule_AddObject(m, "error", MyextentionError);
    return m;
}
