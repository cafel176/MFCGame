
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mapArray.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int size = 32;//一个格子尺寸
int screenWidth = 6;//屏幕宽度

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
//afx_msg宏没有任何语法上的实际意义。afx_msg宏表示声明的是一个消息响应函数
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


// CMFCApplication1Dlg 主对话框

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//用于存放各类控件的变量信息
void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()   //响应控制指令
	ON_WM_PAINT()         //响应绘图消息，用于刷新窗口
	ON_WM_QUERYDRAGICON() //当用户拖动最小化窗口时取得光标
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMFCApplication1Dlg 消息处理程序

//用于初始化对话框
BOOL CMFCApplication1Dlg::OnInitDialog()
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
	init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//统指令响应函数，默认处理窗口最小化和最大化指令等
void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

//绘图消息响应函数
void CMFCApplication1Dlg::OnPaint()
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
		drawSth();

		CDialogEx::OnPaint();
	}

}

//窗口大小改变时重新绘制
void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//当窗口大小改变的时候，使客户区无效
	Invalidate(FALSE);
}

int CMFCApplication1Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1, 500, NULL);//角色用
	SetTimer(2, 1000, NULL);//灯光用

	CRect rect;
	GetWindowRect(rect);
	MoveWindow(rect.left, rect.top, (screenWidth * 2+1)*size+16, (screenWidth * 2+2)  * size + 16, TRUE);

	return 0;
}

//==================================游戏逻辑==================================
//角色初始位置
int playerX = 7,playerY=14;
//初始化
void CMFCApplication1Dlg::init()
{
	//读图
	//0-A2,1-A4,2-A5,3-B,4-C,5-D,6-E,7-fire,8-piano,9-K,10-ray
	CString picName[bitNum] = { CString("pic/A2.bmp"),CString("pic/A4.bmp"),CString("pic/A5.bmp"),
		CString("pic/B.bmp"),CString("pic/C.bmp"),CString("pic/D.bmp"),CString("pic/E.bmp"),
		CString("pic/fire.bmp"),CString("pic/piano.bmp"),CString("pic/K.bmp"),CString("pic/ray.bmp") };
	CString maskName[bitNum] = { CString(""),CString(""),CString(""),
		CString("pic/B_mask.bmp"),CString("pic/C_mask.bmp"),CString("pic/D_mask.bmp"),
		CString("pic/E_mask.bmp"),CString("pic/fire_mask.bmp"),CString("pic/piano_mask.bmp"),
		CString("pic/K_mask.bmp"),CString("pic/ray_mask.bmp") };

	//按照图片原来的大小加载图片
	int picx[] = {512,512,256,512,512,512,512,384,288,96,192};
	int picy[] = {384,480,512,512,512,512,512,512,256,256,512};

	//加载bitmap
	for (int i = 0; i < bitNum; i++)
	{
		bitmap[i][0].m_hObject = (HBITMAP)::LoadImage(NULL, picName[i], IMAGE_BITMAP, picx[i], picy[i], LR_LOADFROMFILE);
		bitmap[i][1].m_hObject = (HBITMAP)::LoadImage(NULL, maskName[i], IMAGE_BITMAP, picx[i], picy[i], LR_LOADFROMFILE);
	}
	animaNum = sizeof(anima) / sizeof(anima[0]);

	//使角色位于画面中心
	anima[0].posx = screenWidth;
	anima[0].posy = screenWidth-1;

	CClientDC cdc(this);
	//双缓冲
	mdc = new CDC;
	mdc->CreateCompatibleDC(&cdc);//缓存DC，保存结果图
	mdc2 = new CDC;
	mdc2->CreateCompatibleDC(mdc);//计算DC
}

//主要的绘制函数
void CMFCApplication1Dlg::drawSth() {

	dc = new CPaintDC(this);

	CRect rect;
	GetClientRect(&rect);
	//给缓存DC铺上一张全屏幕的空bitmap，没有位图无法往DC上画东西
	CBitmap bit;
	bit.CreateCompatibleBitmap(dc,rect.Width(),rect.Height());
	mdc->SelectObject(bit);

	int minx, maxx, miny, maxy;
	//判断滚动地图范围
	if (playerX <= screenWidth) {
		minx = 0; maxx = screenWidth * 2; 
	}
	else if (playerX >= X - screenWidth) {
		minx = X - 2 * screenWidth-1; maxx = X-1; 
	}
	else {
		minx = playerX - screenWidth;
		maxx= playerX + screenWidth;
	}

	if (playerY <= screenWidth) {
		miny = 0; maxy = screenWidth * 2; 
	}
	else if (playerY >= Y - screenWidth) {
		miny = Y - 2 * screenWidth-1; maxy = Y-1; 
	}
	else {
		miny = playerY - screenWidth;
		maxy = playerY + screenWidth;
	}

	//铺地板
	int n, x, y;
	for (int i = 0; i<=2*screenWidth; i++)
		for (int j = 0; j <= 2 * screenWidth; j++)
		{
			x = i+minx; y = j+miny;
			n = getPos(0, x, y);
			if (n != -1) 
			{
				mdc2->SelectObject(bitmap[n][0]);
				mdc->BitBlt(i* size, j * size, size, size, mdc2, x* size/2, y* size/2, SRCCOPY);
				//最后一个参数传递的是Raster运算值,用来设置位图贴到目的DC的方式
			}
		}

	//铺覆盖物
	for (int i = 0; i<=2 * screenWidth; i++)
		for (int j = 0; j <= 2 * screenWidth; j++)
		{
			x = i+minx; y = j+miny;
			n = getPos(1, x, y);
			if (n != -1)
			{
				mdc2->SelectObject(bitmap[n][1]);
				mdc->BitBlt(i* size, j * size, size, size, mdc2, x* size, y* size, SRCAND);
				mdc2->SelectObject(bitmap[n][0]);
				mdc->BitBlt(i* size, j * size, size, size, mdc2, x* size, y* size, SRCPAINT);
			}
		}

	//更新动画绘制
	for (int i = 1; i < animaNum; i++) {
		if (anima[i].posx+anima[i].width<minx|| anima[i].posx>maxx)
			continue;
		if (anima[i].posy+ anima[i].height<miny || anima[i].posy>maxy)
			continue;

		mdc2->SelectObject(bitmap[anima[i].n][1]);
		mdc->BitBlt((anima[i].posx-minx) * size, (anima[i].posy-miny) * size, 
			anima[i].width*size,anima[i].height*size, mdc2, anima[i].nowx* size, anima[i].nowy* size, SRCAND);
			
		mdc2->SelectObject(bitmap[anima[i].n][0]);
		mdc->BitBlt((anima[i].posx - minx) * size,(anima[i].posy - miny) * size, 
			anima[i].width*size,anima[i].height*size, mdc2, anima[i].nowx* size, anima[i].nowy* size, SRCPAINT);
	}

	//绘制角色
	mdc2->SelectObject(bitmap[anima[0].n][1]);
	mdc->BitBlt(anima[0].posx * size, anima[0].posy * size, anima[0].width*size,
		anima[0].height*size, mdc2, anima[0].nowx* size, anima[0].nowy* size, SRCAND);

	mdc2->SelectObject(bitmap[anima[0].n][0]);
	mdc->BitBlt(anima[0].posx * size, anima[0].posy * size, anima[0].width*size,
		anima[0].height*size, mdc2, anima[0].nowx* size, anima[0].nowy* size, SRCPAINT);
	//显示
	dc->BitBlt(0, 0, rect.Width(), rect.Height(), mdc, 0, 0, SRCCOPY);
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
		case 1:
			anima[0].nextFrame();//更新角色动画
			break;
		case 2:
			for (int i = 1; i < animaNum; i++) {//更新灯动画
				anima[i].nextFrame();
			}
			break;
		default:
			break;
	}
	Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}

//添加键盘响应
BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch (pMsg->wParam)
		{
			case VK_LEFT:
				anima[0].changeRow(1);
				if (blockArray[playerX-1][playerY]==0&&playerX > 0) {
					playerX--;
					if (playerX < screenWidth||playerX >= X - screenWidth-1)
						anima[0].changePos(-1, 0);
				}
				break;
			case VK_RIGHT:
				anima[0].changeRow(2);
				if (blockArray[playerX+1][playerY] == 0 && playerX < X-1) {
					playerX++;
					if (playerX <= screenWidth || playerX > X - screenWidth-1)
						anima[0].changePos(1, 0);
				}
				break;
			case VK_UP:
				anima[0].changeRow(3);
				if (blockArray[playerX][playerY-1] == 0 && playerY > 0) {
					playerY--;
					if (playerY < screenWidth || playerY >= Y - screenWidth-1)
						anima[0].changePos(0, -1);
				}
				break;
			case VK_DOWN:
				anima[0].changeRow(0);
				if (blockArray[playerX][playerY+1] == 0 && playerY <Y-1) {
					playerY++;
					if (playerY <= screenWidth || playerY > Y - screenWidth-1)
						anima[0].changePos(0, 1);
				}
				break;
			default:
				break;
		}
		
		Invalidate(FALSE);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

