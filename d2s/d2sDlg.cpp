
// d2sDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "d2s.h"
#include "d2sDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cd2sDlg 对话框



Cd2sDlg::Cd2sDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(IDD_D2S_DIALOG, pParent)
  , m_path(_T(""))
  , mp_d2sGeneralData(NULL)
  , m_d2sDataSize(0)
  , m_flag(_T(""))
  , m_ver(_T(""))
  , m_size(_T(""))
  , m_checkSum(_T(""))
  , m_activeW(_T(""))
  , m_name(_T(""))
  , m_status(_T(""))
  , m_progression(_T(""))
  , m_class(_T(""))
  , m_level(_T(""))
  , m_difficulty(_T(""))
  , m_wayPoint(_T(""))
  , m_stat(_T(""))
  , m_wpEnable(FALSE)
  , m_temp(_T(""))
  , m_time(_T(""))
  , m_forge(FALSE)
  , m_byte(_T(""))
  , m_result(_T(""))
  , m_stat00(_T(""))
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cd2sDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, m_path);
  DDV_MaxChars(pDX, m_path, 255);
  DDX_Text(pDX, IDC_EDIT2, m_flag);
  DDX_Text(pDX, IDC_EDIT3, m_ver);
  DDX_Text(pDX, IDC_EDIT4, m_size);
  DDX_Text(pDX, IDC_EDIT5, m_checkSum);
  DDX_Text(pDX, IDC_EDIT6, m_activeW);
  DDX_Text(pDX, IDC_EDIT7, m_name);
  DDV_MaxChars(pDX, m_name, 16);
  DDX_Text(pDX, IDC_EDIT8, m_status);
  DDV_MaxChars(pDX, m_status, 2);
  DDX_Text(pDX, IDC_EDIT9, m_progression);
  DDX_Text(pDX, IDC_EDIT10, m_class);
  DDV_MaxChars(pDX, m_class, 2);
  DDX_Text(pDX, IDC_EDIT11, m_level);
  DDV_MaxChars(pDX, m_level, 2);
  DDX_Text(pDX, IDC_EDIT12, m_difficulty);
  DDX_Text(pDX, IDC_EDIT13, m_wayPoint);
  DDX_Text(pDX, IDC_EDIT14, m_stat);
  DDX_Check(pDX, IDC_CHECK1, m_wpEnable);
  DDX_Text(pDX, IDC_EDIT15, m_temp);
  DDX_Text(pDX, IDC_EDIT16, m_time);
  DDX_Check(pDX, IDC_CHECK2, m_forge);
  DDX_Text(pDX, IDC_EDIT17, m_byte);
  DDX_Text(pDX, IDC_EDIT18, m_result);
  DDX_Text(pDX, IDC_EDIT19, m_stat00);
}

BEGIN_MESSAGE_MAP(Cd2sDlg, CDialogEx)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUTTON2, &Cd2sDlg::OnBnClickedButton2)
  ON_BN_CLICKED(IDOK, &Cd2sDlg::OnBnClickedOk)
  ON_EN_CHANGE(IDC_EDIT7, &Cd2sDlg::OnEnChangeEdit7)
  ON_EN_CHANGE(IDC_EDIT8, &Cd2sDlg::OnEnChangeEdit8)
  ON_EN_CHANGE(IDC_EDIT10, &Cd2sDlg::OnEnChangeEdit10)
  ON_EN_CHANGE(IDC_EDIT11, &Cd2sDlg::OnEnChangeEdit11)
  ON_BN_CLICKED(IDC_CHECK1, &Cd2sDlg::OnBnClickedCheck1)
  ON_BN_CLICKED(IDC_CHECK2, &Cd2sDlg::OnBnClickedCheck2)
  ON_BN_CLICKED(IDC_BUTTON1, &Cd2sDlg::OnBnClickedButton1)
  ON_BN_CLICKED(IDC_BUTTON3, &Cd2sDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Cd2sDlg 消息处理程序

CString Cd2sDlg::hexDisp(unsigned char* vp_buffer, int v_length)
{
  CString t_cs = _T("");
  for (int t_i = 0; t_i < v_length; t_i++)
  {
    if (t_i % 8 == 0)
    {
      t_cs.Format(_T("%s "), t_cs, _T(" "));
    }
    t_cs.Format(_T("%s %02X"), t_cs, *vp_buffer++);
  }
  t_cs.Trim();
  return t_cs;
}

CString Cd2sDlg::decDisp(int v_i)
{
  CString t_cs = _T("");
  t_cs.Format(_T("%d"), v_i);
  t_cs.Trim();
  return t_cs;
}

CString Cd2sDlg::stringDisp(unsigned char* vp_buffer, int v_length)
{
  CString t_cs = CString((char*)vp_buffer);
  return t_cs;
}

int Cd2sDlg::getBits(unsigned char* vp_buffer, int v_start, int v_length)
{
  unsigned int t_rt = 0;
  unsigned char* t_ch = vp_buffer + v_start / 8;
  t_rt = *(t_ch++) >> (v_start % 8);
  for (int t_i = 0; t_i < ((v_length - (8 - v_start % 8)) / 8); t_i++)
  {
    t_rt += *(t_ch++);
  }
  t_rt += *(t_ch++) >> (((v_length - (8 - v_start % 8)) % 8));
  return(t_rt);
}

void Cd2sDlg::setBits(unsigned char* vp_buffer, int v_start, int v_length, unsigned int v_value)
{

}

CString Cd2sDlg::checkSum(struct s_d2sGeneralFormat* vp_buffer, int v_length)
{
  int t_sum = 0;
  unsigned char* t_ch = (unsigned char*)vp_buffer;
  for (int t_i = 0; t_i < v_length; t_i++)
  {
    t_sum = (t_sum << 1) + (t_sum < 0) + *t_ch++;
  }
  vp_buffer->m_checkSum = t_sum;
  return hexDisp((unsigned char*)&t_sum, 4);
}

BOOL Cd2sDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
  //  执行此操作
  SetIcon(m_hIcon, TRUE);			// 设置大图标
  SetIcon(m_hIcon, FALSE);		// 设置小图标

  // TODO: 在此添加额外的初始化代码

  m_path = _T(DEF_defaultPath);
  UpdateData(FALSE);
  d2sParser(m_path);

  return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cd2sDlg::OnPaint()
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
HCURSOR Cd2sDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

void Cd2sDlg::OnBnClickedButton2()
{
  // TODO: 在此添加控件通知处理程序代码
  CString t_defaultDir = _T("../");   //默认打开的文件路径  
  CString t_filter = _T("文件 (*.d2s)|*.d2s||");   //文件过虑的类型  
  CFileDialog openFileDlg(TRUE, t_defaultDir, m_path, OFN_HIDEREADONLY | OFN_READONLY, t_filter, NULL);
  INT_PTR t_result = openFileDlg.DoModal();
  if (t_result == IDOK)
  {
    m_path = openFileDlg.GetPathName();
    UpdateData(FALSE);
    d2sParser(m_path);
  }
}

int Cd2sDlg::d2sParser(CString v_path)
{
  CStdioFile t_csf;
  t_csf.Open(v_path, CFile::modeRead | CFile::typeBinary);
  mp_d2sGeneralData = (struct s_d2sGeneralFormat*)malloc(DEF_bufferLength);
  memset(mp_d2sGeneralData, 0, DEF_bufferLength);
  m_d2sDataSize = t_csf.Read(mp_d2sGeneralData, DEF_bufferLength);
  t_csf.Close();
  m_flag = hexDisp((unsigned char*)&mp_d2sGeneralData->m_flag, 4);
  m_ver = hexDisp((unsigned char*)&mp_d2sGeneralData->m_ver, 4);
  m_size = hexDisp((unsigned char*)&mp_d2sGeneralData->m_size, 4);
  m_checkSum = hexDisp((unsigned char*)&mp_d2sGeneralData->m_checkSum, 4);
  memset(&mp_d2sGeneralData->m_checkSum, 0, 4);
  m_activeW = hexDisp((unsigned char*)&mp_d2sGeneralData->m_activeW, 4);
  m_name = stringDisp((unsigned char*)mp_d2sGeneralData->m_name, 16);
  m_status = hexDisp((unsigned char*)&mp_d2sGeneralData->m_status, 1);
  m_progression = hexDisp((unsigned char*)&mp_d2sGeneralData->m_progression, 1);
  m_class = hexDisp((unsigned char*)&mp_d2sGeneralData->m_class, 1);
  m_level = decDisp((int)mp_d2sGeneralData->m_level);
  m_difficulty = hexDisp((unsigned char*)&mp_d2sGeneralData->m_difficulty, 3);
  m_wayPoint = hexDisp((unsigned char*)&mp_d2sGeneralData->m_wayPoint, 81);
  m_time = decDisp((int)mp_d2sGeneralData->m_time);
  m_stat = hexDisp((unsigned char*)((int)mp_d2sGeneralData + sizeof(struct s_d2sGeneralFormat)), mp_d2sGeneralData->m_size - sizeof(struct s_d2sGeneralFormat) + 4);
  m_d2sStatData.m_statHead = *(UINT16*)((int)mp_d2sGeneralData + sizeof(struct s_d2sGeneralFormat));
  m_d2sStatData.mp_stat = (unsigned char*)((int)mp_d2sGeneralData + sizeof(struct s_d2sGeneralFormat) + sizeof(m_d2sStatData.m_statHead));

  m_temp = hexDisp((unsigned char*)((int)mp_d2sGeneralData + sizeof(struct s_d2sGeneralFormat)), 56);
  UpdateData(FALSE);
  return 0;
}

void Cd2sDlg::OnBnClickedOk()
{
  // TODO: 在此添加控件通知处理程序代码
  CStdioFile t_csf;
 
  checkSum(mp_d2sGeneralData, m_d2sDataSize);
  t_csf.Open(m_path, CFile::modeWrite | CFile::typeBinary);
  t_csf.Write(mp_d2sGeneralData, ((struct s_d2sGeneralFormat*)mp_d2sGeneralData)->m_size);
  t_csf.Close();
  CDialogEx::OnOK();
}

void Cd2sDlg::OnEnChangeEdit7()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  memset(mp_d2sGeneralData->m_name, 0, 16);
  UpdateData(TRUE);
}


void Cd2sDlg::OnEnChangeEdit8()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  UpdateData(TRUE);
  mp_d2sGeneralData->m_status = (unsigned char)_tcstol(m_status, NULL, 16);
}


void Cd2sDlg::OnEnChangeEdit10()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  UpdateData(TRUE);
  mp_d2sGeneralData->m_class = (unsigned char)_tcstol(m_class, NULL, 16);
}


void Cd2sDlg::OnEnChangeEdit11()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 CDialogEx::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
  UpdateData(TRUE);
  mp_d2sGeneralData->m_level = (unsigned char)_tcstol(m_level, NULL, 10);
}


void Cd2sDlg::OnBnClickedCheck1()
{
  // TODO: 在此添加控件通知处理程序代码
  UpdateData(TRUE);
  if (m_wpEnable)
  {
    for (int t_i = 10; t_i <= 58; t_i += 24)
    {

      mp_d2sGeneralData->m_wayPoint[t_i] = 0xff;
      mp_d2sGeneralData->m_wayPoint[t_i + 1] = 0xff;
      mp_d2sGeneralData->m_wayPoint[t_i + 2] = 0xff;
      mp_d2sGeneralData->m_wayPoint[t_i + 3] = 0xff;
      mp_d2sGeneralData->m_wayPoint[t_i + 4] = 0x7f;
    }
  }
  else
  {
    for (int t_i = 10; t_i <= 58; t_i += 24)
    {

      mp_d2sGeneralData->m_wayPoint[t_i] = 0x01;
      mp_d2sGeneralData->m_wayPoint[t_i + 1] = 0x00;
      mp_d2sGeneralData->m_wayPoint[t_i + 2] = 0x00;
      mp_d2sGeneralData->m_wayPoint[t_i + 3] = 0x00;
      mp_d2sGeneralData->m_wayPoint[t_i + 4] = 0x00;
    }
  }
  m_wayPoint = hexDisp((unsigned char*)&mp_d2sGeneralData->m_wayPoint, 81);
  UpdateData(FALSE);
}


void Cd2sDlg::OnBnClickedCheck2()
{
  // TODO: 在此添加控件通知处理程序代码
  UpdateData(TRUE);
  if (m_forge)
  {
    mp_d2sGeneralData->m_quest[16] = (mp_d2sGeneralData->m_quest[16] & 0xfc) + 0x2;
  }
}


void Cd2sDlg::OnBnClickedButton1()
{
  // TODO: 在此添加控件通知处理程序代码
  UpdateData(TRUE);
  unsigned char t_ch = (unsigned char)_tcstol(m_byte, NULL, 16);
  m_result = _T("");
  unsigned char* tp_ch = (unsigned char*)mp_d2sGeneralData;
  for (int t_i = 0; t_i < mp_d2sGeneralData->m_size; t_i++)
  {
    if (t_ch == *(tp_ch++))
    {
      m_result.Format(_T("%s %d"), m_result, t_i);
    }
  }
  m_result.Trim();
  UpdateData(FALSE);
}


void Cd2sDlg::OnBnClickedButton3()
{
  // TODO: 在此添加控件通知处理程序代码
  m_result = _T("");
  CString t_defaultDir = _T("../");   //默认打开的文件路径  
  CString t_filter = _T("文件 (*.d2s)|*.d2s||");   //文件过虑的类型  
  CString t_path = _T("");
  CFileDialog openFileDlg(TRUE, t_defaultDir, t_path, OFN_HIDEREADONLY | OFN_READONLY, t_filter, NULL);
  INT_PTR t_result = openFileDlg.DoModal();
  unsigned char t_data[DEF_bufferLength] = { 0 };
  memset(t_data, 0, DEF_bufferLength);
  int t_len = 0;
  unsigned char* tp_ch1 = (unsigned char*)mp_d2sGeneralData;
  unsigned char* tp_ch2 = (unsigned char*)t_data;
  if (t_result == IDOK)
  {
    t_path = openFileDlg.GetPathName();
    CStdioFile t_csf;
    t_csf.Open(t_path, CFile::modeRead | CFile::typeBinary);
    t_len = t_csf.Read(t_data, DEF_bufferLength);
    t_csf.Close();
    int t_max = (t_len > m_d2sDataSize) ? t_len : m_d2sDataSize;
    for (int t_i = 0; t_i < t_max; t_i++)
    {
      if (*(tp_ch1++) != *(tp_ch2++))
      {
        m_result.Format(_T("%s %d"), m_result, t_i);
      }
    }
    m_result.Trim();
    UpdateData(FALSE);
  }
}
