#include <dllmain.h>
#include <std>
#include <pybind11/pybind11.h>

using namespace std;
namespace py = pybind11;


vector<string> runBasicTcpConnect(BasicTcpConnect& connector) {
	return connector.run();
}

PYBIND11_MODULE(feig_rfid_module, m) {
	m.doc() = "Wrapper module for FEIG Gen3 Windows SDK. It uses a BasicTcpConnection class to connect to a given ip, port, reads for a given readTime and returns all tagInfos as String vector.";
	py::class_<BasicTcpConnect>(m, "BasicTcpConnect")
		.def(py::init<std::string&, uint16_t, int>())
		.def("run", &runBasicTcpConnect);
}