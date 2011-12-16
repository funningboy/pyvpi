//The 
#include "pyvalue.h"

//Type define here
PyTypeObject pyvpi_value_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyvpi._Value",             /*tp_name*/
    sizeof(s_pyvpi_value),     /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyvpi_value_Dealloc, /*tp_dealloc*/    
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
    "pyvpi value objects",     /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyvpi_value_methods,       /* tp_methods */
    pyvpi_value_members,       /* tp_members */
    pyvpi_value_getsets,       /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) pyvpi_value_Init, /* tp_init */
    0,                         /* tp_alloc */
    pyvpi_value_New,           /* tp_new */
};

void pyvpi_value_Dealloc(p_pyvpi_value self)
{
    //Free self.
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Value is release,ptr is 0x%x.\n",self);
#endif    
    self->ob_type->tp_free((PyObject*)self);
}

int  pyvpi_value_Init(s_pyvpi_value *self, PyObject *args, PyObject *kwds)
{    
    static char *kwlist[] = {"format", NULL};
    
    self->_vpi_value.format = vpiHexStrVal; //Default value.
    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist,                                      
                                      &self->_vpi_value.format))
        return -1;
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Value is Initial,format is 0x%x.\n",self->_vpi_value.format);
#endif
    return 0;
}

PyObject * pyvpi_value_New(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    p_pyvpi_value   self;
    self = (p_pyvpi_value)type->tp_alloc(type, 0);
#ifdef PYVPI_DEBUG
    vpi_printf("[PYVPI_DEBUG] pyvpi._Value is allocate,ptr is <0x%x>, type ptr is <0x%x>.\n",self,type);
#endif 
    return (PyObject *) self;
}


//Get/Set
PyObject * s_pyvpi_value_getvalue(s_pyvpi_value *self, void *closure)
{
    switch(self->_vpi_value.format){
        case vpiBinStrVal: 
        case vpiOctStrVal: 
        case vpiDecStrVal:
        case vpiHexStrVal: 
        case vpiStringVal:
            //Need malloc new space or not??
            return Py_BuildValue("s",self->_vpi_value.value.str);
        case vpiScalarVal:
            return Py_BuildValue("i",self->_vpi_value.value.scalar);
        case vpiIntVal:
            return Py_BuildValue("i",self->_vpi_value.value.integer);
        case vpiRealVal:
            return Py_BuildValue("d",self->_vpi_value.value.real);
        case vpiVectorVal:  //TBD
        case vpiStrengthVal:  //TBD
        case vpiTimeVal : //TBD
        case vpiObjTypeVal: //TBD
        case vpiSuppressVal: //TBD
        default : 
            Py_INCREF(Py_None);
            return Py_None;
    }
}
int        s_pyvpi_value_setvalue(s_pyvpi_value *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot set index to NULL.");
        return -1;
    }
//    if (! PyInt_Check(value)) {
//        PyErr_SetString(PyExc_TypeError,
//                        "The index must be a int.");
//        return -1;
//    }
    switch(self->_vpi_value.format){
        case vpiBinStrVal: 
        case vpiOctStrVal: 
        case vpiDecStrVal:
        case vpiHexStrVal: 
        case vpiStringVal:
            //Need malloc new space or not??
            
        case vpiScalarVal:
            
        case vpiIntVal:
            
        case vpiRealVal:
            
        case vpiVectorVal:  //TBD
        case vpiStrengthVal:  //TBD
        case vpiTimeVal : //TBD
        case vpiObjTypeVal: //TBD
        case vpiSuppressVal: //TBD
        default : 
            return -1;
    }
}
