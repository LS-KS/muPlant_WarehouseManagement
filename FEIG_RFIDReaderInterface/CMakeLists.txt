# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(feig_rfid_module)

# Find Pybind11 package
find_package(pybind11 REQUIRED)

# Include the directory of the FEIG_RFIDReaderInterface project
add_subdirectory(C:/Users/pink_/Documents/GitHub/muPlant_WarehouseManagement/FEIG_RFIDReaderInterface)

# Define your library
add_library(feig_rfid_module MODULE dllmain.cpp wrapper.cpp)

# Link your library with the required libraries
target_link_libraries(feig_rfid_module PRIVATE FEIG_RFIDReaderInterface_LIBRARY_NAME)
target_link_libraries(feig_rfid_module PRIVATE pybind11::module)  # Link with Pybind11
