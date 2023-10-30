cmake_minimum_required(VERSION 3.26)

project(FEIGRfidInterface)
set(CMAKE_CXX_STANDARD 23)

# Add your source files here
add_executable(BasicTcpConnect BasicTcpConnect.cpp)

# Specify the directories where CMake should look for libraries
target_include_directories(BasicTcpConnect PRIVATE /Users/lennartschink/Documents/GitHub/muPlant_WarehouseManagement/FEIG_RFIDReaderInterface/FEIG.ID.SDK.Gen3.Windows.Cpp-v6.6.0/x64.vc142/include/fedm)

# Link the necessary libraries from the FEIG SDK
target_link_libraries(BasicTcpConnect /Users/lennartschink/Documents/GitHub/muPlant_WarehouseManagement/FEIG_RFIDReaderInterface/FEIG.ID.SDK.Gen3.Windows.Cpp-v6.6.0/x64.vc142/lib/FEIDiLib)
target_link_libraries(BasicTcpConnect /Users/lennartschink/Documents/GitHub/muPlant_WarehouseManagement/FEIG_RFIDReaderInterface/FEIG.ID.SDK.Gen3.Windows.Cpp-v6.6.0/x64.vc142/lib/FEIDiLib32)

# If you have other libraries or dependencies, add them here
# target_link_libraries(BasicTcpConnect some_other_library)

# Optionally, set the output directory for the built executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)



