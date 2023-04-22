//////////////
// main file of Serial Framework
// -
// Framework used to ensure easy access to serial devices connected to raspberry pi
// This project uses python scr

//////////
//
// Base SerialDevice 
// 	Holds Name and other general info
//
// SerialDevice::LedMatrix
//	LedMatrix SerialDevice
//

#include <iostream>
#include <Python.h>
#include <string>
#include <stdio.h>
#include <thread>



int main(int argc, char** argv)
{
	std::string pythonFileName{"testLedMatrix.py"};
	Py_SetProgramName(L"python3");
	Py_Initialize();


	FILE* pFile;
	pFile = fopen(pythonFileName.c_str(), "r");
	if(pFile == NULL){
		std::cout<<"file could not be opened!"<<std::endl;
		Py_Finalize();
		return 0;

	}
	PyRun_SimpleFile(pFile, pythonFileName.c_str());
	Py_Finalize();
	fclose(pFile);
	std::cout<<"hello world"<<std::endl;

	return 1;

}

