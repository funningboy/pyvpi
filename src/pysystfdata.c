/*
 * =====================================================================================
 *
 *       Filename:  pysystfdata.c
 *
 *    Description:  This is sys
 *
 *        Version:  1.0
 *        Created:  12/22/2011 09:54:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gene Kong (), gyx_edu@qq.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "pysystfdata.h"

PyTypeObject pyvpi_systfdata_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi._SysTfData",        /*tp_name*/
    sizeof(s_pyvpi_systfdata), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyvpi_systfdata_Dealloc, /*tp_dealloc*/    
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "pyvpi system task func data objects",     /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyvpi_systfdata_methods,       /* tp_methods */
    pyvpi_systfdata_members,       /* tp_members */
    pyvpi_systfdata_getsets,       /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) pyvpi_systfdata_Init, /* tp_init */
    0,                         /* tp_alloc */
    pyvpi_systfdata_New,           /* tp_new */
};


void pyvpi_systfdata_Dealloc(p_pyvpi_systfdata self)
{
    //Free self.
    Py_DECREF(self->tfname);
    Py_DECREF(self->calltf);
    Py_DECREF(self->compiletf);
    Py_DECREF(self->tfname);
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._SysTfData is release,ptr is <0x%lx>.\n",self);
#endif
    self->ob_type->tp_free((PyObject*)self);
}

int  pyvpi_systfdata_Init(s_pyvpi_systfdata *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"type"，"sysfunctype","tfname","calltf","compiletf","sizetf", NULL};
    self->tfname    =   NULL;
    self->calltf    =   NULL;
    self->compiletf =   NULL;
    self->sizetf    =   NULL;
    self->_vpi_systfdata.type           = vpiSysTask; //Default value.
    self->_vpi_systfdata.sysfunctype    = vpiSysTask; //Default value.
    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|iiOOOO", kwlist,                                      
                                      &self->_vpi_systfdata.type,
                                      &self->_vpi_systfdata.sysfunctype,
                                      &self->tfname,
                                      &self->calltf,
                                      &self->compiletf,
                                      &self->sizetf
                                      ))
        return -1;
    //Check type and sysfunctype.
    if(self->_vpi_systfdata.type == vpiSysTask) {
        if(self->_vpi_systfdata.sysfunctype != vpiSysTask) {
            PyErr_SetString(PyExc_TypeError, "Can't set sysfunctype to other values"
                    "except vpiSysTask for vpiSysTask.");
            return -1;
        }
    }
    else if(self->_vpi_systfdata.sysfunctype == vpiSysFunc){
        if(self->_vpi_systfdata.sysfunctype != vpiSysTask) {
            PyErr_SetString(PyExc_TypeError, "Can't set sysfunctype to other values "
                    "except vpi[Int,Real,Time,Sized,SizedSigned]Func for vpiSysFunc.");
            return -1;
        }
    }
    else {
        PyErr_SetString(PyExc_TypeError, "Can't set type to other values except vpiSysTask,vpiSysFunc.");
        return -1;
    }
    //Check tfname
    if(self->tfname == NULL){
        PyErr_SetString(PyExc_TypeError, "Can't set tfname to None.");
        return -1;
    } else {
        Py_INCREF(self->tfname);
        self->_vpi_systfdata.tfname = PyString_AsString(self->tfname);
    }
    self->_vpi_systfdata.user_data = self;
    //Check calltf
    if(self->calltf == NULL){
        PyErr_SetString(PyExc_TypeError, "Can't set calltf to None.");
        return -1;
    } 
    else {
        if (!PyCallable_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "calltf must be a callable.");
            return -1;
        }
        Py_INCREF(self->calltf);
        self->_vpi_systfdata.calltf = _calltf;
    }
    //Check compiletf
    if(self->compiletf == NULL){
        Py_INCREF(Py_None);
        self->compiletf = Py_None;
    } 
    else {
        if (!PyCallable_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "compiletf must be a callable.");
            return -1;
        }
        Py_INCREF(self->compiletf);
        self->_vpi_systfdata.compiletf = _compiletf;
    }
    //Check sizetf
    if(self->sizetf == NULL){
        Py_INCREF(Py_None);
        self->sizetf = Py_None;
    } 
    else {
        if (!PyCallable_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "sizetf must be a callable.");
            return -1;
        }
        PyINCREF(self->sizetf);
        self->_vpi_systfdata.sizetf = _sizetf;
    }
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._SysTfData is Initial,type is <0x%lx>.\n",self->_vpi_systfdata.type);
#endif
    return 0;
}

PyObject * pyvpi_systfdata_New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{   
    p_pyvpi_systfdata self = (p_pyvpi_systfdata)type->tp_alloc(type, 0);
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._SysTfData is allocate,ptr is <0x%lx>, type ptr is <0x%lx>.\n",self,type);
#endif
    return (PyObject *) self;
}

PyObject * s_pyvpi_systfdata_gettype(s_pyvpi_value *self, void *closure)
{
    return Py_BuildValue("i",self->_vpi_systfdata.type);
}
int        s_pyvpi_systfdata_settype(s_pyvpi_value *self, PyObject *value, void *closure)
{
    //Check type, it must be vpiSysTask,vpiSysFunc.
    int tmp;
    if(!PyInt_Check(value)){
        PyErr_SetString(PyExc_TypeError,
                        "The value must be vpiSys[Task,Func].");
        return -1;
    }
    tmp = PyInt_AS_LONG(value);
    if(tmp != vpiSysTask &&
       tmp != vpiSysFunc) {
        PyErr_SetString(PyExc_TypeError,
                        "The value must be vpiSys[Task,Func].");
        return -1;
    }
    self->_vpi_systfdata.type = tmp;
    return 0;
}

PyObject * s_pyvpi_systfdata_getsystftype(s_pyvpi_value *self, void *closure)
{
    //Get SysTask/Func return type.
     return Py_BuildValue("i",self->_vpi_systfdata.systftype);
}
int        s_pyvpi_systfdata_setsystftype(s_pyvpi_value *self, PyObject *value, void *closure)
{
    //Set SysTask/Func return type.
    //Check type, it must be vpiSysTask,vpiSysFunc.
    int tmp;
    if(!PyInt_Check(value)){
        PyErr_SetString(PyExc_TypeError,
                        "The value must be vpiSysTask, vpi[Int,Real,Time,Sized,SizedSigned]Func.");
        return -1;
    }
    tmp = PyInt_AS_LONG(value);
    if(self->_vpi_systfdata.type == vpiSysTask){
        //Task
        if(tmp != vpiSysTask){
            PyErr_SetString(PyExc_TypeError,
                            "The value must be vpiSysTask when type is vpiSysTask.");
            return -1;
        }
    }
    else {
        //Function return...
        if( tmp == vpiIntFunc   ||
            tmp == vpiRealFunc  ||
            tmp == vpiTimeFunc  ||
            tmp == vpiSizedFunc ||
            tmp == vpiSizedSignedFunc )
        {
            //dummy code here...
        }
        else {
            PyErr_SetString(PyExc_TypeError,
                            "The value must be vpi[Int,Real,Time,Sized,SizedSigned]Func when type is vpiSysFunc.");
            return -1;
        }
    }
    self->_vpi_systfdata.systftype = tmp;
    return 0;    
}    

PyObject * s_pyvpi_systfdata_gettfname(s_pyvpi_value *self, void *closure)
{
    Py_INCREF(self->tfname);
    return self->tfname;
}
int        s_pyvpi_systfdata_settfname(s_pyvpi_value *self, PyObject *value, void *closure)
{
    char * name;
    if(self->tfname == NULL){
        PyErr_SetString(PyExc_TypeError, "Can't set tfname to None.");
        return -1;
    }

    name = PyString_AsString(self->tfname);
    if(strlen(name)<2) {
        PyErr_SetString(PyExc_TypeError, "The tfname len must big than 1.");
        return -1;
    }
    if(name[0] != "$") {
        PyErr_SetString(PyExc_TypeError, "The tfname must start with $");
        return -1;
    }
    Py_INCREF(value);
    self->_vpi_systfdata.tfname = name; 
    Py_XDECREF(self->tfname);
    self->tfname = value;
    return 0;
}

PyObject * s_pyvpi_systfdata_getcalltf(s_pyvpi_value *self, void *closure)
{
    Py_INCREF(self->calltf);
    return self->calltf;
}
int        s_pyvpi_systfdata_setcalltf(s_pyvpi_value *self, PyObject *value, void *closure)
{

}

PyObject * s_pyvpi_systfdata_getcompiletf(s_pyvpi_value *self, void *closure)
{
    Py_INCREF(self->compiletf);
    return self->compiletf;
}

int        s_pyvpi_systfdata_setcompiletf(s_pyvpi_value *self, PyObject *value, void *closure)
{
}

PyObject * s_pyvpi_systfdata_getsizetf(s_pyvpi_value *self, void *closure)
{
    Py_INCREF(self->sizetf);
    return self->sizetf;
}

int        s_pyvpi_systfdata_setsizetf(s_pyvpi_value *self, PyObject *value, void *closure)
{
}

PLI_INT32 _calltf(PLI_BYTE8 *self)
{
    p_pyvpi_systfdata _self = (p_pyvpi_systfdata) self;
    PyObject * ans;
    arglist = Py_BuildValue("(O)",_self);
    ans = PyObject_CallObject(self->calltf, arglist);
    Py_DECREF(arglist);
    if(ans == NULLL) 
        return 0;
    if(PyInt_Check(ans)){
        return PyInt_AsLong(ans);
    }
    if(PyFloat_Check(ans)){
        return PyFloat_AsDouble(ans);
    }
    //What is time function???
    return 0;
}

PLI_INT32 _compiletf(PLI_BYTE8 *self)
{
    p_pyvpi_systfdata _self = (p_pyvpi_systfdata) self;
    PyObject * ans;
    arglist = Py_BuildValue("(O)",_self);
    ans = PyObject_CallObject(self->compiletf, arglist);
    Py_DECREF(arglist);
    if(ans == NULLL) 
        return 0;
    if(PyInt_Check(ans)){
        return PyInt_AsLong(ans);
    }
    if(PyFloat_Check(ans)){
        return PyFloat_AsDouble(ans);
    }
    //What is time function???
    return 0;
}

PLI_INT32 _sizetf(PLI_BYTE8 *self)
{
    p_pyvpi_systfdata _self = (p_pyvpi_systfdata) self;
    PyObject * ans;
    arglist = Py_BuildValue("(O)",_self);
    ans = PyObject_CallObject(self->sizetf, arglist);
    Py_DECREF(arglist);
    if(ans == NULLL) 
        return 0;
    if(PyInt_Check(ans)){
        return PyInt_AsLong(ans);
    }
    if(PyFloat_Check(ans)){
        return PyFloat_AsDouble(ans);
    }
    //What is time function???
    return 0;
}

