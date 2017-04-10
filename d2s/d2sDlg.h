
// d2sDlg.h : 头文件
//

#pragma once
#pragma pack(1)

#define DEF_defaultPath "C:\\code\\Visual C++ 项目\\d2s\\d2s\\ToeN.d2s"
//#define DEF_defaultPath "D:\\code\\Visual C++ Project\\d2s\\d2s\\ToeA.d2s"
#define DEF_bufferLength 0x80000
#define DEF_statNumber 0x10
#define DEF_statLength {10,10,10,10,10,8,21,21,21,21,21,21,7,32,25,25}

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
  int m_start;
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
  struct s_d2sStatFormat m_d2sStatData[DEF_statNumber];
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
  unsigned char getBit(unsigned char*, int);
  unsigned int getBits(unsigned char*, int, int);
  void setBit(unsigned char*, int, int);
  void setBits(unsigned char*, int, int, unsigned int);
  CString m_stat01;
  CString m_stat02;
  CString m_stat03;
  CString m_stat04;
  CString m_stat05;
  CString m_stat06;
  CString m_stat07;
  CString m_stat08;
  CString m_stat09;
  CString m_stat10;
  CString m_stat11;
  CString m_stat12;
  CString m_stat13;
  CString m_stat14;
  CString m_stat15;
  void saveD2sData();
  afx_msg void OnEnChangeEdit24();
  unsigned char* m_statBuffer;
  unsigned char* m_itemBuffer;
  afx_msg void OnEnChangeEdit23();
  afx_msg void OnEnChangeEdit33();
  afx_msg void OnEnChangeEdit34();
  CString m_item;
  CString m_itemFile;
  afx_msg void OnBnClickedButton4();
  CString m_itemFilePath;
  unsigned char m_itemFileData[DEF_bufferLength];
  int m_itemFileLength;

  afx_msg void OnBnClickedButton5();
  BOOL m_mfFlag;
  afx_msg void OnBnClickedCheck3();
};
