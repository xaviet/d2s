
// d2sDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "d2s.h"
#include "d2sDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cd2sDlg �Ի���



Cd2sDlg::Cd2sDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(IDD_D2S_DIALOG, pParent)
  , m_path(_T(""))
  , mp_d2sData(NULL)
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


// Cd2sDlg ��Ϣ�������

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

CString  Cd2sDlg::stringDisp(unsigned char* vp_buffer, int v_length)
{
  CString t_cs = CString((char*)vp_buffer);
  return t_cs;
}

CString Cd2sDlg::checkSum(struct s_d2sFormat* vp_buffer, int v_length)
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

  // ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
  //  ִ�д˲���
  SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
  SetIcon(m_hIcon, FALSE);		// ����Сͼ��

  // TODO: �ڴ���Ӷ���ĳ�ʼ������

  m_path = _T("C:\\code\\Visual C++ ��Ŀ\\d2s\\d2s\\ToeA.d2s");
  UpdateData(FALSE);
  d2sParser(m_path);

  return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cd2sDlg::OnPaint()
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
HCURSOR Cd2sDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

void Cd2sDlg::OnBnClickedButton2()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  CString t_defaultDir = _T("../");   //Ĭ�ϴ򿪵��ļ�·��  
  CString t_filter = _T("�ļ� (*.d2s)|*.d2s||");   //�ļ����ǵ�����  
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
  mp_d2sData = (struct s_d2sFormat*)malloc(DEF_bufferLength);
  memset(mp_d2sData, 0, DEF_bufferLength);
  m_d2sDataSize = t_csf.Read(mp_d2sData, DEF_bufferLength);
  t_csf.Close();
  m_flag = hexDisp((unsigned char*)&mp_d2sData->m_flag, 4);
  m_ver = hexDisp((unsigned char*)&mp_d2sData->m_ver, 4);
  m_size = hexDisp((unsigned char*)&mp_d2sData->m_size, 4);
  m_checkSum = hexDisp((unsigned char*)&mp_d2sData->m_checkSum, 4);
  memset(&mp_d2sData->m_checkSum, 0, 4);
  m_activeW = hexDisp((unsigned char*)&mp_d2sData->m_activeW, 4);
  m_name = stringDisp((unsigned char*)mp_d2sData->m_name, 16);
  m_status = hexDisp((unsigned char*)&mp_d2sData->m_status, 1);
  m_progression = hexDisp((unsigned char*)&mp_d2sData->m_progression, 1);
  m_class = hexDisp((unsigned char*)&mp_d2sData->m_class, 1);
  m_level = decDisp((int)mp_d2sData->m_level);
  m_difficulty = hexDisp((unsigned char*)&mp_d2sData->m_difficulty, 3);
  m_wayPoint = hexDisp((unsigned char*)&mp_d2sData->m_wayPoint, 81);
  m_stat = hexDisp((unsigned char*)&mp_d2sData->m_stat, mp_d2sData->m_size - sizeof(struct s_d2sFormat) + 4);
  m_time = decDisp((int)mp_d2sData->m_time);

  m_temp = hexDisp((unsigned char*)&mp_d2sData->m_stat, 64);
  UpdateData(FALSE);
  return 0;
}

void Cd2sDlg::OnBnClickedOk()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  CStdioFile t_csf;
  checkSum(mp_d2sData, m_d2sDataSize);
  t_csf.Open(m_path, CFile::modeWrite | CFile::typeBinary);
  t_csf.Write(mp_d2sData, ((struct s_d2sFormat*)mp_d2sData)->m_size);
  t_csf.Close();
  CDialogEx::OnOK();
}

void Cd2sDlg::OnEnChangeEdit7()
{
  // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
  // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
  // ���������� CRichEditCtrl().SetEventMask()��
  // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

  // TODO:  �ڴ���ӿؼ�֪ͨ����������
  memset(mp_d2sData->m_name, 0, 16);
  UpdateData(TRUE);
}


void Cd2sDlg::OnEnChangeEdit8()
{
  // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
  // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
  // ���������� CRichEditCtrl().SetEventMask()��
  // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

  // TODO:  �ڴ���ӿؼ�֪ͨ����������
  UpdateData(TRUE);
  mp_d2sData->m_status = (unsigned char)_tcstol(m_status, NULL, 16);
}


void Cd2sDlg::OnEnChangeEdit10()
{
  // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
  // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
  // ���������� CRichEditCtrl().SetEventMask()��
  // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

  // TODO:  �ڴ���ӿؼ�֪ͨ����������
  UpdateData(TRUE);
  mp_d2sData->m_class = (unsigned char)_tcstol(m_class, NULL, 16);
}


void Cd2sDlg::OnEnChangeEdit11()
{
  // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
  // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
  // ���������� CRichEditCtrl().SetEventMask()��
  // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

  // TODO:  �ڴ���ӿؼ�֪ͨ����������
  UpdateData(TRUE);
  mp_d2sData->m_level = (unsigned char)_tcstol(m_level, NULL, 10);
}


void Cd2sDlg::OnBnClickedCheck1()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  UpdateData(TRUE);
  if (m_wpEnable)
  {
    for (int t_i = 10; t_i <= 58; t_i += 24)
    {

      mp_d2sData->m_wayPoint[t_i] = 0xff;
      mp_d2sData->m_wayPoint[t_i + 1] = 0xff;
      mp_d2sData->m_wayPoint[t_i + 2] = 0xff;
      mp_d2sData->m_wayPoint[t_i + 3] = 0xff;
      mp_d2sData->m_wayPoint[t_i + 4] = 0x7f;
    }
  }
  else
  {
    for (int t_i = 10; t_i <= 58; t_i += 24)
    {

      mp_d2sData->m_wayPoint[t_i] = 0x01;
      mp_d2sData->m_wayPoint[t_i + 1] = 0x00;
      mp_d2sData->m_wayPoint[t_i + 2] = 0x00;
      mp_d2sData->m_wayPoint[t_i + 3] = 0x00;
      mp_d2sData->m_wayPoint[t_i + 4] = 0x00;
    }
  }
  m_wayPoint = hexDisp((unsigned char*)&mp_d2sData->m_wayPoint, 81);
  UpdateData(FALSE);
}


void Cd2sDlg::OnBnClickedCheck2()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  UpdateData(TRUE);
  if (m_forge)
  {
    mp_d2sData->m_quest[16] = (mp_d2sData->m_quest[16] & 0xfc) + 0x2;
  }
}


void Cd2sDlg::OnBnClickedButton1()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  UpdateData(TRUE);
  unsigned char t_ch = (unsigned char)_tcstol(m_byte, NULL, 16);
  m_result = _T("");
  unsigned char* tp_ch = (unsigned char*)mp_d2sData;
  for (int t_i = 0; t_i < mp_d2sData->m_size; t_i++)
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
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  m_result = _T("");
  CString t_defaultDir = _T("../");   //Ĭ�ϴ򿪵��ļ�·��  
  CString t_filter = _T("�ļ� (*.d2s)|*.d2s||");   //�ļ����ǵ�����  
  CString t_path = _T("");
  CFileDialog openFileDlg(TRUE, t_defaultDir, t_path, OFN_HIDEREADONLY | OFN_READONLY, t_filter, NULL);
  INT_PTR t_result = openFileDlg.DoModal();
  unsigned char t_data[DEF_bufferLength] = { 0 };
  memset(t_data, 0, DEF_bufferLength);
  int t_len = 0;
  unsigned char* tp_ch1 = (unsigned char*)mp_d2sData;
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
