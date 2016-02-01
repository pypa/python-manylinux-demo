#include "Python.h"
#include "cblas.h"


/* The wrapper to the underlying C function */
static PyObject *
py_dot(PyObject *self, PyObject *args)
{
    PyObject *x_obj, *y_obj;
    double *x, *y;
    Py_ssize_t i, length_x, length_y;
    if (!PyArg_ParseTuple(args, "OO", &x_obj, &y_obj))
        return NULL;
    if ((!PySequence_Check(x_obj)) || (!PySequence_Check(y_obj))) {
        PyErr_SetString(PyExc_TypeError, "A sequence is required.");
        return NULL;
    }

    length_x = PySequence_Length(x_obj);
    length_y = PySequence_Length(y_obj);

    if (length_x < 0 || length_y < 0) {
        PyErr_SetString(PyExc_TypeError, "A sequence is required.");
        return NULL;
    }

    if (length_x != length_y) {
        PyErr_SetString(PyExc_ValueError, "Lengths are not aligned.");
    }

    x = (double*) calloc(length_x, sizeof(double));
    y = (double*) calloc(length_y, sizeof(double));

    for (i = 0; i < length_x; i++) {
        PyObject* x_item = PySequence_GetItem(x_obj, i);
        PyObject* y_item = PySequence_GetItem(y_obj, i);

        x[i] = PyFloat_AsDouble(x_item);
        if (PyErr_Occurred()) {
            Py_DECREF(x_item);
            Py_DECREF(y_item);
            PyErr_SetString(PyExc_TypeError, "Cannot convert object to double.");
            return NULL;
        }

        y[i] = PyFloat_AsDouble(y_item);
        if (PyErr_Occurred()) {
            Py_DECREF(x_item);
            Py_DECREF(y_item);
            PyErr_SetString(PyExc_TypeError, "Cannot convert object to double.");
            return NULL;
        }

        Py_DECREF(x_item);
        Py_DECREF(y_item);
    }

    double result = cblas_ddot(length_x, x, 1, y, 1);
    return PyFloat_FromDouble(result);
}

static PyMethodDef module_functions[] = {
	{"dot",  py_dot, METH_VARARGS, NULL},
	{NULL, NULL}      /* sentinel */
};


#if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "extension",     /* m_name */
        "This is a module",  /* m_doc */
        -1,                  /* m_size */
        module_functions,    /* m_methods */
        NULL,                /* m_reload */
        NULL,                /* m_traverse */
        NULL,                /* m_clear */
        NULL,                /* m_free */
    };
#endif


static PyObject *
moduleinit(void)
{
    PyObject *m;

#if PY_MAJOR_VERSION >= 3
    m = PyModule_Create(&moduledef);
#else
    m = Py_InitModule3("extension",
                        module_functions, "This is a module");
#endif
  return m;
}

#if PY_MAJOR_VERSION < 3
    PyMODINIT_FUNC
    initextension(void)
    {
        moduleinit();
    }
#else
    PyMODINIT_FUNC
    PyInit_extension(void)
    {
        return moduleinit();
    }
#endif
