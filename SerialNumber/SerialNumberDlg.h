
// SerialNumberDlg.h : ͷ�ļ�
//

#include"ExcelClass\ExcelClass.h"
#pragma once

// ������������ʹ��


// CSerialNumberDlg �Ի���
class CSerialNumberDlg : public CDialogEx
{
// ����
public:
	CSerialNumberDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALNUMBER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
