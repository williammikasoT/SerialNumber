#include "../stdafx.h"
#include "ExcelClass.h"


ExcelClass::ExcelClass()
{
}


ExcelClass::~ExcelClass()
{
}


BOOL ExcelClass::InitExcel()
{
	if (!AfxOleInit())
	{
		//MessageBox(L"��ʼ��������");
		return FALSE;
	}
	return TRUE;
}

BOOL ExcelClass::WriteExcel(std::vector<CString> vtrData, CString strFileName,BOOL bLogExcelTimeLastCol)
{
	std::vector<CString> vStrLetter,vStrData;
	// ��ʱ���дABCDE��
	vStrLetter.push_back("A");
	vStrLetter.push_back("B");
	vStrLetter.push_back("C");
	vStrLetter.push_back("D");
	vStrLetter.push_back("E");
	vStrLetter.push_back("F");
	vStrLetter.push_back("G");
	vStrLetter.push_back("H");
	vStrLetter.push_back("I");
	vStrLetter.push_back("J");
	vStrLetter.push_back("K");
	vStrLetter.push_back("L");





	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		//this->MessageBox(_T("�޷�����ExcelӦ�ã�"));
		return FALSE;
	}

	books = app.get_Workbooks();
	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, szPath);
	CString strPath(szPath);
	strPath += strFileName; // "\\ģ��.xlsx"
	lpDisp = books.Open(strPath, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	book.AttachDispatch(lpDisp);
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));
	//��õ�Ԫ������� ʹ������׷�Ӽ�¼
	range = sheet.get_UsedRange();
	range = range.get_Rows();
	long UsedRows = range.get_Count();
	CString strNum;
	strNum.Format("%d", UsedRows + 1);


	if (bLogExcelTimeLastCol) 
	{
		vtrData.push_back(GetCurTiem());
	}

	//A3 A3,B3 B3 C3 C3,D3 D3
	CString strI;
	for (int i = 0; i < vtrData.size(); i++)
	{
		strI = vStrLetter[i] + strNum;
		range = sheet.get_Range(COleVariant(strI), COleVariant(strI));
		CString sss = vtrData[i];
		range.put_Value2(COleVariant(sss));  // ��������
	}

	// excel�����ļ�����ǰĿ¼�¸���,����ʾ����
	book.Save();
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.Quit();
	app.ReleaseDispatch();

	return TRUE;

}

CString ExcelClass::GetCurTiem()
{
	CString strTime, str;
	CTime time = CTime::GetCurrentTime();   ///����CTime����
	int m_nYear = time.GetYear();      ///��
	int m_nMonth = time.GetMonth();      ///��
	int m_nDay = time.GetDay();      ///��
	int m_nHour = time.GetHour();      ///Сʱ
	int m_nMinute = time.GetMinute();   ///����
	int m_nSecond = time.GetSecond();   ///��
	strTime.Format("%d/", m_nYear);
	str = strTime;
	strTime.Format("%02d/", m_nMonth);
	str += strTime;
	strTime.Format("%02d/", m_nDay);
	str += strTime;
	strTime.Format("%02d:", m_nHour);
	str += strTime;
	strTime.Format("%02d:", m_nMinute);
	str += strTime;
	strTime.Format("%02d", m_nSecond);
	str += strTime;

	return str;
}