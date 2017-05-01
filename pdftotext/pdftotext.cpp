#include <Python.h>
#include <structmember.h>

typedef struct {
    PyObject_HEAD
    int page_count;
    // TODO: poppler doc will go here
} PDF;

static PyMemberDef PDF_members[] = {
    {
        (char*)"page_count",
        T_INT,
        offsetof(PDF, page_count),
        READONLY,
        (char*)"Page count.",
    },
    {NULL},  // Sentinel
};

static int PDF_init(PDF* self, PyObject* args, PyObject* kwds) {
    PyObject* arg;
    static char* kwlist[] = {(char*)"pdf_file", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist, &arg)) {
        return -1;
    }

    return 0;
}

static PyObject* PDF_read(PyObject* self, PyObject* args, PyObject* kwds) {
    int* page_number;
    static char* kwlist[] = {(char*)"page_number", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &page_number)) {
        return NULL;
    }
    return PyUnicode_FromString("TODO: read a single page");
}

static PyObject* PDF_read_all(PyObject* self, PyObject*) {
    return PyUnicode_FromString("TODO: read the whole document");
}

static void PDF_dealloc(PDF* self) {
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyMethodDef PDF_methods[] = {
    {
        "read",
        (PyCFunction)PDF_read,
        METH_VARARGS | METH_KEYWORDS,
        "Extract text from the given page number.",
    },
    {
        "read_all",
        PDF_read_all,
        METH_NOARGS,
        "Extract text from the entire document.",
    },
    {NULL},  // Sentinel
};

static PyTypeObject pdftotext_PDFType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pdftotext.PDF",             // tp_name
    sizeof(PDF),                 // tp_basicsize
    0,                           // tp_itemsize
    (destructor)PDF_dealloc,     // tp_dealloc
    0,                           // tp_print
    0,                           // tp_getattr
    0,                           // tp_setattr
    0,                           // tp_reserved
    0,                           // tp_repr
    0,                           // tp_as_number
    0,                           // tp_as_sequence
    0,                           // tp_as_mapping
    0,                           // tp_hash
    0,                           // tp_call
    0,                           // tp_str
    0,                           // tp_getattro
    0,                           // tp_setattro
    0,                           // tp_as_buffer
    Py_TPFLAGS_DEFAULT,          // tp_flags
    "TODO: docstring for PDF.",  // tp_doc
    0,                           // tp_traverse
    0,                           // tp_clear
    0,                           // tp_richcompare
    0,                           // tp_weaklistoffset
    0,                           // tp_iter
    0,                           // tp_iternext
    PDF_methods,                 // tp_methods
    PDF_members,                 // tp_members
    0,                           // tp_getset
    0,                           // tp_base
    0,                           // tp_dict
    0,                           // tp_descr_get
    0,                           // tp_descr_set
    0,                           // tp_dictoffset
    (initproc)PDF_init,          // tp_init
};

static PyObject* PdftotextError;

static PyModuleDef pdftotextmodule = {
    PyModuleDef_HEAD_INIT,
    "pdftotext",
    "Simple PDF text extraction.",
};

PyMODINIT_FUNC PyInit_pdftotext() {
    PyObject* module;

    pdftotext_PDFType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&pdftotext_PDFType) < 0) {
        return NULL;
    }

    module = PyModule_Create(&pdftotextmodule);
    if (module == NULL) {
        return NULL;
    }

    Py_INCREF(&pdftotext_PDFType);
    PyModule_AddObject(module, "PDF", (PyObject*)&pdftotext_PDFType);

    PdftotextError = PyErr_NewExceptionWithDoc(
        "pdftotext.Error", "TODO: docstring for Error.", NULL, NULL);
    Py_INCREF(PdftotextError);
    PyModule_AddObject(module, "Error", PdftotextError);

    return module;
}
