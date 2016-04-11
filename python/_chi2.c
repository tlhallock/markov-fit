#include <Python.h>
#include <numpy/arrayobject.h>
#include "chi2.h"


static char module_docstring[] =
    "This module provides an interface for calculating chi-squared using C.";
static char chi2_docstring[] =
    "Calculate the chi-squared of some data given a model.";
    
static PyObject *chi2_chi2(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"chi2", chi2_chi2, METH_VARARGS, chi2_docstring},
    {NULL, NULL, 0, NULL}
};



static PyObject *chi2_chi2(PyObject *self, PyObject *args)
{
    PyObject *q_obj;
    int i;

    /* Parse the input tuple */
    if (!PyArg_ParseTuple(args, "O", &q_obj))
        return NULL;

    /* Interpret the input objects as numpy arrays. */
    PyObject *x_array = PyArray_FROM_OTF(q_obj, NPY_DOUBLE, NPY_IN_ARRAY);

    /* If that didn't work, throw an exception. */
    if (x_array == NULL) {
        Py_XDECREF(x_array);
        return NULL;
    }

    /* How many data points are there? */
    int N = (int)PyArray_DIM(x_array, 0);

    /* Get pointers to the data as C-types. */
    double *x    = (double*)PyArray_DATA(x_array);

    double v = 0;
    for (i=0;i<N;i++)
    {
	    v += (1 - x[i]) * (1-x[i]);
    }
    
//    printf("The vector passed in was:\n");
//    for (int i=0;i<N;i++)
//    {
//	    printf("%lf ", x[i]);
//    }

    /* Clean up. */
    Py_DECREF(x_array);

//    if (v < 0.0) {
//        PyErr_SetString(PyExc_RuntimeError,
//                    "Chi-squared returned an impossible value.");
//        return NULL;
//    }

    /* Build the output tuple */
    PyObject *ret = Py_BuildValue("d", v);
    return ret;
}





PyMODINIT_FUNC init_chi2(void)
{
    PyObject *m = Py_InitModule3("_chi2", module_methods, module_docstring);
    if (m == NULL)
        return;

    /* Load `numpy` functionality. */
    import_array();
}

