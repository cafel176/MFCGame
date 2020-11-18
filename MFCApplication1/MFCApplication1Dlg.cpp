
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mapArray.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int size = 32;//һ�����ӳߴ�
int screenWidth = 6;//��Ļ���

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
//afx_msg��û���κ��﷨�ϵ�ʵ�����塣afx_msg���ʾ��������һ����Ϣ��Ӧ����
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


// CMFCApplication1Dlg ���Ի���

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//���ڴ�Ÿ���ؼ��ı�����Ϣ
void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()   //��Ӧ����ָ��
	ON_WM_PAINT()         //��Ӧ��ͼ��Ϣ������ˢ�´���
	ON_WM_QUERYDRAGICON() //���û��϶���С������ʱȡ�ù��
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMFCApplication1Dlg ��Ϣ�������

//���ڳ�ʼ���Ի���
BOOL CMFCApplication1Dlg::OnInitDialog()
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
	init();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//ͳָ����Ӧ������Ĭ�ϴ�������С�������ָ���
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

//��ͼ��Ϣ��Ӧ����
void CMFCApplication1Dlg::OnPaint()
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
		drawSth();

		CDialogEx::OnPaint();
	}

}

//���ڴ�С�ı�ʱ���»���
void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//�����ڴ�С�ı��ʱ��ʹ�ͻ�����Ч
	Invalidate(FALSE);
}

int CMFCApplication1Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(1, 500, NULL);//��ɫ��
	SetTimer(2, 1000, NULL);//�ƹ���

	CRect rect;
	GetWindowRect(rect);
	MoveWindow(rect.left, rect.top, (screenWidth * 2+1)*size+16, (screenWidth * 2+2)  * size + 16, TRUE);

	return 0;
}

//==================================��Ϸ�߼�==================================
//��ɫ��ʼλ��
int playerX = 7,playerY=14;
//��ʼ��
void CMFCApplication1Dlg::init()
{
	//��ͼ
	//0-A2,1-A4,2-A5,3-B,4-C,5-D,6-E,7-fire,8-piano,9-K,10-ray
	CString picName[bitNum] = { CString("pic/A2.bmp"),CString("pic/A4.bmp"),CString("pic/A5.bmp"),
		CString("pic/B.bmp"),CString("pic/C.bmp"),CString("pic/D.bmp"),CString("pic/E.bmp"),
		CString("pic/fire.bmp"),CString("pic/piano.bmp"),CString("pic/K.bmp"),CString("pic/ray.bmp") };
	CString maskName[bitNum] = { CString(""),CString(""),CString(""),
		CString("pic/B_mask.bmp"),CString("pic/C_mask.bmp"),CString("pic/D_mask.bmp"),
		CString("pic/E_mask.bmp"),CString("pic/fire_mask.bmp"),CString("pic/piano_mask.bmp"),
		CString("pic/K_mask.bmp"),CString("pic/ray_mask.bmp") };

	//����ͼƬԭ���Ĵ�С����ͼƬ
	int picx[] = {512,512,256,512,512,512,512,384,288,96,192};
	int picy[] = {384,480,512,512,512,512,512,512,256,256,512};

	//����bitmap
	for (int i = 0; i < bitNum; i++)
	{
		bitmap[i][0].m_hObject = (HBITMAP)::LoadImage(NULL, picName[i], IMAGE_BITMAP, picx[i], picy[i], LR_LOADFROMFILE);
		bitmap[i][1].m_hObject = (HBITMAP)::LoadImage(NULL, maskName[i], IMAGE_BITMAP, picx[i], picy[i], LR_LOADFROMFILE);
	}
	animaNum = sizeof(anima) / sizeof(anima[0]);

	//ʹ��ɫλ�ڻ�������
	anima[0].posx = screenWidth;
	anima[0].posy = screenWidth-1;

	CClientDC cdc(this);
	//˫����
	mdc = new CDC;
	mdc->CreateCompatibleDC(&cdc);//����DC��������ͼ
	mdc2 = new CDC;
	mdc2->CreateCompatibleDC(mdc);//����DC
}

//��Ҫ�Ļ��ƺ���
void CMFCApplication1Dlg::drawSth() {

	dc = new CPaintDC(this);

	CRect rect;
	GetClientRect(&rect);
	//������DC����һ��ȫ��Ļ�Ŀ�bitmap��û��λͼ�޷���DC�ϻ�����
	CBitmap bit;
	bit.CreateCompatibleBitmap(dc,rect.Width(),rect.Height());
	mdc->SelectObject(bit);

	int minx, maxx, miny, maxy;
	//�жϹ�����ͼ��Χ
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

	//�̵ذ�
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
				//���һ���������ݵ���Raster����ֵ,��������λͼ����Ŀ��DC�ķ�ʽ
			}
		}

	//�̸�����
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

	//���¶�������
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

	//���ƽ�ɫ
	mdc2->SelectObject(bitmap[anima[0].n][1]);
	mdc->BitBlt(anima[0].posx * size, anima[0].posy * size, anima[0].width*size,
		anima[0].height*size, mdc2, anima[0].nowx* size, anima[0].nowy* size, SRCAND);

	mdc2->SelectObject(bitmap[anima[0].n][0]);
	mdc->BitBlt(anima[0].posx * size, anima[0].posy * size, anima[0].width*size,
		anima[0].height*size, mdc2, anima[0].nowx* size, anima[0].nowy* size, SRCPAINT);
	//��ʾ
	dc->BitBlt(0, 0, rect.Width(), rect.Height(), mdc, 0, 0, SRCCOPY);
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
		case 1:
			anima[0].nextFrame();//���½�ɫ����
			break;
		case 2:
			for (int i = 1; i < animaNum; i++) {//���µƶ���
				anima[i].nextFrame();
			}
			break;
		default:
			break;
	}
	Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}

//��Ӽ�����Ӧ
BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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

