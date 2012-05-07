// IMAGEMATCHOnSIFTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IMAGEMATCHOnSIFT.h"
#include "IMAGEMATCHOnSIFTDlg.h"
#include "ShowImgDlg.h"
#include "DlgMClose.h"

#include "sift\siftdll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIMAGEMATCHOnSIFTDlg dialog

CIMAGEMATCHOnSIFTDlg::CIMAGEMATCHOnSIFTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIMAGEMATCHOnSIFTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIMAGEMATCHOnSIFTDlg)
	m_sltImg1 = _T("");
	m_sltImg2 = _T("");
	m_gws = -1;
	m_bd = -1;
	m_sdr = -1;
	m_mt = -1;
	m_is = _T("");
	m_cd = _T("");
	m_miniRes = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//
	/*初始化成员变量值*/
	m_imgdata1 = m_imgdata2 = NULL;		//存放图像数据，包括头信息和结构信息等
	m_orgdata1 = m_orgdata2 = NULL;		//存放RGB数据
	//	m_newdata = NULL;
	m_img1path = "";
	m_img2path = "";
	m_graydata1 = NULL;
	m_graydata2 = NULL;
	matchedcos = NULL;
	featVect1 = NULL;
	featVect2 = NULL;
}

void CIMAGEMATCHOnSIFTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIMAGEMATCHOnSIFTDlg)
	DDX_Control(pDX, IDC_COMBOMINIRES, m_COMBOMiniRes);
	DDX_Control(pDX, IDC_EDITCD, m_EDITCD);
	DDX_Control(pDX, IDC_SLIDERCD, m_SLIDERCD);
	DDX_Control(pDX, IDC_EDITIS, m_EDITIS);
	DDX_Control(pDX, IDC_SLIDERIS, m_SLIDERIS);
	DDX_Control(pDX, IDC_EDITSELECTIMG2, m_EDITSLTIMG2);
	DDX_Control(pDX, IDC_EDITSELECTIMG1, m_EDITSLTIMG1);
	DDX_Control(pDX, IDC_COMBOMT, m_COMBOMT);
	DDX_Control(pDX, IDC_COMBOSDR, m_COMBOSDR);
	DDX_Control(pDX, IDC_COMBOBD, m_COMBOBD);
	DDX_Control(pDX, IDC_COMBOGWS, m_COMBOGWS);
	DDX_Text(pDX, IDC_EDITSELECTIMG1, m_sltImg1);
	DDX_Text(pDX, IDC_EDITSELECTIMG2, m_sltImg2);
	DDX_CBIndex(pDX, IDC_COMBOGWS, m_gws);
	DDX_CBIndex(pDX, IDC_COMBOBD, m_bd);
	DDX_CBIndex(pDX, IDC_COMBOSDR, m_sdr);
	DDX_CBIndex(pDX, IDC_COMBOMT, m_mt);
	DDX_Text(pDX, IDC_EDITIS, m_is);
	DDX_Text(pDX, IDC_EDITCD, m_cd);
	DDX_CBIndex(pDX, IDC_COMBOMINIRES, m_miniRes);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIMAGEMATCHOnSIFTDlg, CDialog)
	//{{AFX_MSG_MAP(CIMAGEMATCHOnSIFTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSELECTIMG1, OnButtonselectimg1)
	ON_BN_CLICKED(IDC_BUTTONSELECTIMG2, OnButtonselectimg2)
	ON_EN_MAXTEXT(IDC_EDITSELECTIMG1, OnMaxtextEditselectimg1)
	ON_EN_MAXTEXT(IDC_EDITSELECTIMG2, OnMaxtextEditselectimg2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERIS, OnCustomdrawSlideris)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERCD, OnCustomdrawSlidercd)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONSHOWIMG, static_cast<void>(OnButtonshowimg))
	ON_BN_CLICKED(IDC_BUTTONCLEAR, OnButtonclear)
	ON_BN_CLICKED(IDC_BUTTONFD, OnButtonfd)
	ON_CBN_SELCHANGE(IDC_COMBOGWS, OnSelchangeCombogws)
	ON_CBN_SELCHANGE(IDC_COMBOBD, OnSelchangeCombobd)
	ON_WM_MOVE()
	ON_CBN_DROPDOWN(IDC_COMBOGWS, OnDropdownCombogws)
	ON_BN_CLICKED(IDC_BUTTONMATCH, OnButtonmatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIMAGEMATCHOnSIFTDlg message handlers

BOOL CIMAGEMATCHOnSIFTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//设置对话框屏幕位置
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 20, 20, 0, 0,SWP_SHOWWINDOW|SWP_NOSIZE);
	/*gauss平滑核窗口大小下拉列表*/
	CString gausswidsize;
	gausswidsize = "1.5";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "1.75";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "2.0";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "2.25";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "2.5";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "2.75";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "3.0";
	m_COMBOGWS.AddString(gausswidsize);
	m_COMBOGWS.SetCurSel(2);
	
	/*边界距离选择，以像素为单位，不能小于gauss平滑窗口*/
	CString bd;
	bd = "3";
	m_COMBOBD.AddString(bd);
	bd = "4";
	m_COMBOBD.AddString(bd);
	bd = "5";
	m_COMBOBD.AddString(bd);
	bd = "6";
	m_COMBOBD.AddString(bd);
	bd = "7";
	m_COMBOBD.AddString(bd);
	m_COMBOBD.SetCurSel(2);

	/*匹配距离比例*/
	CString distratio;
	distratio = "0.90";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.85";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.80";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.78";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.75";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.72";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.70";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.68";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.65";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.60";
	m_COMBOSDR.AddString(distratio);
	m_COMBOSDR.SetCurSel(3);

	/*梯度阈值*/
	CString mt;
	mt = "0.2";
	m_COMBOMT.AddString(mt);
	m_COMBOMT.SetCurSel(0);

	/*设置文本编辑框字数限制*/
	m_EDITSLTIMG1.SetLimitText(100);
	m_EDITSLTIMG2.SetLimitText(100);

	/*设置滑动条滑动范围及初始位置*/
	m_SLIDERIS.SetRange(0, 60);		//0.8-2.0,space：0.02
	m_SLIDERIS.SetPos(40);
	m_SLIDERCD.SetRange(0, 18);		//0.03-0.12 space:0.005
	m_SLIDERCD.SetPos(2);

	/*设置initial scale编辑框初始内容*/
	char	buf[10];
	CString edit;
	int		pos = m_SLIDERIS.GetPos();
	float	scale = pos*0.02+0.8;
	sprintf(buf, "%lf", scale);
	edit.Format("%s", buf);
	SetDlgItemText(IDC_EDITIS, edit);
	m_EDITIS.SetLimitText(4);

	/*设置contrast threshhold 编辑框初始内容*/
	pos = m_SLIDERCD.GetPos();
	scale = pos*0.005 + 0.03;
	sprintf(buf, "%lf", scale);
	edit.Format("%s", buf);
	SetDlgItemText(IDC_EDITCD, edit);
	m_EDITCD.SetLimitText(4);

	/*check box， 选择是否double基本层图像,默认不选中*/
	((CButton *)GetDlgItem(IDC_CHECKDBLBASEIMG))->SetCheck(false);

	/*设置最后一个octave的分辨率大小*/
	CString miniRes;
	miniRes = "4";
	m_COMBOMiniRes.AddString(miniRes);
	miniRes = "8";
	m_COMBOMiniRes.AddString(miniRes);
	miniRes = "16";
	m_COMBOMiniRes.AddString(miniRes);
	miniRes = "32";
	m_COMBOMiniRes.AddString(miniRes);
	m_COMBOMiniRes.SetCurSel(1);

	/*将编辑框组合框等的内容更新到变量中*/
	UpdateData(true);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIMAGEMATCHOnSIFTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIMAGEMATCHOnSIFTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIMAGEMATCHOnSIFTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIMAGEMATCHOnSIFTDlg::OnButtonselectimg1() 
{
	// TODO: Add your control notification handler code here
	//select an image
	if (dspDlg.m_hWnd)
	{
		MessageBox("图像已经打开，请先关闭图像!");	
		return;
	}
	CFileDialog selectDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, NULL, NULL);
	selectDlg.m_ofn.lpstrTitle = TEXT("Select image 1") ;
	selectDlg.m_ofn.lpstrFilter="BMP Files (*.bmp, *.BMP)\0*.bmp\0\0";
	int retVal = selectDlg.DoModal();
	CString fext = selectDlg.GetFileExt();
	while((fext != "bmp")&&(fext != "BMP")&&(retVal!=IDCANCEL))
	{
		MessageBox("invalid image file!");
		retVal = selectDlg.DoModal();
		fext = selectDlg.GetFileExt();
	}
	if (retVal == IDCANCEL)
		return;	
	
	//get image path name
	SetDlgItemText(IDC_EDITSELECTIMG1, selectDlg.GetPathName());
}

void CIMAGEMATCHOnSIFTDlg::OnButtonselectimg2() 
{
	// TODO: Add your control notification handler code here
	if (dspDlg.m_hWnd)
	{
		MessageBox("图像已经打开，请先关闭图像!");	
		return;
	}
	CFileDialog selectDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, NULL, NULL);
	selectDlg.m_ofn.lpstrTitle = TEXT("Select image 2") ;
	selectDlg.m_ofn.lpstrFilter="BMP Files (*.bmp, *.BMP)\0*.bmp\0\0";
	int retVal = selectDlg.DoModal();
	CString fext = selectDlg.GetFileExt();
	while((fext != "bmp")&&(fext != "BMP")&&(retVal!=IDCANCEL))
	{
		MessageBox("invalid image file!");
		retVal = selectDlg.DoModal();
		fext = selectDlg.GetFileExt();
	}
	if (retVal == IDCANCEL)
		return;	
	
	//get image path name
	SetDlgItemText(IDC_EDITSELECTIMG2, selectDlg.GetPathName());
}



void CIMAGEMATCHOnSIFTDlg::OnMaxtextEditselectimg1() 
{
	// TODO: Add your control notification handler code here
	MessageBox("文件路径过长！");
	SetDlgItemText(IDC_EDITSELECTIMG1, "");
}


void CIMAGEMATCHOnSIFTDlg::OnMaxtextEditselectimg2() 
{
	// TODO: Add your control notification handler code here
	MessageBox("文件路径过长！");
	SetDlgItemText(IDC_EDITSELECTIMG2, "");
}

void CIMAGEMATCHOnSIFTDlg::OnCustomdrawSlideris(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	char	buf[10];
	CString edit;
	int		pos = m_SLIDERIS.GetPos();
	float	scale = pos*0.02+0.8;
	sprintf(buf, "%lf", scale);
	edit.Format("%s", buf);
	SetDlgItemText(IDC_EDITIS, edit);

	UpdateData(true);

	*pResult = 0;
}

void CIMAGEMATCHOnSIFTDlg::OnCustomdrawSlidercd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	char buf[10];
	int pos = m_SLIDERCD.GetPos();
	float scale = pos*0.005 + 0.03;
	CString edit;
	sprintf(buf, "%lf", scale);
	edit.Format("%s", buf);
	SetDlgItemText(IDC_EDITCD, edit);
	m_EDITCD.SetLimitText(4);

	UpdateData(true);
	
	*pResult = 0;
}

/*filepath:图像路径名，img:图像序号，0or1*/
bool CIMAGEMATCHOnSIFTDlg::LoadSrcImg(CString fpathname, int img)
{
	//目前只接受bmp图像
	CBitmap bmp;

	//位图句柄
	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), fpathname, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	if (!hBmp)
	{
		if (img==0)
			MessageBox("输入路径下找不到图像1!");
		else
			MessageBox("输入路径下找不到图像2!");
		return false;
	}

	//attach
	bmp.Attach(hBmp);

	//DIBSECTION
	DIBSECTION ds;
	//位图头信息
	BITMAPINFOHEADER &bmpInfo = ds.dsBmih;
	bmp.GetObject(sizeof(DIBSECTION), &ds); //分配空间

	//图像长度和宽度，像素为单位
	int w = bmpInfo.biWidth;
	int h = bmpInfo.biHeight;

	if ((w>800)||(h>800))
	{
		MessageBox("暂不支持800x800以上分辨率图像!");
		return false;
	}

	//读图像数据到缓冲区中
	CFile infile;
	BYTE *tmpimgbuf, *tmporgbuf, *tmpgraydata;		//临时缓冲区
	infile.Open(fpathname, CFile::modeRead);
	UINT flen = (UINT)infile.GetLength(); //得到图像长度
	infile.SeekToBegin();		//定位到文件头部
	if (img==0)  //img 0
	{
		m_width1 = w;
		m_height1 = h;
		if (m_imgdata1)
			delete[] m_imgdata1;
		m_imgdata1	= new BYTE[flen];
		tmpimgbuf	= m_imgdata1;
	}
	else //image 2
	{
		m_width2 = w;
		m_height2 = h;
		if (m_imgdata2)
			delete[] m_imgdata2;
		m_imgdata2 = new BYTE[flen];
		tmpimgbuf = m_imgdata2;
	}
	//将数据读入缓冲区
	infile.Read((void *)tmpimgbuf, flen);
	//infile.Flush();
	infile.Close();

	//得到rgb 数据或灰度数据
	BITMAPFILEHEADER *bmpfile = (BITMAPFILEHEADER *)tmpimgbuf;
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(tmpimgbuf + sizeof(BITMAPFILEHEADER));
	if (bmpfile->bfType != 0x4d42)		//不是bmp图像
	{
		AfxMessageBox("加载图像不是bmp格式！");
		//释放已分配空间
		if (img==0)
		{
			if (m_orgdata1)
				delete[] m_orgdata1;
			if (m_imgdata1)
				delete[] m_imgdata1;
		}
		else
		{
			if (m_orgdata2)
				delete[] m_orgdata2;
			if (m_imgdata2)
				delete[] m_imgdata2;
		}
		return false;
	}
	if ((bmpinfo->biBitCount!=24)&&(bmpinfo->biBitCount!=8))
	{
		AfxMessageBox("目前只支持24为彩色或8位灰度图像！");
		//释放已分配空间
		if (img==0)
		{
			if (m_imgdata1)
				delete[] m_imgdata1;
		}
		else
		{
			if (m_imgdata2)
				delete[] m_imgdata2;
		}
		tmpimgbuf = NULL;
		return false;
	}

	int bbc = bmpinfo->biBitCount;  //24 or 8
	int bpl = ((bbc*w+31)/32)*4;	//每行占用的内存空间，4bytes对齐
	int imgsize = bpl*h;			//存放图像数据所需内存空间,字节
	BYTE *imgdata = (BYTE *)(tmpimgbuf + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));  //rgbdata指向图像数据区
	//为灰度信息分配空间，不管输入为color还是gray，本程序均将其转换为灰度图像进行特征匹配
	//int bpl_gray = ((8*w+31)/32)*4;
	int bpl_gray = w;
	int imgsize_gray = bpl_gray*h;
	if (img == 0)
	{
		if (m_orgdata1) //rgb数据
			delete[] m_orgdata1;
		m_orgdata1 = new BYTE[imgsize];
		tmporgbuf = m_orgdata1;

		if (m_graydata1) //gray数据
			delete[] m_graydata1;
		m_graydata1 = new BYTE[imgsize_gray];
		tmpgraydata = m_graydata1;
	}
	else
	{
		if (m_orgdata2)
			delete[] m_orgdata2;
		m_orgdata2 = new BYTE[imgsize];
		tmporgbuf = m_orgdata2;

		if (m_graydata2)
			delete[] m_graydata2;
		m_graydata2 = new BYTE[imgsize_gray];
		tmpgraydata = m_graydata2;
	}
	//拷贝rgb或gray数据
	for (int k=0; k<h; k++)
		memcpy(tmporgbuf+k*bpl, imgdata+k*bpl, bpl);

	//计算灰度值
	if (bbc == 8) //原来图像为灰度图像
	{
		for (int k=0; k<h; k++)
			memcpy(tmpgraydata+k*bpl_gray, imgdata+k*bpl, bpl_gray);
	}
	else		//原图像为彩色图像
	{
		int i,j,co,con;
		int gray;
		double r, g, b;
		for (j=0; j<h; j++)
		{
			for (i=0; i<w; i++)
			{
				co = j*bpl + i*3;
				con = j*bpl_gray + i;
				b = imgdata[co];
				g = imgdata[co+1];
				r = imgdata[co+2];

				gray = (int)(0.11*r+0.59*g+0.3*b);
				gray = (gray<255) ? gray : 255;
				tmpgraydata[con] = gray;
			}
		}
	}

	return true;
}


void CIMAGEMATCHOnSIFTDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CIMAGEMATCHOnSIFTDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//
	CDlgMClose dlg;
	if (dlg.DoModal()==IDCANCEL)
		return;

	//释放空间
	if (m_orgdata1)
	{
		delete[] m_orgdata1;
		m_orgdata1 = NULL;
	}		
	if (m_orgdata2)
	{
		delete[] m_orgdata2;
		m_orgdata2 = NULL;
	}		
	if (m_imgdata1)
	{
		delete[] m_imgdata1;
		m_imgdata1 = NULL;
	}		
	if (m_imgdata2)
	{
		delete[] m_imgdata2;
		m_orgdata2 = NULL;
	}
	if (m_graydata1)
	{
		delete[] m_graydata1;
		m_graydata1 = NULL;
	}
	if (m_graydata2)
	{
		delete[] m_graydata2;
		m_graydata2 = NULL;
	}

	if (matchedcos)
	{
		delete[] matchedcos;
		matchedcos = NULL;
	}

	if (featVect1)
	{
		free_feature_nodes(featVect1);
		featVect1 = NULL;
	}		
	if (featVect2)
	{
		free_feature_nodes(featVect2);
		featVect2 = NULL;
	}

	::DestroyWindow(this->m_hWnd);
	CDialog::OnClose();
}

BOOL CIMAGEMATCHOnSIFTDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DestroyWindow();
}



int CIMAGEMATCHOnSIFTDlg::OnButtonshowimg() 
{
	// TODO: Add your control notification handler code here
	if (dspDlg.m_hWnd)
	{
		return 1;		//图像已经打开
	}
	CWnd *wnd;
	//UpdateData(); //获取编辑框中数据
	GetDlgItemText(IDC_EDITSELECTIMG1, m_img1path);
	GetDlgItemText(IDC_EDITSELECTIMG2, m_img2path);
	if (m_img1path.IsEmpty())
	{
		MessageBox("请选择图像1的路径!");
		wnd = GetDlgItem(IDC_BUTTONSELECTIMG1);
		wnd->SetFocus();
		return 0;
	}
	if (m_img2path.IsEmpty())
	{
		MessageBox("请选择图像2的路径!");
		wnd = GetDlgItem(IDC_BUTTONSELECTIMG2);
		wnd->SetFocus();
		return 0;
	}
	//设置编辑框只读
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDITSELECTIMG1);
	pEdit1->SetReadOnly(true);
	CEdit *pEdit2 = (CEdit *)GetDlgItem(IDC_EDITSELECTIMG2);
	pEdit2->SetReadOnly(true);
	if (!LoadSrcImg(m_img1path, 0))
	{
		MessageBox("加载图像1失败!请重新选择图像");
		pEdit1->SetReadOnly(false);
		wnd = GetDlgItem(IDC_EDITSELECTIMG1);
		wnd->SetFocus();
		pEdit1->SetSel(0, pEdit1->LineLength(0));
		return 0;
	}		
	if (!LoadSrcImg(m_img2path, 1))
	{
		MessageBox("加载图像2失败!请重新选择图像");
		pEdit2->SetReadOnly(false);
		wnd = GetDlgItem(IDC_EDITSELECTIMG2);
		wnd->SetFocus();
		pEdit2->SetSel(0, pEdit2->LineLength(0));
		return 0;
	}
	
	/*新建一个对话框并将图像显示其中*/
	ShowImage();

	return 1;
}

void CIMAGEMATCHOnSIFTDlg::ShowImage()
{
	BITMAPFILEHEADER *bmpfile1, *bmpfile2;
	BITMAPINFOHEADER *bmpinfo1, *bmpinfo2;
	int nw, nh;			//新图像的高度和宽度,像素为单位
	
	bmpfile1 = (BITMAPFILEHEADER *)m_imgdata1;
	bmpinfo1 = (BITMAPINFOHEADER *)(m_imgdata1 + sizeof(BITMAPFILEHEADER));
	bmpfile2 = (BITMAPFILEHEADER *)m_imgdata2;
	bmpinfo2 = (BITMAPINFOHEADER *)(m_imgdata2 + sizeof(BITMAPFILEHEADER));
	
	nw = (m_width1>m_width2) ? m_width1 : m_width2;
	nh = m_height1 + m_height2;
	int bbc1 = bmpinfo1->biBitCount;
	int bbc2 = bmpinfo2->biBitCount;
	/*int nbbc = (bbc1>bbc2) ? bbc1 : bbc2;*/
	int nbbc = 24;  //新图像均以24位显示
	int bpl1 = ((bbc1*m_width1+31)/32)*4;
	int bpl2 = ((bbc2*m_width2+31)/32)*4;
	int nbpl = ((nbbc*nw+31)/32)*4;
	int nimgsize = nbpl*nh;

	//临时数据缓冲区
	BYTE *newdata = new BYTE[nimgsize];
	
	//拷贝新图像数据
	int i,j,k1,nk;
	if (bmpinfo1->biBitCount==8)  //8位灰度数据
	{
		for (j=0; j<m_height1; j++)
			for (i=0; i<m_width1; i++)
			{
				k1 = j*bpl1 + i;
				nk = j*nbpl + i*3;
				newdata[nk] = newdata[nk+1] = newdata[nk+2] = m_orgdata1[k1];
			}
	}
	else //24位彩色数据
	{
		for (j=0; j<m_height1; j++)
			memcpy(newdata+j*nbpl, m_orgdata1+j*bpl1, bpl1);
	}
	if (bmpinfo2->biBitCount==8)  //8位灰度数据
	{
		//nk = (m_height1-1)*nbpl;
		for (j=0; j<m_height2; j++)
			for (i=0; i<m_width2; i++)
			{
				k1 = j*bpl2 + i;
				nk = (j+m_height1)*nbpl + i*3;
				newdata[nk] = newdata[nk+1] = newdata[nk+2] = m_orgdata2[k1];
			}
	}
	else //24位彩色数据
	{
		for (j=0; j<m_height2; j++)
			memcpy(newdata+(m_height1+j)*nbpl, m_orgdata2+j*bpl2, bpl2);
	}
	/*显示*/
	//拷贝图像信息, 此函数必须位于显示之前
	BYTE *imgdata = (bbc1>bbc2) ? m_imgdata1:m_imgdata2;
	dspDlg.SetImgInfo(nw, nh, nimgsize, imgdata, newdata);
	dspDlg.Create(IDD_IMGDISPLAYER, this);  //创建显示图像的对话框
	CWnd *pWnd = dspDlg.GetDlgItem(IDC_IMGDISPLAYER); //得到图片控件指针
	CRect rect;
	pWnd->GetWindowRect(&rect); //得到图像控件相对于屏幕左上角的坐标
	dspDlg.ScreenToClient(&rect); //将屏幕坐标转换为用户坐标

	/*设置显示对话框的位置*/
	//得到当前主要对话框的位置
	CRect dlgrect;
	::GetWindowRect(this->m_hWnd, &dlgrect);
	nw = nw + (int)(2.5*rect.left);
	int sysy = GetSystemMetrics(SM_CYSCREEN);
	nh = nh + (int)(4.5*rect.top);
	::SetWindowPos(dspDlg.m_hWnd, HWND_TOPMOST, dlgrect.right, dlgrect.top, nw, nh,SWP_SHOWWINDOW);	
	dspDlg.GetWindowRect(&dlgrect);
	m_showdlgh = dlgrect.bottom-dlgrect.top;
	
	dspDlg.ShowWindow(SW_SHOW);		//显示对话框

	//设置滚动条滚动范围
	dspDlg.ScreenToClient(&dlgrect);
	int vmaxPos = (int)((nh-m_showdlgh+49)/50);  //suppose i unit means 50 pixels
	::SetScrollRange(dspDlg.m_hWnd, SB_VERT, 0, vmaxPos, true);

	//释放临时空间
	if (newdata)
		delete[] newdata;
	else
		MessageBox("error");
	//note:还要在dspdlg中的onpaint中重绘	
}

void CIMAGEMATCHOnSIFTDlg::OnButtonclear() 
{
	// TODO: Add your control notification handler code here
	//清空2个编辑框内容
	if (dspDlg.m_hWnd)
	{
		MessageBox("图像已打开，请先关闭图像!");
		return;
	}
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDITSELECTIMG1);
	pEdit->SetReadOnly(false);
	pEdit = (CEdit *)GetDlgItem(IDC_EDITSELECTIMG2);
	pEdit->SetReadOnly(false);
	SetDlgItemText(IDC_EDITSELECTIMG1, "");
	SetDlgItemText(IDC_EDITSELECTIMG2, "");
}

void CIMAGEMATCHOnSIFTDlg::OnButtonfd() 
{
	// TODO: Add your control notification handler code here
	/*判断对象是否已经打开*/
	if (dspDlg.m_hWnd==NULL)
	{
		//若当前图像未加载，调用buttonshowimg函数
		if (OnButtonshowimg()==0)
			return;
	}
	if (dspDlg.m_sifted)/*已经特征检测了*/
		return;

	//提取参数
	CString buf;
	UpdateData(true);
	CComboBox *pCombo;

	//gauss窗口半径s
	float	gsw;	
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBOGWS);
	pCombo->GetLBText(m_gws, buf);
	gsw = atof(buf);

	//为进行高斯平滑设置的边界距离
	int		bd;		
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBOBD);
	pCombo->GetLBText(m_bd, buf);
	bd = atoi(buf);

	//第0个octave的第0层的高斯平滑系数
	float	sigma0;		
	sigma0 = atof(m_is);

	//为消除低对比度设置的阈值
	float	contr_thr;		
	contr_thr = atof(m_cd);

	//特征向量归一化设置的梯度阈值
	float norm_thresh;
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBOMT);
	pCombo->GetLBText(m_mt, buf);
	norm_thresh = atof(buf);

	//基本层图像是否要double
	int db_img= ((CButton *)GetDlgItem(IDC_CHECKDBLBASEIMG))->GetCheck();
	if (db_img==BST_UNCHECKED)
		db_img = 0;
	else if (db_img==BST_CHECKED)
		db_img = 1;

	//最后一组图像的分辨率
	int top_oct_res;
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBOMINIRES);
	pCombo->GetLBText(m_miniRes, buf);
	top_oct_res = atoi(buf);

	//假定图像已经存在的模糊系数
	float sigman = 0.5f;		

// 	gsw = 2.5;							//gauss卷积模板半径为gwid*sigma
// 	db_img = 0;
// 	sigma0 = 1.6f;
// 	sigman = 0.5f;
// 	contr_thr	= 0.03f;					//都对比度阈值=contr_thr/scales
// 	bd = 5;
// 	norm_thresh = 0.2f;				//歸一化閾值

	//计算两幅图像的特征向量
	HeadStand(m_width1, m_height1, m_graydata1);	//
	featVect1 = sifting(m_width1, m_height1, m_graydata1, gsw, db_img, sigma0, sigman, contr_thr, bd, norm_thresh, top_oct_res);
	CString keyn1;
	char chbuf[10];
	int keynum1 = featVect1->to_extr_num;
	itoa(keynum1, chbuf, 10);
	keyn1.Format("%s", chbuf);
	SetDlgItemText(IDC_EDITKEYPOINTSNUM1, keyn1);		//显示检测到的关键点数

	HeadStand(m_width2, m_height2, m_graydata2);
	featVect2 = sifting(m_width2, m_height2, m_graydata2, gsw, db_img, sigma0, sigman, contr_thr, bd, norm_thresh, top_oct_res);
	CString keyn2;
	int keynum2 = featVect2->to_extr_num;
	itoa(keynum2, chbuf, 10);
	keyn2.Format("%s", chbuf);
	SetDlgItemText(IDC_EDITKEYPOINTSNUM2, keyn2);

	dspDlg.m_sifted = true;	
}
/*
执行sift特征提取

w:			图像宽度
h:			图像高度
graydata:	图像数据
wid:		gauss窗口因子
db_img:		基本层图像是否要double
sigma0:     最底层图像的平滑因子
sigman:		假定初始图像已有的平滑因子
contr_thr:	对比度阈值
sift_border:极值点搜索边界
norm_thresh:特征向量梯度阈值 
*/
FeatureVect* CIMAGEMATCHOnSIFTDlg::sifting(int w, int h, BYTE *graydata, float wid, int db_img, float sigma0,\
										   float sigman, float contr_thr, int sift_border, float norm_thresh, int top_oct_res)
{
	FeatureVect *featVect;

	featVect = _sift_main("reserved", graydata, w, h, wid, db_img, sigma0, sigman, contr_thr, sift_border, norm_thresh, top_oct_res);

	//将监测到的关键点显示到图像上
	ShowKeypoints(0);
	//dspDlg.SetFocus();
	return featVect;
}
//将得到的关键点显示在界面上
void CIMAGEMATCHOnSIFTDlg::ShowKeypoints(int img)
{
	//更新
	dspDlg.SetFocus();
	dspDlg.Invalidate(FALSE);
	//dspDlg中的onpaint函数完成重绘
}



void CIMAGEMATCHOnSIFTDlg::OnSelchangeCombogws() 
{
	// TODO: Add your control notification handler code here
	CString gwsItem, bdItem;
	GetDlgItemText(IDC_COMBOBD, bdItem);
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBOGWS);
	pCombo->GetLBText(pCombo->GetCurSel(), gwsItem);

	UpdateData(true);
}


void CIMAGEMATCHOnSIFTDlg::OnSelchangeCombobd() 
{
	// TODO: Add your control notification handler code here
	CString gwsItem, bdItem;
	GetDlgItemText(IDC_COMBOGWS, gwsItem);
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBOBD);
	pCombo->GetLBText(pCombo->GetCurSel(), bdItem);

	UpdateData(true);
}

//本函数实现当主对话框移动时，子对话框跟随主对话框移动
void CIMAGEMATCHOnSIFTDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);

	if (dspDlg.m_hWnd)
	{
		int nw = (m_width1>m_width2) ? m_width1 : m_width2;
		CWnd *pWnd = dspDlg.GetDlgItem(IDC_IMGDISPLAYER); //得到图片控件指针
		CRect dlgrect, rect;
		pWnd->GetWindowRect(&rect); //得到图像控件相对于屏幕左上角的坐标
		dspDlg.ScreenToClient(&rect); //将屏幕坐标转换为用户坐标
		::GetWindowRect(this->m_hWnd, &dlgrect);
		nw = nw+(int)(2.5*rect.left);
		::SetWindowPos(dspDlg.m_hWnd, HWND_TOPMOST, dlgrect.right, dlgrect.top, nw, m_showdlgh,SWP_SHOWWINDOW);	
	}
	
	// TODO: Add your message handler code here	
}

void CIMAGEMATCHOnSIFTDlg::OnDropdownCombogws() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_COMBOGWS);
	pCombo->SetFocus();
}


int CIMAGEMATCHOnSIFTDlg::mem2D_alloc(double ***arr, int h, int w)
{
	*arr = new double*[h];
	for (int j=0; j<h; j++)
		(*arr)[j] = new double[w];

	return h*w*sizeof(double);
}

void CIMAGEMATCHOnSIFTDlg::mem2D_free(double **arr, int h)
{
	if (arr)
	{
		for (int j=0; j<h; j++)
			delete[] arr[j];
		delete[] arr;
	}
}

int CIMAGEMATCHOnSIFTDlg::mem3D_alloc(double ****arr, int h, int w, int o)
{
	*arr = new double**[h];
	for (int j=0; j<h; j++)
		mem2D_alloc((*arr)+j, w, o);
	return h*w*o*sizeof(double);
}

void CIMAGEMATCHOnSIFTDlg::mem3D_free(double ***arr, int h, int w)
{
	if (arr)
	{
		for (int j=0; j<h; j++)
			mem2D_free(arr[j], w);
		delete[] arr;
	}
}

int CIMAGEMATCHOnSIFTDlg::mem4D_alloc(double *****arr, int h, int w, int o, int b)
{
	*arr = new double ***[h];
	for (int j=0; j<h; j++)
		mem3D_alloc((*arr)+j, w, o, b);
	return h*w*o*b*sizeof(double);
}

void CIMAGEMATCHOnSIFTDlg::mem4D_free(double ****arr, int h, int w, int o)
{
	if (arr)
	{
		for (int j=0; j<h; j++)
			mem3D_free(arr[j], w, o);
		delete[] arr;
	}
}



void CIMAGEMATCHOnSIFTDlg::OnButtonmatch() 
{
	// TODO: Add your control notification handler code here
	if  (!dspDlg.m_sifted)
	{
		MessageBox("请先特征匹配");
		return;
	}
		
	int k;
	int matchednum = 0;		//匹配点个数
	double distance1, distance2, distance;
	double dr;
	
	CString buf;
	UpdateData(true);
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBOSDR);
	pCombo->GetLBText(m_sdr, buf);
	dr = atof(buf);		
	dr = dr*dr;			//distance ratio 0.8*0.8

	//int (*matchedcos)[2][2];
	int keynum1 = featVect1->to_extr_num;
	int keynum2 = featVect2->to_extr_num;

	int keynum = (keynum1>keynum2) ? keynum1 : keynum2;
	matchedcos = new int[keynum][2][2];			//匹配点的坐标 0:img1, 1:img2 0: y, 1:x

	int x12, x22, y12, y22;		//	y距离图像
	FeatureNode *node1, *node2;
	node1 = featVect1->first;
	float *descriptor1, *descriptor2;
	double diff;

	int bx, by, ex, ey;

	while(node1!=NULL)
	{
		bx = (int)(node1->feat->ox+0.5f);
		by = (int)(node1->feat->oy+0.5f);
		if ((bx==14)&&(by==84))
		{
			MessageBox("");
		}

		descriptor1 = node1->feat->descriptor;
		distance1 = distance2 = 100000000000000000000.00;
		node2 = featVect2->first;

		while(node2!=NULL)
		{
			ex = (int)(node2->feat->ox+0.5f);
			ey = (int)(node2->feat->oy+0.5f);
			if ((ex>254)&&(ex<264)&&(ey>9)&&(ey<19))
			{
				MessageBox("");
			}

			descriptor2 = node2->feat->descriptor;
			distance = 0.0;
			for (k=0; k<SIFT_DESC_LEN; k++)
			{
				diff = descriptor1[k]-descriptor2[k];
				distance += diff*diff;
			}
			if (distance<distance1)
			{
				distance2 = distance1;
				distance1 = distance;
				y22 = y12;
				x22 = x12;
				y12 = (int)(node2->feat->oy+0.5);
				x12 = (int)(node2->feat->ox+0.5);
			}
			else if (distance<distance2)
			{
				distance2 = distance;
				y22 = (int)(node2->feat->oy+0.5);
				x22 = (int)(node2->feat->ox+0.5);
			}
			node2 = node2->next;
		}
		if ((distance1/distance2<dr)) //接受匹配
		{
			matchedcos[matchednum++][0][0] = (int)(node1->feat->oy+0.5);
			matchedcos[matchednum-1][0][1] = (int)(node1->feat->ox+0.5);
			matchedcos[matchednum-1][1][0] = y12;
			matchedcos[matchednum-1][1][1] = x12;
		}
		node1 = node1->next;
	}

	m_matchednum = matchednum;

	dspDlg.m_matched = true;
	ShowKeypoints(0);
	
	char chbuf[10];
	CString keyn;
	itoa(m_matchednum, chbuf, 10);
	keyn.Format("%s", chbuf);
	SetDlgItemText(IDC_EDITMATCHEDNUM, keyn);
}

/*deprecated. 不好使*/
void CIMAGEMATCHOnSIFTDlg::DrawMatchedLine()
{
	int k;
	CWnd *pWnd = GetDlgItem(IDC_IMGDISPLAYER);
	CClientDC dc(pWnd);
	CPen pen(PS_SOLID, 1, RGB(255,0,0));
	CPen *pOldpen = dc.SelectObject(&pen);
	dc.SelectStockObject(HOLLOW_BRUSH); 
	int nhnum = m_height1 + m_height2 -1;
	int y10;
	int x10;
	int y20;
	int x20;
	
	for (k=0; k<m_matchednum; k++)
	{
		y10 = matchedcos[k][0][0];
		x10 = matchedcos[k][0][1];
		y20 = matchedcos[k][1][0];
		x20 = matchedcos[k][1][1];
		
		dc.MoveTo(x10, nhnum-y10);
		dc.LineTo(x20, m_height2-1-y20);
	}
	dc.SelectObject(pOldpen);
}

/*
top->bottom,图像的rgb数据顺序与显示顺序相反

width: 图像宽度
height:图像高度
imgbuf:图像存放缓冲区
*/
void CIMAGEMATCHOnSIFTDlg::HeadStand(int width, int height, BYTE *imgbuf)
{
	int dist;
	BYTE *buftmp;

	dist	 = width*sizeof(BYTE);
	buftmp = new BYTE[dist];

	for (int i=0; i<height/2; i++)
	{
		memcpy(buftmp, imgbuf+i*dist, dist);
		memcpy(imgbuf+i*dist, imgbuf+(height-1)*dist-i*dist, dist);
		memcpy(imgbuf+(height-1)*dist-i*dist, buftmp, dist);
	}
	
	delete[] buftmp;
}
