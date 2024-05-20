#include <Python.h>

static PyObject *init(PyObject *self, PyObject *args) {
    const char *device;
    int baud;
    if (!PyArg_ParseTuple(args, "si", &device, &baud)) {
        return NULL;
    }
    PyObject *module = PyImport_ImportModule("RoboPiLib");
    if (module == NULL) {
        PyErr_Print();
        return NULL;
    }
    PyObject *init_func = PyObject_GetAttrString(module, "RoboPiInit");
    if (init_func == NULL || !PyCallable_Check(init_func)) {
        PyErr_Print();
        Py_XDECREF(init_func);
        Py_XDECREF(module);
        return NULL;
    }
    PyObject *result = PyObject_CallFunction(init_func, "si", device, baud);
    Py_XDECREF(init_func);
    Py_XDECREF(module);
    return result;
}

static PyObject *servo(PyObject *self, PyObject *args) {
    int pin, val;
    if (!PyArg_ParseTuple(args, "ii", &pin, &val)) {
        return NULL;
    }
    PyObject *module = PyImport_ImportModule("RoboPiLib");
    if (module == NULL) {
        PyErr_Print();
        return NULL;
    }
    PyObject *servo_func = PyObject_GetAttrString(module, "servoWrite");
    if (servo_func == NULL || !PyCallable_Check(servo_func)) {
        PyErr_Print();
        Py_XDECREF(servo_func);
        Py_XDECREF(module);
        return NULL;
    }
    PyObject *result = PyObject_CallFunction(servo_func, "ii", pin, val);
    Py_XDECREF(servo_func);
    Py_XDECREF(module);
    return result;
}

static PyObject *exit(PyObject *self, PyObject *args) {
    PyObject *module = PyImport_ImportModule("RoboPiLib");
    if (module == NULL) {
        PyErr_Print();
        return NULL;
    }
    PyObject *exit_func = PyObject_GetAttrString(module, "RoboPiExit");
    if (exit_func == NULL || !PyCallable_Check(exit_func)) {
        PyErr_Print();
        Py_XDECREF(exit_func);
        Py_XDECREF(module);
        return NULL;
    }
    PyObject *result = PyObject_CallFunction(exit_func, NULL);
    Py_XDECREF(exit_func);
    Py_XDECREF(module);
    return result;
}

static PyMethodDef RoboPiMethods[] = {
    {"init", init, METH_VARARGS, "Initialize RoboPi."},
    {"servo", servo, METH_VARARGS, "Control servo."},
    {"exit", exit, METH_NOARGS, "Clean up RoboPi resources."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef RoboPiModule = {
    PyModuleDef_HEAD_INIT,
    "RoboPiLib", // Module name
    NULL, // Module documentation
    -1,
    RoboPiMethods
};

PyMODINIT_FUNC PyInit_RoboPiLib(void) {
    return PyModule_Create(&RoboPiModule);
}
