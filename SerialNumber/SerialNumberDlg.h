
// SerialNumberDlg.h : 头文件
//

#include"ExcelClass\ExcelClass.h"
#pragma once

// 函数返回数组使用


// CSerialNumberDlg 对话框
class CSerialNumberDlg : public CDialogEx
{
// 构造
public:
	CSerialNumberDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALNUMBER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCreate();
	CString ArrayByCString(char * data);
	//CString 
	std::vector<CString> EndEncryptEx(const char * key, CString strData_in);
	CString EndDecryptEx(const char * key, CString strData_in);
	ExcelClass m_Excel;
	afx_msg void OnBnClickedButtonQuery();
	CString cArray_unsignedcArray(char * data);
};
