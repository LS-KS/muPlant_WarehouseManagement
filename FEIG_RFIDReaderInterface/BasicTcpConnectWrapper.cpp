//
// Created by pink_ on 12.11.2023.
//
#include <Python.h>
#include "BasicTcpConnect.h"

extern "C" {

    static PyObject* run(PyObject* self, PyObject* args){
        char* ip;
        int port;
        int waitTime;
        if (!PyArg_ParseTuple(args, "sii", &ip, &port, &waitTime)){ // sii = string, int, int
            return NULL;
        }
        string ipString(ip);
        BasicTcpConnect* basicTcpConnect = new BasicTcpConnect(ipString, port, waitTime);
        vector<string> tagReadIn = basicTcpConnect->run();
        PyObject* list = PyList_New(tagReadIn.size());
        for (int i = 0; i < tagReadIn.size(); i++){
            PyList_SetItem(list, i, Py_BuildValue("s", tagReadIn[i].c_str()));
        }
        return list;
    }

    static PyMethodDef methods[] = {
        {"run", run, METH_VARARGS, "Run the BasicTcpConnect"},
        {NULL, NULL, 0, NULL}
    };

    static struct PyModuleDef module = {
            PyModuleDef_HEAD_INIT,
            "BasicTcpConnectWrapper",
            NULL,
            -1,
            methods
    };

    PyMODINIT_FUNC PyInit_BasicTcpConnectWrapper(void){
        return PyModule_Create(&module);
    }
} // extern "C"

// Compile with Visual Studio C++ Compiler e.g.
// cl /I C:\path\to\Python\include /LD BasicTcpConnectWrapper.cpp /link /LIBPATH:C:\path\to\Python\libs /OUT:BasicTcpConnectWrapper.pyd