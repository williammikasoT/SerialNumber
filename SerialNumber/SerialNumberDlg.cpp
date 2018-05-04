
// SerialNumberDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSerialNumberDlg 对话框



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


// CSerialNumberDlg 消息处理程序

BOOL CSerialNumberDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CEdit* m_Edit = (CEdit*)GetDlgItem(IDC_EDIT_KEY);       // 设置edit内输入的长度
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
	// 级别
	GetDlgItem(IDC_EDIT_LEVEL)->SetWindowText("12345678");
	// 名字
	GetDlgItem(IDC_EDIT_NAME)->SetWindowText("affff444555");
	// excel初始化
	m_Excel.InitExcel();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSerialNumberDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
* 加密
* return@ 1.乱码 2.十六进制
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
	// TODO: 在此添加控件通知处理程序代码
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

	// 加密
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
	

	// 解密
	char *pkey = "f983efe624b8ffc3";

	//char*data_in = (char*)vStr[i].GetBuffer(0);
	//End_Decrypt(pEncrypt_key, pkey, data_out);
	//strTmp = cArray_unsignedcArray(data_out);

	// 把liunx程序拷给过来解析数据

	//CString strDectrpt =  EndDecryptEx(pEncrypt_key, vStr[0]);
	//GetDlgItem(IDC_EDIT_TEST)->SetWindowText(strDectrpt);


	// 保存数据
	//strLevel = "'" + strLevel;
	//std::vector<CString> vData;
	//vData.push_back(strKey);
	//vData.push_back(strID);
	//vData.push_back(strLevel);
	//vData.push_back(vStr[0]);
	//vData.push_back(vStr[1]);
	//vData.push_back(strDectrpt);

	//m_Excel.WriteExcel(vData,"\\模版.xlsx",TRUE);
	//Sleep(500);
}



void CSerialNumberDlg::OnBnClickedButtonQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(0, _T("open"), "模版.xlsx", NULL, NULL, SW_NORMAL);
}


