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
    0,                                  /* tp_setattr */
    0,                                  /* tp_reserved */
    0,                                  /* tp_repr */
    0,                                  /* tp_as_number */
    0,                                  /* tp_as_sequence */
    0,                                  /* tp_as_mapping */
    0,                                  /* tp_hash  */
    0,                                  /* tp_call */
    0,                                  /* tp_str */
    0,                                  /* tp_getattro */
    0,                                  /* tp_setattro */
    0,                                  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "myextension objects",                    /* tp_doc */
}

static PyObject * myextensionError;

static PyObject * myextension_isprime(PyObject *self, PyObject *args){
    int flag = 0;
    int i = 0;
    int n = 0;

    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    if(n >= 0){
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

    myextension_PersonType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&myextension_PersonType) < 0)
        return NULL;

    m = PyModule_Create(&myextensionmodule);
    if(m == NULL)
        return NULL;
    
    myextensionError = PyErr_NewException("myextension.error", NULL, NULL);
    Py_INCREF(myextensionError);
    PyModule_AddObject(m, "error", myextensionError);
    
    Py_INCREF(myextensionError);
    PyModule_AddObject(m, "Person", (PyObject *)&myextension_PersonType);

    return m;
}
