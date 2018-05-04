
// SerialNumberDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SerialNumber.h"
#include "SerialNumberDlg.h"
#include "afxdialogex.h"
#include "PUClass.h"
#include "DES-Decrypt.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSerialNumberDlg �Ի���



CSerialNumberDlg::CSerialNumberDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALNUMBER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSerialNumberDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CSerialNumberDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &CSerialNumberDlg::OnBnClickedButtonQuery)
END_MESSAGE_MAP()


// CSerialNumberDlg ��Ϣ�������

BOOL CSerialNumberDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CEdit* m_Edit = (CEdit*)GetDlgItem(IDC_EDIT_KEY);       // ����edit������ĳ���
	m_Edit->SetLimitText(24);
	m_Edit = (CEdit*)GetDlgItem(IDC_EDIT_CPU_ID);       
	m_Edit->SetLimitText(16);
	m_Edit = (CEdit*)GetDlgItem(IDC_EDIT_LEVEL);
	m_Edit->SetLimitText(8);

	
	// key
	GetDlgItem(IDC_EDIT_KEY)->SetWindowText("HZXXCONTROLSYSTEMNAMEICL");
	// cpu id
	CPUClass cpuc;
	CString strCPU = cpuc.ReadCPU();
	GetDlgItem(IDC_EDIT_CPU_ID)->SetWindowText(strCPU);
	// ����
	GetDlgItem(IDC_EDIT_LEVEL)->SetWindowText("12345678");
	// ����
	GetDlgItem(IDC_EDIT_NAME)->SetWindowText("affff444555");
	// excel��ʼ��
	m_Excel.InitExcel();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSerialNumberDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSerialNumberDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSerialNumberDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString CSerialNumberDlg::ArrayByCString(char * data)
{
	CString strData;
	for (int i = 0; i< 8; i++)
	{
		strData += data[i];
	}
	return strData;
}

CString CSerialNumberDlg::cArray_unsignedcArray(char * data)
{
	char buf[12],buf_data[24];
	unsigned char unsigData[8];
	unsigned char a;
	char b;
	CString str,strT;

	for (int i = 0; i<8; i++)
	{
		b = data[i];
		a = (unsigned char)b;
		unsigData[i] = a;
		sprintf_s(buf, "%02x", unsigData[i]);
  		strT = buf;
		//strT += ",";
		str += strT;
	}

	
	return str;
}


/*
* ����
* return@ 1.���� 2.ʮ������
*/
std::vector<CString> CSerialNumberDlg::EndEncryptEx(const char * key, CString strData_in)
{
	CString str, strArrayData, strTmp;
	char data_out[8];
	std::vector<CString>	vStr, vData;
	vStr.push_back(strData_in.Left(8));
	vStr.push_back(strData_in.Mid(8, 8));
	vStr.push_back(strData_in.Right(8));
	for (int i = 0; i < 3; i++)
	{
		char*data_in = (char*)vStr[i].GetBuffer(0);
		End_Encrypt(key, data_in, data_out);
		strTmp = cArray_unsignedcArray(data_out);
		strArrayData += strTmp;
		str += ArrayByCString(data_out);
	}
	vData.push_back(str);
	vData.push_back(strArrayData);
	return vData;
}

CString CSerialNumberDlg::EndDecryptEx(const char * key, CString strData_in)
{
	CString str;
	char data_out[8];
	std::vector<CString>	vStr;
	vStr.push_back(strData_in.Left(8));
	vStr.push_back(strData_in.Mid(8, 8));
	vStr.push_back(strData_in.Right(8));
	
	for (int i = 0; i < 3; i++)
	{
		char*data_in = (char*)vStr[i].GetBuffer(0);
		End_Decrypt(key, data_in, data_out);
		str += ArrayByCString(data_out);
	}

	return str;
}


void CSerialNumberDlg::OnBnClickedButtonCreate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_SERIAL_NUMBER)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_TEST)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_HEX)->EnableWindow(1);
	
	CString strKey,strID,strLevel,strSerial,strName;
	GetDlgItem(IDC_EDIT_KEY)->GetWindowText(strKey);
	GetDlgItem(IDC_EDIT_CPU_ID)->GetWindowText(strID);
	GetDlgItem(IDC_EDIT_LEVEL)->GetWindowText(strLevel);
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(strName);

	USES_CONVERSION;
	char *pEncrypt_key = T2A(strKey.GetBuffer(0));
	// id + serial == 16 + 8 == 24
	strSerial = strID + strLevel;

	// ����
	std::vector<CString> vStr = EndEncryptEx(pEncrypt_key, strSerial);
	GetDlgItem(IDC_EDIT_SERIAL_NUMBER)->SetWindowText(vStr[0]);
	//GetDlgItem(IDC_EDIT_HEX)->SetWindowText(vStr[1]);


	char data_out[9];
	CString strTmp,strLongName;
	if (!strName.IsEmpty())
	{
		int len = strName.GetLength();
		int iF = len / 8;
		int iY = len % 8;
		strTmp = strName;
		if (iF>0)
		{	
			for (int i = 0; i < iF; i++)
			{
				strTmp = strTmp.Left(8);
				char*data_in = (char*)strTmp.GetBuffer(0);
				End_Encrypt(pEncrypt_key, data_in, data_out);
				strTmp = cArray_unsignedcArray(data_out);
				strLongName += strTmp;
				strTmp = strTmp.Right(len - 8);
				len = len - 8;
			}
			char*data_in = (char*)strTmp.GetBuffer(0);
			End_Encrypt(pEncrypt_key, data_in, data_out);
			strTmp = cArray_unsignedcArray(data_out);
			strTmp = strTmp.Left(iY * 2);
			strTmp = strLongName + strTmp;

		}
		else if (iF == 0)
		{
			char*data_in = (char*)strName.GetBuffer(0);
			End_Encrypt(pEncrypt_key, data_in, data_out);
			strTmp = cArray_unsignedcArray(data_out);
			strTmp = strTmp.Left(len*2);
		}
	}
	strTmp =vStr[1] + strTmp;
	GetDlgItem(IDC_EDIT_HEX)->SetWindowText(strTmp);
	

	// ����
	char *pkey = "f983efe624b8ffc3";

	//char*data_in = (char*)vStr[i].GetBuffer(0);
	//End_Decrypt(pEncrypt_key, pkey, data_out);
	//strTmp = cArray_unsignedcArray(data_out);

	// ��liunx���򿽸�������������

	//CString strDectrpt =  EndDecryptEx(pEncrypt_key, vStr[0]);
	//GetDlgItem(IDC_EDIT_TEST)->SetWindowText(strDectrpt);


	// ��������
	//strLevel = "'" + strLevel;
	//std::vector<CString> vData;
	//vData.push_back(strKey);
	//vData.push_back(strID);
	//vData.push_back(strLevel);
	//vData.push_back(vStr[0]);
	//vData.push_back(vStr[1]);
	//vData.push_back(strDectrpt);

	//m_Excel.WriteExcel(vData,"\\ģ��.xlsx",TRUE);
	//Sleep(500);
}



void CSerialNumberDlg::OnBnClickedButtonQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(0, _T("open"), "ģ��.xlsx", NULL, NULL, SW_NORMAL);
}


