#include <Python.h>
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject *firstName;
    PyObject *lastName;
} myextension_Person;

static void
myextension_Person_dealloc(myextension_Person* self)
{
    Py_XDECREF(self->firstName);
    Py_XDECREF(self->lastName);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *myextension_Person_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    myextension_Person *self;

    self = (myextension_Person *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->firstName = PyUnicode_FromString("");
        if (self->firstName == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->lastName = PyUnicode_FromString("");
        if (self->lastName == NULL) {
            Py_DECREF(self);
            return NULL;
        }
    }

    return (PyObject *)self;
}

static int myextension_Person_init(myextension_Person *self, PyObject *args, PyObject *kwds)
{
    PyObject *firstName=NULL, *lastName=NULL, *tmp;

    static char *kwlist[] = {"firstName", "lastName", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
                                      &firstName, &lastName))
        return -1;

    if (firstName) {
        tmp = self->firstName;
        Py_INCREF(firstName);
        self->firstName = firstName;
        Py_XDECREF(tmp);
    }

    if (lastName) {
        tmp = self->lastName;
        Py_INCREF(lastName);
        self->lastName = lastName;
        Py_XDECREF(tmp);
    }

    return 0;
}

static PyMemberDef myextension_Person_members[] = {
    {"firstName", T_OBJECT_EX, offsetof(myextension_Person, firstName), 0,
     "first name"},
    {"lastName", T_OBJECT_EX, offsetof(myextension_Person, lastName), 0,
     "last name"},
    {NULL}  /* Sentinel */
};

static PyObject *myextension_Person_fullName(myextension_Person* self)
{
    if (self->firstName == NULL) {
        PyErr_SetString(PyExc_AttributeError, "firstName");
        return NULL;
    }

    if (self->lastName == NULL) {
        PyErr_SetString(PyExc_AttributeError, "lastName");
        return NULL;
    }

    return PyUnicode_FromFormat("%S %S", self->firstName, self->lastName);
}

static PyMethodDef myextension_Person_methods[] = {
    {"fullName", (PyCFunction)myextension_Person_fullName, METH_NOARGS,
     "Return the full name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject myextension_PersonType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "myextension.Person",             /* tp_name */
    sizeof(myextension_Person), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)myextension_Person_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
    "Person Object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    myextension_Person_methods,             /* tp_methods */
    myextension_Person_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)myextension_Person_init,      /* tp_init */
    0,                         /* tp_alloc */
    myextension_Person_new,                 /* tp_new */
};

static PyObject * myextensionError;

static PyObject * myextension_isprime(PyObject *self, PyObject *args){
    int flag = 0;
    int i = 0;
    int n = 0;

    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    if(n <= 0){
        PyErr_SetString(myextensionError, "The number must be a non 0 positive integer!");
        return NULL;
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

    if (PyType_Ready(&myextension_PersonType) < 0)
        return NULL;

    m = PyModule_Create(&myextensionmodule);
    if(m == NULL)
        return NULL;
    
    myextensionError = PyErr_NewException("myextension.error", NULL, NULL);
    Py_INCREF(myextensionError);
    PyModule_AddObject(m, "error", myextensionError);

    Py_INCREF(&myextension_PersonType);
    PyModule_AddObject(m, "Person", (PyObject *)&myextension_PersonType);
    return m;
}