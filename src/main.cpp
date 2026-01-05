#ifdef WIN32
#include <Windows.h>
#endif
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif
#include "AutoSpace.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;
//AutoSpace auto2
//int add(int i, int j) { return i + j; }
//int sub(int i, int j) { return i - j; }
//
//struct MyData
//{
//    float x, y;
//
//    MyData() : x(0), y(0) {}
//    MyData(float x, float y) : x(x), y(y) {}
//
//    void print() { printf("%f, %f\n", x, y); }
//};

PYBIND11_MODULE(_auto2, m) {          // "example" module name should be same of module name in CMakeLists
    m.doc() = "korean autospace module"; // optional module docstring

    //m.def("add", &add, "A function that adds two numbers");
    //m.def("sub", &sub, "A function that subtracts two numbers");

    py::class_<AutoSpace>(m, "AutoSpace")
        .def(py::init<>())
        .def("autospace", &AutoSpace::autospace);
}
