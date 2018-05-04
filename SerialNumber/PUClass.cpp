#include "stdafx.h"
#include "PUClass.h"


CPUClass::CPUClass()
{
}


CPUClass::~CPUClass()
{
}

CString CPUClass::ReadCPU()
{
	std::array<int, 4> cpui;    //#include <array>
								// Calling __cpuid with 0x0 as the function_id argument  
								// gets the number of the highest valid function ID.  什么是function ID？
	__cpuid(cpui.data(), 0x0);    //cpui[0] = "funcition_id的最大值"
	int nIds_ = cpui[0];
	std::vector<std::array<int, 4>> data_;  //保存遍历到的所有cpui的值    
	for (int i = 0; i <= nIds_; ++i)
	{
		__cpuidex(cpui.data(), i, 0);
		data_.push_back(cpui);
	}
	//reinterpret_cast<int*>(vendor) //*reinterpret_cast<int*>(vendor)
	//索引0 0+4 0+8的值构成了CPU芯片的名称
	char vendor[0x20] = { 0 };
	*reinterpret_cast<int*>(vendor) = data_[0][1];
	*reinterpret_cast<int*>(vendor + 4) = data_[0][3];
	*reinterpret_cast<int*>(vendor + 8) = data_[0][2];  // vendor="GenuineIntel"    
	std::string vendor_ = vendor;
	bool isIntel_ = false;
	bool isAMD = false;
	if ("GenuineIntel" == vendor_)
	{
		isIntel_ = true;    //厂商为INTEL
	}
	else if ("AuthenticAMD" == vendor_)
	{
		isAMD = true;       //厂商为AMD
	}
	char vendor_serialnumber[0x14] = { 0 };
	sprintf_s(vendor_serialnumber, sizeof(vendor_serialnumber), "%08X%08X", data_[1][3], data_[1][0]);
	CString str;
	str = vendor_serialnumber;
	return str;
}