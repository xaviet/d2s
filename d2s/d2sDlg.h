
// d2sDlg.h : 头文件
//

#pragma once
#pragma pack(1)

//#define DEF_defaultPath "C:\\code\\Visual C++ 项目\\d2s\\d2s\\ToeA.d2s"
#define DEF_defaultPath "D:\\code\\Visual C++ Project\\d2s\\d2s\\ToeA.d2s"
#define DEF_bufferLength 0x80000

struct s_d2sGeneralFormat
{
  int m_flag;
  int m_ver;
  int m_size;
  int m_checkSum;
  int m_activeW;
  unsigned char m_name[16];
  unsigned char m_status;
  unsigned char m_progression;
  UINT16 m_pad1;
  unsigned char m_class;
  UINT16 m_pad2;
  unsigned char m_level;
  int m_pad3;
  int m_time;
  int m_pad4;
  unsigned char m_pad5[64];
  int m_lMouse;
  int m_rMouse;
  int m_lMouseSw;
  int m_rMouseSw;
  unsigned char m_pad6[32];
  unsigned char m_difficulty[3];
  int m_map;
  UINT16 m_pad7;
  UINT16 m_mercD;
  int m_mercS;
  UINT16 m_mercN;
  UINT16 m_mercT;
  int m_mercE;
  unsigned char m_pad8[144];
  unsigned char m_quest[298];
  unsigned char m_wayPoint[81];
  unsigned char m_npc[51];
};

struct s_d2sStatFormat
{
  UINT16 m_statHead;
  unsigned char* mp_stat;
  int m_length;
};

// Cd2sDlg 对话框
class Cd2sDlg : public CDialogEx
{
// 构造
public:
	Cd2sDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D2S_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
  struct s_d2sGeneralFormat* mp_d2sGeneralData;
  struct s_d2sStatFormat m_d2sStatData;
  int m_d2sDataSize;
  CString hexDisp(unsigned char*, int);
  CString decDisp(int);
  CString stringDisp(unsigned char*, int);
  CString checkSum(struct s_d2sGeneralFormat*, int);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  CString m_path;
  afx_msg void OnBnClickedButton2();
  int d2sParser(CString);
  CString m_flag;
  CString m_ver;
  CString m_size;
  CString m_checkSum;
  afx_msg void OnBnClickedOk();
  CString m_activeW;
  CString m_name;
  afx_msg void OnEnChangeEdit7();
  CString m_status;
  afx_msg void OnEnChangeEdit8();
  CString m_progression;
  CString m_class;
  afx_msg void OnEnChangeEdit10();
  CString m_level;
  afx_msg void OnEnChangeEdit11();
  CString m_difficulty;
  CString m_wayPoint;
  CString m_stat;
  afx_msg void OnBnClickedCheck1();
  BOOL m_wpEnable;
  CString m_temp;
  CString m_time;
  BOOL m_forge;
  afx_msg void OnBnClickedCheck2();
  CString m_byte;
  CString m_result;
  afx_msg void OnBnClickedButton1();
  afx_msg void OnBnClickedButton3();
  CString m_stat00;
  int getBits(unsigned char*, int, int);
  void setBits(unsigned char*, int, int, unsigned int);
};
