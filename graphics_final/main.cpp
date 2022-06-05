using namespace std;
#include <iostream>
#include<math.h>
#include<stack>
#include <fstream>
#include <windows.h>
#include <list>
#include <gdiplus.h>
#include <vector>
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <tchar.h>
#include <windows.h>
//other
#define SAVE 01
#define LOAD 02
#define CLEAR 03
//cursor shape
#define HAND 11
#define STANDARD 12
#define CROSS 13
//color
#define Pink 21
#define Green 22
#define Purple 23
#define Black 24
//Line
#define LINE_DDA 31
#define MIDPOINT_LINE 32
#define PARAMETRIC 33
//Circle
#define DIRECT 41
#define POLAR 42
#define ITERATIVE_POLAR 43
#define MIDPOINT_CIRCLE 44
#define MIDPOINT_MODIFIED 45
#define FILLING_LINES 46
#define FILLING_CIRCLES 47
//Ellipse
#define DIRECT_ELLIPSE 51
#define POLAR_ELLIPSE 52
#define MIDPOINT_ELLIPSE 53
//Curves
#define SQUARE_HERMIT 61
#define RECTANGLE_BEZIR 62
#define CARDINAL_SPLINE 63
//Filing
#define CONVEX 71
#define NON_CONVEX 72
#define RECURSIVE 73
#define NON_RECURSIVE 74
//clipping
#define CIRCLE_POINT 81
#define CIRCLE_LINE 82
#define  RECTANGLE_POINT 83
#define RECTANGLE_LINE 84
#define RECTANGLE_POLYGON 85
#define SQUARE_POINT 86
#define SQUARE_LINE 87


LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void draw(HDC hdc);
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

LPCSTR cursorShape = IDC_ARROW;
COLORREF color=RGB(0,0,0);
static int i=0;
int choice=0;
string data="";


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{

    HWND hwnd;

    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    /* Use white colour as the background of the window */
    COLORREF background = RGB(255, 255, 255);
    wincl.hbrBackground = CreateSolidBrush(background);

    if (!RegisterClassEx (&wincl))
        return 0;
    hwnd = CreateWindowEx (
           0,
           szClassName,
           _T("Code::Blocks Template Windows App"),
           WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           900,
           544,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

void Menu (HWND hWnd)
{
    HMENU mainMenu = CreateMenu();

    HMENU cursorShape  = CreateMenu();
    AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)cursorShape, _T("Pick a Cursor Shape!"));
    AppendMenu(cursorShape, MF_STRING, HAND, _T("Hand"));
    AppendMenu(cursorShape, MF_STRING, STANDARD, _T("standard"));
    AppendMenu(cursorShape, MF_STRING, CROSS, _T("cross"));

    HMENU colors  = CreateMenu();
     AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)colors, _T("Pick a Color !"));
    AppendMenu(colors , MF_STRING, Pink, _T("Pink"));
    AppendMenu(colors , MF_STRING, Green, _T("Green"));
    AppendMenu(colors , MF_STRING, Purple, _T("Purple"));
    AppendMenu(colors , MF_STRING, Black, _T("Black"));


    HMENU  Line = CreateMenu();
     AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Line, _T("Draw a line?"));
    AppendMenu(Line , MF_STRING, LINE_DDA, _T("DDA"));
    AppendMenu(Line , MF_STRING, MIDPOINT_LINE, _T("Mid-point"));
    AppendMenu(Line , MF_STRING, PARAMETRIC, _T("Parametric"));


    HMENU Circle = CreateMenu();
     AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Circle , _T("Draw a circle?"));
    AppendMenu(Circle  , MF_STRING, DIRECT, _T("Direct"));
    AppendMenu(Circle , MF_STRING, POLAR, _T("Polar"));
    AppendMenu(Circle  , MF_STRING, ITERATIVE_POLAR, _T("Iterative Polar"));
    AppendMenu(Circle , MF_STRING, MIDPOINT_CIRCLE, _T("Mid-point"));
    AppendMenu(Circle  , MF_STRING, MIDPOINT_MODIFIED, _T("Modified mid-point"));
     AppendMenu(Circle , MF_STRING, FILLING_LINES, _T("Filling with Lines"));
    AppendMenu(Circle  , MF_STRING, FILLING_CIRCLES, _T("Filling with circles"));

    HMENU  ELLLPSE = CreateMenu();
     AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)ELLLPSE , _T("Draw an Ellipse?"));
    AppendMenu(ELLLPSE  , MF_STRING, DIRECT_ELLIPSE, _T("Direct"));
    AppendMenu(ELLLPSE , MF_STRING, POLAR_ELLIPSE, _T("Polar"));
    AppendMenu(ELLLPSE  , MF_STRING, MIDPOINT_ELLIPSE, _T("Midpoint"));


    HMENU CURVES = CreateMenu();
     AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)CURVES , _T("Draw a Curve?"));
    AppendMenu(CURVES  , MF_STRING, CARDINAL_SPLINE, _T("Cardinal spline"));
    AppendMenu(CURVES , MF_STRING, SQUARE_HERMIT, _T("Filing square with hermit"));
    AppendMenu(CURVES , MF_STRING, RECTANGLE_BEZIR, _T("Filling rectngle with bezir "));

    HMENU Clipping = CreateMenu();
     AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Clipping , _T("Do a clipping?"));
    AppendMenu(Clipping , MF_STRING, CIRCLE_POINT, _T("Circle point clipping"));
    AppendMenu(Clipping , MF_STRING, CIRCLE_LINE, _T("Circle line clipping"));
    AppendMenu(Clipping , MF_STRING, RECTANGLE_POINT, _T("Rectangle point clipping"));
    AppendMenu(Clipping , MF_STRING, RECTANGLE_LINE, _T("Rectangle line clipping"));
    AppendMenu(Clipping , MF_STRING, RECTANGLE_POLYGON, _T("Rectangle polygon clipping"));
    AppendMenu(Clipping , MF_STRING, SQUARE_POINT, _T("Square point clipping"));
    AppendMenu(Clipping , MF_STRING, SQUARE_LINE, _T("Square line clipping"));




      HMENU  Filling = CreateMenu();
     AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Filling , _T("Filling?"));
    AppendMenu(Filling  , MF_STRING, CONVEX, _T("Convex"));
    AppendMenu(Filling , MF_STRING, NON_CONVEX, _T("Non_convex"));
    AppendMenu(Filling  , MF_STRING,RECURSIVE, _T("Recursive flood fill"));
     AppendMenu(Filling  , MF_STRING, NON_RECURSIVE, _T("Non_recursive flood fill"));


     HMENU other = CreateMenu();
     AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)other , _T("More options"));
    AppendMenu(other  , MF_STRING, SAVE, _T("Save"));
    AppendMenu(other , MF_STRING, LOAD, _T("Load"));
    AppendMenu(other , MF_STRING, CLEAR, _T("Clear"));

    SetMenu(hWnd,mainMenu);

}


//*************************************LINE ALGORITHMS********************************



void DDA(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color) {
	int dx = xe - xs;
	int dy = ye - ys;
	SetPixel(hdc, xs, ys, color);
	if (abs(dx) >= abs(dy)) {
		int x = xs, xinc = dx > 0 ? 1 : -1;
		double y = ys, yinc = (double)dy / dx*xinc;
		while (x != xe)
		{
			x += xinc; y += yinc;
			SetPixel(hdc, x, round(y), color);
		}
	}
	else {
		int y = ys, yinc = dy > 0 ? 1 : -1;
		double x = (double)xs, xinc =  (double)dx / dy*yinc;
		while (y != ye)
		{
			x += xinc; y += yinc;
			SetPixel(hdc, round(x), y, color);
		}
	}
}

void Parametric(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
	int x, y;
	for (double t=0; t<1; t+=0.001) {
		 x=x1+((x2-x1)*t);
         y=y1+((y2-y1)*t);
		SetPixel(hdc, x, y, color);
	}
}


void midPointLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
     int dx = x2-x1;
    int dy = y2-y1;
    double slope = (((double)dy)/dx);

    if(slope < 1 && slope > 0)
    {
        if(x1>x2)
        {
            swap(x1,x2);
            swap(y1,y2);
            dy = y2-y1;
            dx = x2-x1;
        }
        int x = x1, y = y1;
        int d = dx - (2 * dy);
        int change1 = 2*(dx-dy);
        int change2 = -2*dy;
        SetPixel(hdc,x,y,color);
        while(x<x2)
        {
            if(d<=0)
            {
                d+=change1;
                y++;
            }
            else
                d+=change2;
            x++;
            SetPixel(hdc,x,y,color);
        }
    }
    else if(slope > 1)
    {
        if(y1>y2)
        {
            swap(x1,x2);
            swap(y1,y2);
            dy = y2-y1;
            dx = x2-x1;
        }

        int x = x1, y = y1;
        int d = (2 * dx) - dy;
        int change1 = 2*(dx-dy);
        int change2 = 2*dx;

        SetPixel(hdc,x,y,color);

        while(y<y2)
        {
            if(d>=0)
            {
                d+=change1;
                x++;
            }
            else
                d+=change2;

            y++;
            SetPixel(hdc,x,y,color);
        }
    }
    else if(slope > -1 && slope < 0)
    {
        if(x1<x2)
        {
            swap(x1,x2);
            swap(y1,y2);
            dy = y2-y1;
            dx = x2-x1;
        }
        int x = x1, y = y1;
        int d = dx + (2 *dy);
        int change1 = 2*(dx+dy);
        int change2 = 2*dy;
        SetPixel(hdc,x,y,color);
        while(x>x2)
        {
            if(d>=0)
            {
                d+=change1;
                y++;
            }
            else
                d+=change2;
            x--;
            SetPixel(hdc,x,y,color);
        }
    }
    else
    {
        if(y1>y2)
        {
            swap(x1,x2);
            swap(y1,y2);
            dy = y2-y1;
            dx = x2-x1;
        }
        int x = x1, y = y1;
        int d = (2 * dx) + dy;
        int change1 = 2*(dx+dy);
        int change2 = 2*dx;
        SetPixel(hdc,x,y,color);
        while(y<y2)
        {
            if(d<=0)
            {
                d+=change1;
                x--;
            }
            else
                d+=change2;
            y++;
            SetPixel(hdc,x,y,color);
        }
    }
}

//*************************************CIRCLE ALGORITHMS********************************

void draw8points(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
	SetPixel(hdc, xc + x, yc + y, color);
	SetPixel(hdc, xc - x, yc + y, color);
	SetPixel(hdc, xc - x, yc - y, color);
	SetPixel(hdc, xc + x, yc - y, color);
	SetPixel(hdc, xc + y, yc + x, color);
	SetPixel(hdc, xc - y, yc + x, color);
	SetPixel(hdc, xc - y, yc - x, color);
	SetPixel(hdc, xc + y, yc - x, color);
}

void circleDirect(HDC hdc,int xc,int yc, int R,COLORREF color)
{
   int x = 0, y = R;
   int R2 = R*R;
	draw8points(hdc, xc, yc, x, y, color);
	while (x < y)
	{
		x++;
		y = round(sqrt((double)(R2 - x*x)));
		draw8points(hdc, xc, yc, x, y, color);
	}
}

void Polar(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=R,y=0;
    double theta=0,dtheta=1.0/R;
   draw8points(hdc,xc,yc,x,y,color);
    while(x>y)
    {
    theta+=dtheta;
    x=round(R*cos(theta));
    y=round(R*sin(theta));
    draw8points(hdc,xc,yc,x,y,color);
}
}
void iterativePolar(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    double x=R,y=0;
    double dtheta=1.0/R;
    double cdtheta=cos(dtheta),sdtheta=sin(dtheta);
    draw8points(hdc,xc,yc,R,0,color);
    while(x>y)
    {
    double x1=x*cdtheta-y*sdtheta;
    y=x*sdtheta+y*cdtheta;
    x=x1;
    draw8points(hdc,xc,yc,round(x),round(y),color);
}
}

void circleMidpoint(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
   draw8points(hdc,xc,yc,x,y,color);
    while(x<y)
    {
    if(d<0)
    d+=2*x+2;
    else
     {
    d+=2*(x-y)+5;
    y--;
    }
    x++;
    draw8points(hdc,xc,yc,x,y,color);
    }
}
void modifiedMidpoint(HDC hdc,int xc,int yc, int R,COLORREF color)
{
        int x=0,y=R;
        int d=1-R;
        int c1=3, c2=5-2*R;
        draw8points(hdc,xc,yc,x,y,color);
        while(x<y)
        {
        if(d<0)
        {
        d+=c1;
        c2+=2;
        }
        else
         {
        d+=c2;
        c2+=4;
        y--;
        }
        c1+=2;
        x++;
        draw8points(hdc,xc,yc,x,y,color);
        }
}

void draw2points_line(HDC hdc,int x,int y,int xc,int yc,int q,COLORREF color)
{
    switch(q)
    {
    case 2:
        Parametric(hdc,xc+y,yc-x,xc,yc,color);
        Parametric(hdc,xc+x,yc-y,xc,yc,color);
        break;
    case 3:
        Parametric(hdc,xc-y,yc+x,xc,yc,color);
        Parametric(hdc,xc-x,yc+y,xc,yc,color);
        break;
    case 1:
        Parametric(hdc,xc-x,yc-y,xc,yc,color);
        Parametric(hdc,xc-y,yc-x,xc,yc,color);
        break;
    case 4:
       Parametric(hdc,xc+x,yc+y,xc,yc,color);
       Parametric(hdc,xc+y,yc+x,xc,yc,color);
        break;
    }
}

void lineFilling(HDC hdc,int xc,int yc, int r,int q,COLORREF color)
{
    int x=0;
    int y=r;
    int d=1-r;
    int c1=3, c2=5-(2*r);
    draw2points_line(hdc,x,y,xc,yc,q,color);
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {
            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        draw2points_line(hdc,x,y,xc,yc,q,color);
    }

}

void draw2points_circle(HDC hdc, int xc, int yc, int a, int b, COLORREF color, int quarter)
{
    if (quarter == 3)
    {
        SetPixel(hdc, xc + b, yc + a, color);
        SetPixel(hdc, xc + a, yc + b, color);
    }
    else if (quarter == 4)
    {
        SetPixel(hdc, xc - a, yc + b, color);
        SetPixel(hdc, xc - b, yc + a, color);
    }
    else if (quarter == 1)
    {
        SetPixel(hdc, xc - a, yc - b, color);
        SetPixel(hdc, xc - b, yc - a, color);
    }
    else if (quarter == 2)
    {
        SetPixel(hdc, xc + a, yc - b, color);
        SetPixel(hdc, xc + b, yc - a, color);
    }
}
void circleFilling(HDC hdc,int xc,int yc, int R,int q,COLORREF color)
{

while(R!=0){
int x=R,y=0;
double theta=0,dtheta=1.0/R;
draw2points_circle(hdc,xc,yc,x,y,color,q);
while(x>y)
{
theta+=dtheta;
x=round(R*cos(theta));
y=round(R*sin(theta));
draw2points_circle(hdc,xc,yc,x,y,color,q);

}
R--;
}
}

//*************************************ELLIPSE ALGORITHMS********************************
void draw4Points(HDC hdc,int h,int k,int x,int y,COLORREF color)
{
    SetPixel(hdc,h+x,k+y,color);
    SetPixel(hdc,h+x,k-y,color);
    SetPixel(hdc,h-x,k-y,color);
    SetPixel(hdc,h-x,k+y,color);
}

void polarEllipse(HDC hdc,int xc,int yc,int rx,int ry,COLORREF color)
{
    float x=rx;
    float y=0;
    float theta=0;

    float inc;
    if(rx > ry)
        inc = 1.0/rx;
    else
        inc = 1.0/ry;

    do
    {
       draw4Points(hdc,xc,yc,round(x),round(y),color);
        theta+=inc;
        x=(rx*cos(theta));
        y=(ry*sin(theta));
    }
    while(x > 0);
}

void directEllipse(HDC hdc,int xc,int yc,int rx,int ry)
{
    double rx2 = rx*rx;
    double ry2 = ry*ry;
    if(rx > ry)
    {
        int x=0,y=ry;
        do
        {
             draw4Points(hdc,xc,yc,round(x),round(y),color);
            x++;
            y=round(sqrt(ry2 - ((ry2 * (x*x)) / rx2)));

        }
        while(x < rx);
    }
    else
    {
        int x=rx,y=0;
        do
        {
             draw4Points(hdc,xc,yc,round(x),round(y),color);
            y++;
            x=round(sqrt(rx2 - ((rx2 * (y*y)) / ry2)));

        }
        while(y < ry);
    }
}


void midpointEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{
    int x = 0, y = b;
    draw4Points(hdc, xc, yc, x, y, c);
    int a2 = a * a;
    int b2 = b * b;
    int d = (b2) - (a2 * b) + round(a2 / 4.0);
    int d1 = (3 * b2) - (2 * b * a2) + (2 * a2);
    int d2 = (3 * b2);
    int change1 = 2 * b2 + 2 * a2;
    int change2 = 2 * b2;
    while(d1 < a * a + b * b)
    {
        if(d > 0)
            y--, d += d1, d1 += change1, d2 += change2;
        else
            d += d2, d1 += change2, d2 += change2;
        x++;
        draw4Points(hdc, xc, yc, x, y, c);
    }
    d1 = -2 * a2 * y + 3 * a2;
    d2 = 2 * b2 * x + 2 + d1;
    change1 = 2 * a2;
    change2 = 2 * (b2 + a2);
    while(y >= 0)
    {
        if(d > 0)
            d += d1, d1 += change1, d2 += change1;
        else
            x++, d += d2, d1 += change1, d2 += change2;
        y--;
        draw4Points(hdc, xc, yc, x, y, c);
    }
}

//*************************************CURVE ALGORITHMS********************************
struct Vector
{
    double v[2];
    Vector(double x = 0, double y = 0)
    {
        v[0] = x;
        v[1] = y;
    }
    double& operator[](int i)
    {
        return v[i];
    }

};
void hermite_cardinial(HDC hdc,Vector& p1, Vector& T1, Vector& p2, Vector& T2, COLORREF c)
{

    double a0 = p1[0], a1 = T1[0],
           a2 = -3 * p1[0] - 2 * T1[0] + 3 * p2[0] - T2[0],
           a3 = 2 * p1[0] + T1[0] - 2 * p2[0] + T2[0];
    double b0 = p1[1], b1 = T1[1],
           b2 = -3 * p1[1] - 2 * T1[1] + 3 * p2[1] - T2[1],
           b3 = 2 * p1[1] + T1[1] - 2 * p2[1] + T2[1];
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t*t, t3 = t2*t;
        double x = a0 + a1*t + a2*t2 + a3*t3;
        double y = b0 + b1*t + b2*t2 + b3*t3;
            SetPixel(hdc,round(x), round(y),c);


    }
}

void DrawCardinalSpline(HDC hdc,Vector P[],int n,int c,COLORREF C)
{
double c1=c/2;
Vector T[n];
for(int i=1; i<n-1; i++){

    T[i][0]=c1*(P[i+1][0]-P[i-1][0]);
    T[i][1]=c1*(P[i+1][1]-P[i-1][1]);
}
T[0][0]=c1*(P[1][0]-P[0][0]);
T[0][1]=c1*(P[1][1]-P[0][1]);

T[n-1][0]=c1*(P[n-1][0]-P[n-2][0]);
T[n-1][1]=c1*(P[n-1][1]-P[n-2][1]);
for(int i=0; i<n-1; i++){

   hermite_cardinial(hdc,P[i],T[i],P[i+1],T[i+1],C);

}
}

void DrawHermiteCurve(HDC hdc,int x1,int y1,int x2,int y2,COLORREF c,int cx,int cy,int RR2)
{
    int a,b;
    double a0 = x1, a1 = 50,
           a2 = -3 * x1 - 2 * 50 + 3 * x2 - 50,
           a3 = 2 * x1 + 50 - 2 * x2 + 50;
    double b0 = y1, b1 = 30,
           b2 = -3 * y1 - 2 *30 + 3 * y2 - 60,
           b3 = 2 * y1 + 30 - 2 * y2 + 60;
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t*t, t3 = t2*t;
        double x = a0 + a1*t + a2*t2 + a3*t3;
        double y = b0 + b1*t + b2*t2 + b3*t3;
        a=cx-x;
        b=cy-y;
    if(x>=cx&&x<=(cx+RR2)&&y>=cy&&y<=(cy+RR2)){
        SetPixel(hdc,round(x), round(y),c);
        }


    }
}


void drawhermite(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color,int cx,int cy,int RR){
int dx=xe-xs;
int dy=ye-ys;
int yy=ye+RR;
//SetPixel(hdc,xs,ys,color);
DrawHermiteCurve( hdc, xs, ys,xs,yy,color, cx, cy , RR );
if(abs(dx)>=abs(dy))
{
int x=xs,xinc= dx>0?1:-1;
double y=ys,yinc=(double)dy/dx*xinc;
while(x!=xe)
{
x+=xinc;
y+=yinc;
SetPixel(hdc,x,round(y),color);
yy=round(y)+RR;
DrawHermiteCurve( hdc, x, round(y),x,yy,color, cx, cy , RR );
}
}
else
{
int y=ys,yinc= dy>0?1:-1;
double x=xs,xinc=(double)dx/dy*yinc;
while(y!=ye)
{
x+=xinc;
y+=yinc;
SetPixel(hdc,round(x),y,color);
}
}
}

void square_hermite(HDC hdc,int xc,int yc,int dist,COLORREF c)
{
int x1,y1;
//dist=100;
//cout<<"enter the square size "<<endl;
//cin>>dist;
x1=xc+dist;
y1=yc+dist;
Parametric(hdc,xc,yc,x1,yc,c);
drawhermite(hdc,xc,yc,x1,yc,c,xc,yc,dist);
Parametric(hdc,xc,yc,xc,y1,c);

Parametric(hdc,xc,y1,x1,y1,c);

Parametric(hdc,x1,yc,x1,y1,c);

}
void hermite2(HDC hdc,int x1,int y1,int x2,int y2,int u1,int u2,int u3,int u4,COLORREF c,int cx,int cy,int RR2,int RR3)
{
    int a,b;
    double a0 = x1, a1 = u1,
           a2 = -3 * x1 - 2 * u1 + 3 * x2 - u2,
           a3 = 2 * x1 + u1 - 2 * x2 + u2;
    double b0 = y1, b1 = u3,
           b2 = -3 * y1 - 2 *u3 + 3 * y2 - u4,
           b3 = 2 * y1 + u3 - 2 * y2 + u4;
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t*t, t3 = t2*t;
        double x = a0 + a1*t + a2*t2 + a3*t3;
        double y = b0 + b1*t + b2*t2 + b3*t3;
        a=cx-x;
        b=cy-y;
    if(x>=cx&&x<=(cx+RR2)&&y>=cy&&y<=(cy+RR3)){
        SetPixel(hdc,round(x), round(y),c);
        }


    }
}
void drawbeziercurve( HDC hdc,int x1,int y1,int x2,int y2,COLORREF c,int cx,int cy,int RR2,int RR3 ){

     int t1=50,t2=60,t3=30,t4=60;
     hermite2( hdc, x1, y1, x2, y2,t1,t2,t3,t4, c, cx, cy, RR2,RR3);
}
void drawbezier(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color,int cx,int cy,int RR,int RR1){
int dx=xe-xs;
int dy=ye-ys;
int xa=xs+RR;
//SetPixel(hdc,xs,ys,color);
drawbeziercurve( hdc, xs, ys,xa,ys,color, cx, cy , RR ,RR1);
if(abs(dx)>=abs(dy))
{
int x=xs,xinc= dx>0?1:-1;
double y=ys,yinc=(double)dy/dx*xinc;
while(x!=xe)
{
x+=xinc;
y+=yinc;
//SetPixel(hdc,x,round(y),color);
 xa=x+RR;
drawbeziercurve( hdc, x, round(y),xa,round(y),color, cx, cy , RR ,RR1);
}
}
else
{
int y=ys,yinc= dy>0?1:-1;
double x=xs,xinc=(double)dx/dy*yinc;
while(y!=ye)
{
x+=xinc;
y+=yinc;
 xa= round(x)+RR;
drawbeziercurve( hdc, round(x), y,xa,y,color, cx, cy , RR ,RR1);
}
}

}
void rec_bezir(HDC hdc,int xc,int yc,int dist,int dist1,COLORREF c)
{
int x1,y1;

x1=xc+dist;
y1=yc+dist1;
Parametric(hdc,xc,yc,x1,yc,c);
drawbezier(hdc,xc,yc,xc,y1,c,xc,yc,dist,dist1);

Parametric(hdc,xc,yc,xc,y1,c);

Parametric(hdc,xc,y1,x1,y1,c);

Parametric(hdc,x1,yc,x1,y1,c);

}


//*************************************FILING ALGORITHMS********************************
void floodFill_recursive(HDC hdc,int x ,int y,COLORREF bc,COLORREF fc)
{
        COLORREF c = GetPixel(hdc,x,y);
        if (c==bc||c==fc)return;
        SetPixel(hdc,x,y,fc);
        floodFill_recursive(hdc,x+1,y,bc,fc);
        floodFill_recursive(hdc,x-1,y,bc,fc);
        floodFill_recursive(hdc,x,y-1,bc,fc);
        floodFill_recursive(hdc,x,y+1,bc,fc);
}
void floodFill_nonrecursive(HDC hdc,int x ,int y,COLORREF bc,COLORREF fc)
{

    stack<int> Sx;
    stack<int> Sy;
     Sx.push(x);
    Sy.push(y);

    while(! Sx.empty())
    {
        int top_x =  Sx.top();
         Sx.pop();
        int top_y = Sy.top();
        Sy.pop();
        COLORREF c= GetPixel(hdc,top_x,top_y);
        if(c != bc && c != fc)
        {
            SetPixel(hdc,top_x,top_y,fc);
            Sx.push(top_x+1);
            Sy.push(top_y);

             Sx.push(top_x);
            Sy.push(top_y+1);

             Sx.push(top_x-1);
            Sy.push(top_y);

             Sx.push(top_x);
            Sy.push(top_y-1);
        }
    }
}
struct Entry
{
    int xmin,xmax;
};

void InitEntries(Entry table[])
{
    for(int i=0; i < 800; i++)
        {
            table[i].xmin =  10000;
            table[i].xmax = - 10000;
        }
}
void ScanEdge(POINT v1,POINT v2,Entry table[])
{
    if(v1.y==v2.y)return;
    if(v1.y>v2.y)swap(v1,v2);
    double minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
    double x=v1.x;
    int y=v1.y;
    while(y<v2.y){
            if(x<table[y].xmin)table[y].xmin=(int)ceil(x);
            if(x>table[y].xmax)table[y].xmax=(int)floor(x);
            y++;
            x+=minv;
            }
}
void DrawSanLines(HDC hdc,Entry table[],COLORREF color)
{
for(int y=0;y<800;y++)
if(table[y].xmin<table[y].xmax)
for(int x=table[y].xmin;x<=table[y].xmax;x++)
SetPixel(hdc,x,y,color);
}
void convex(HDC hdc,POINT p[],int n,COLORREF color)
{
    Entry *table=new Entry[800];
    InitEntries(table);
    POINT v1=p[n-1];
    for(int i=0;i<n;i++){
            POINT v2=p[i];
            ScanEdge(v1,v2,table);
            v1=p[i];
            }
    DrawSanLines(hdc,table,color);
    delete table;
}


struct EdgeRec
{
double x;
double minv;
int ymax;
bool operator<(EdgeRec r)
{
return x<r.x;
}
};
typedef list<EdgeRec> EdgeList;


EdgeRec InitEdgeRec(POINT& v1,POINT& v2)
{
if(v1.y>v2.y)swap(v1,v2);
EdgeRec rec;
rec.x=v1.x;
rec.ymax=v2.y;
rec.minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
return rec;
}


void InitEdgeTable(POINT *polygon,int n,EdgeList table[])
{
POINT v1=polygon[n-1];
for(int i=0;i<n;i++)
{
POINT v2=polygon[i];
if(v1.y==v2.y){v1=v2;continue;}
EdgeRec rec=InitEdgeRec(v1, v2);
table[v1.y].push_back(rec);
v1=polygon[i];
}
}

void non_convex(HDC hdc,POINT *polygon,int n,COLORREF c)
{
EdgeList *table=new EdgeList [800];
InitEdgeTable(polygon,n,table);
int y=0;
while(y<800 && table[y].size()==0)y++;
if(y==800)return;
EdgeList ActiveList=table[y];
while (ActiveList.size()>0)
{
ActiveList.sort();
for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
{
int x1=(int)ceil(it->x);
it++;
int x2=(int)floor(it->x);
for(int x=x1;x<=x2;x++)SetPixel(hdc,x,y,c);
}
y++;
EdgeList::iterator it=ActiveList.begin();
while(it!=ActiveList.end())
if(y==it->ymax) it=ActiveList.erase(it); else it++;
for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
it->x+=it->minv;
ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
}
delete[] table;
}



//*************************************CLIPPING ALGORITHMS********************************
void swap(int& x1, int& y1, int& x2, int& y2)
{
 int tmp = x1;
 x1 = x2;
 x2 = tmp;
 tmp = y1;
 y1 = y2;
 y2 = tmp;
}
void circlePointClipping(HDC hdc, int x1, int y1, COLORREF c,int cx,int cy,int RR2)
{
    int a,b;
            a=cx-x1;
            b=cy-y1;
            if(sqrt(a*a+b*b)<=RR2){
   SetPixel(hdc, x1, y1, c);
   }

 }

 void circleLineClipping(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c,int cx,int cy,int RR2)
{
       int a,b;
 int dx = x2 - x1; // Different of x
 int dy = y2 - y1;// Different of y
 if (abs(dy) <= abs(dx))// if the M<1
 {
  if (x1 > x2)swap(x1, y1, x2, y2);
      a=cx-x1;
            b=cy-y1;
            if(sqrt(a*a+b*b)<=RR2){
  SetPixel(hdc, x1, y1, c);}//the center
  int x = x1;
  while (x < x2)
  {
   x++;
   double y = y1 + (double)(x - x1)*dy / dx; //y=y+m
            a=cx-x;
            b=cy-y;
            if(sqrt(a*a+b*b)<=RR2){
   SetPixel(hdc, x, round(y), c);
   }
  }
 }
 else {
  if (y1 > y2)swap(x1, y1, x2, y2);
  SetPixel(hdc, x1, y1, c);
  int y = y1;

  while (y < y2)
  {
   y++;
   double x = x1 + (double)(y - y1)*dx / dy;//x+=1/m
            a=cx-x;
            b=cy-y;
            if(sqrt(a*a+b*b)<=RR2){
   SetPixel(hdc, round(x), y, c);
   }
  }
 }
}



void squarePointClipping(HDC hdc, int x1, int y1, COLORREF c,int cx,int cy,int RR2)
{
    int a,b;
            a=cx-x1;
            b=cy-y1;
            if(sqrt(a*a+b*b)<=RR2){
            if(x1>=cx&&x1<=(cx+RR2)&&y1>=cy&&y1<=(cy+RR2)){
			SetPixel(hdc, x1, y1, c);
			}
			}

	}
void squareLineClipping(HDC hdc, int xs, int ys, int xe, int ye, COLORREF c,int cx,int cy,int RR2)
{
      int dx=xe-xs;
int dy=ye-ys;
if(xs>=cx&&xs<=(cx+RR2)&&ys>=cy&&ys<=(cy+RR2)){
SetPixel(hdc,xs,ys,c);}
if(abs(dx)>=abs(dy))
{
int x=xs,xinc= dx>0?1:-1;
double y=ys,yinc=(double)dy/dx*xinc;
while(x!=xe)
{
x+=xinc;
y+=yinc;
if(x>=cx&&x<=(cx+RR2)&&y>=cy&&y<=(cy+RR2)){
    SetPixel(hdc,x,round(y),c);
}

}
}
else
{
int y=ys,yinc= dy>0?1:-1;
double x=xs,xinc=(double)dx/dy*yinc;
while(y!=ye)
{
x+=xinc;
y+=yinc;
if(x>=cx&&x<=(cx+RR2)&&y>=cy&&y<=(cy+RR2)){
SetPixel(hdc,round(x),y,c);
}
}
}
}
void  rectanglePointClipping(HDC hdc, int x1, int y1, COLORREF c,int cx,int cy,int RR2,int RR3)
{
    int a,b;
            a=cx-x1;
            b=cy-y1;
            if(sqrt(a*a+b*b)<=RR2){
            if(x1>=cx&&x1<=(cx+RR2)&&y1>=cy&&y1<=(cy+RR3)){
   SetPixel(hdc, x1, y1, c);
   }
   }

 }

void rectangleLineClipping(HDC hdc, int xs, int ys, int xe, int ye, COLORREF c,int cx,int cy,int RR2,int RR3)
{
    int dx=xe-xs;
int dy=ye-ys;
if(xs>=cx&&xs<=(cx+RR2)&&ys>=cy&&ys<=(cy+RR3)){
SetPixel(hdc,xs,ys,c);}
if(abs(dx)>=abs(dy))
{
int x=xs,xinc= dx>0?1:-1;
double y=ys,yinc=(double)dy/dx*xinc;
while(x!=xe)
{
x+=xinc;
y+=yinc;
if(x>=cx&&x<=(cx+RR2)&&y>=cy&&y<=(cy+RR3)){
    SetPixel(hdc,x,round(y),c);
}

}
}
else
{
int y=ys,yinc= dy>0?1:-1;
double x=xs,xinc=(double)dx/dy*yinc;
while(y!=ye)
{
x+=xinc;
y+=yinc;
if(x>=cx&&x<=(cx+RR2)&&y>=cy&&y<=(cy+RR3)){
SetPixel(hdc,round(x),y,c);
}
}
}
}

struct Vertex
{
double x,y;
Vertex(int x1=0,int y1=0)
{
x=x1;
y=y1;
}
};
typedef vector<Vertex> VertexList;
typedef bool (*IsInFunc)(Vertex& v,int edge);
typedef Vertex (*IntersectFunc)(Vertex& v1,Vertex& v2,int edge);

VertexList ClipWithEdge(VertexList p,int edge,IsInFunc In,IntersectFunc Intersect)
{
 VertexList OutList;
 Vertex v1=p[p.size()-1];
 bool v1_in=In(v1,edge);
 for(int i=0;i<(int)p.size();i++)
 {
 Vertex v2=p[i];
 bool v2_in=In(v2,edge);
 if(!v1_in && v2_in)
 {
 OutList.push_back(Intersect(v1,v2,edge));
 OutList.push_back(v2);
 }else if(v1_in && v2_in) OutList.push_back(v2);
 else if(v1_in) OutList.push_back(Intersect(v1,v2,edge));
 v1=v2;
 v1_in=v2_in;
 }
return OutList;
}

bool InLeft(Vertex& v,int edge)
{
return v.x>=edge;
}
bool InRight(Vertex& v,int edge)
{
return v.x<=edge;
}
bool InTop(Vertex& v,int edge)
{
return v.y>=edge;
}
bool InBottom(Vertex& v,int edge)
{
return v.y<=edge;
}

Vertex VIntersect(Vertex& v1,Vertex& v2,int xedge)
{
Vertex res;
res.x=xedge;
res.y=v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
return res;
}
Vertex HIntersect(Vertex& v1,Vertex& v2,int yedge)
{
Vertex res;
res.y=yedge;
res.x=v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
return res;
}

void PolygonClip(HDC hdc,POINT *p,int n,int xleft,int ytop,int xright,int ybottom,COLORREF color)
{
VertexList vlist;

for(int i=0;i<3;i++)
{vlist.push_back(Vertex(p[i].x,p[i].y));
}
vlist=ClipWithEdge(vlist,xleft,InLeft,VIntersect);
vlist=ClipWithEdge(vlist,ytop,InTop,HIntersect);
vlist=ClipWithEdge(vlist,xright,InRight,VIntersect);
vlist=ClipWithEdge(vlist,ybottom,InBottom,HIntersect);
Vertex v1=vlist[vlist.size()-1];
for(int i=0;i<(int)vlist.size();i++)
{
Vertex v2=vlist[i];
MoveToEx(hdc,round(v1.x),round(v1.y),NULL);
Parametric(hdc,round(v1.x),round(v1.y),round(v2.x),round(v2.y),color);
v1=v2;
}
}
//*************************************Rectangle and square ALGORITHMS********************************
void DrawRec(HDC hdc,int xc,int yc,int dist,int dist1,COLORREF c)
{
int x1,y1;
x1=xc+dist;
y1=yc+dist1;
Parametric(hdc,xc,yc,x1,yc,c);

Parametric(hdc,xc,yc,xc,y1,c);

Parametric(hdc,xc,y1,x1,y1,c);

Parametric(hdc,x1,yc,x1,y1,c);

}

void DrawSquare(HDC hdc,int xc,int yc,int dist,COLORREF c)
{
int x1,y1;
//dist=100;
//cout<<"enter the square size "<<endl;
//cin>>dist;
x1=xc+dist;
y1=yc+dist;
Parametric(hdc,xc,yc,x1,yc,c);

Parametric(hdc,xc,yc,xc,y1,c);

Parametric(hdc,xc,y1,x1,y1,c);

Parametric(hdc,x1,yc,x1,y1,c);

}

//*************************************OTHER ALGORITHMS********************************

void saveData()
{
    ofstream f;
    f.open ("data.txt",ios::app);
    f << data;
    f.close();
}
void save(string shape,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,COLORREF color)
{
   data += shape + " " + to_string(p1)+ " " +to_string(p2) + " " + to_string(p3) + " " + to_string(p4) + " " + to_string(p5) + " " + to_string(p6) +" " +to_string(p7) + " " + to_string(p8) +" " + to_string(color) + "\n";
}
void loadData(HDC hdc)
{

    fstream f;
     f.open("data.txt",ios::in);
    if (f.is_open())
    { string obj;
     while ( getline (f,obj) )
        {
        vector<string> shape;
         string temp="";
         for(int i = 0; i < obj.length(); i++)
            {
               if(obj[i] != ' ')
                {
                    temp += obj[i];
                }
                else
                {
                    shape.push_back(temp);
                    temp = "";
                }

            }
            shape.push_back(temp);
            temp = "";
            COLORREF c= stoi(shape[shape.size()-1]);
            if("LINE_DDA" == shape[0])
            {
                DDA(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c);
            }
             else if("PARAMETRIC" == shape[0])
            {
                Parametric(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c);
            }
             else if("MIDPOINT_LINE" == shape[0])
            {
                midPointLine(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c);
            }
            else if("DIRECT" == shape[0])
            {
                circleDirect(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
            }
             else if("POLAR" == shape[0])
            {
                Polar(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
            }
             else if("ITERATIVE_POLAR" == shape[0])
            {
                iterativePolar(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
            }
             else if("MIDPOINT_CIRCLE" == shape[0])
            {
               circleMidpoint(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
            }
             else if("MIDPOINT_MODIFIED" == shape[0])
            {
                modifiedMidpoint(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
            }
             else if("FILLING_LINES" == shape[0])
            {
             lineFilling(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c);
            }

            else if("FILLING_CIRCLES" == shape[0])
            {
             circleFilling(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c);
            }

            else if("DIRECT_ELLIPSE" == shape[0])
            {
             directEllipse(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]));
            }
            else if("POLAR_ELLIPSE" == shape[0])
            {
             polarEllipse(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c);
            }
            else if("MIDPOINT_ELLIPSE" == shape[0])
            {
             midpointEllipse(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c);
            }
            else if("CIRCLE_POINT" == shape[0])
            {
             circlePointClipping(hdc,stoi(shape[1]),stoi(shape[2]),c,stoi(shape[3]),stoi(shape[4]),stoi(shape[5]));
            }
            else if("CIRCLE_LINE" == shape[0])
            {
            circleLineClipping(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c,stoi(shape[5]),stoi(shape[6]),stoi(shape[7]));
            }
            else if("SQUARE" == shape[0])
            {
            DrawSquare(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
            }
            else if("SQUARE_POINT" == shape[0])
            {
             squarePointClipping(hdc,stoi(shape[1]),stoi(shape[2]),c,stoi(shape[3]),stoi(shape[4]),stoi(shape[5]));
            }
            else if("SQUARE_LINE" == shape[0])
            {
             squareLineClipping(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c,stoi(shape[5]),stoi(shape[6]),stoi(shape[7]));
            }
            else if("REC" == shape[0])
            {
             DrawSquare(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
            }
             else if("RECTANGLE_POINT" == shape[0])
            {
             rectanglePointClipping(hdc,stoi(shape[1]),stoi(shape[2]),c,stoi(shape[3]),stoi(shape[4]),stoi(shape[5]),stoi(shape[6]));
            }
             else if("RECTANGLE_LINE" == shape[0])
            {
             squareLineClipping(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c,stoi(shape[5]),stoi(shape[6]),stoi(shape[7]));
            }
             else if("CARDINAL_SPLINE" == shape[0])
            {
               // square_hermite(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),color);
                       }
             else if("SQUARE_HERMITE" == shape[0])
            {
                square_hermite(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
                       }
             else if("RECTANGLE_BEZIR" == shape[0])
            {
                rec_bezir(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),stoi(shape[4]),c);
                       }

            else if("RECURSIVE" == shape[0])
            {
                floodFill_recursive(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
                       }
              else if("NON_RECURSIVE" == shape[0])
            {
                floodFill_nonrecursive(hdc,stoi(shape[1]),stoi(shape[2]),stoi(shape[3]),c);
                       }
        }

    f.close();}

}

int x_1,y_1,x_2,y_2,x_3,y_3;
int myRadius;
int radiusFilling,xFilling,yFilling;
POINT polygonPoints[5];
POINT polygonRectangle[5];
static Vector points[5];
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    switch (message)
    {
        case WM_CREATE:
        Menu(hwnd);
        break;
        case WM_COMMAND:
             i=0;
        switch(LOWORD(wParam))
        {
         case HAND:
            cursorShape = IDC_HAND;
             choice=0;
            break;
        case STANDARD:
            cursorShape = IDC_ARROW;
            choice=0;
            break;
        case CROSS:
            cursorShape = IDC_CROSS;
            choice=0;
            break;
        case Pink:
            color = RGB(255,20,147);
            choice=0;
            break;
        case Green:
            color = RGB(60,179,113);
            choice=0;
            break;
        case Purple:
            color = RGB(216,191,216);
            choice=0;
            break;
        case Black:
            color = RGB(0,0,0);
            choice=0;
        case CLEAR:
             data="";
            InvalidateRect(hwnd,NULL ,TRUE);
             choice=0;
        case SAVE:
            saveData();
            choice=0;
            break;
        case LOAD:
            loadData(hdc);
            choice=0;
            break;
        case FILLING_LINES :
            int quarterNum;
            cout <<"Enter quarter num to be filled !"<<endl;
            cin >> quarterNum;
            radiusFilling=myRadius;
            xFilling=x_1;
            yFilling=y_1;
            lineFilling(hdc,xFilling,yFilling,radiusFilling,quarterNum,color);
             save("FILLING_LINES",xFilling,yFilling,radiusFilling,quarterNum,0,0,0,0,color);
             choice=0;
             break;
      case FILLING_CIRCLES :
            quarterNum;
            cout <<"Enter quarter num to be filled !"<<endl;
            cin >> quarterNum;
            radiusFilling=myRadius;
            xFilling=x_1;
            yFilling=y_1;
            circleFilling(hdc,xFilling,yFilling,radiusFilling,quarterNum,color);
             save("FILLING_CIRCLES",xFilling,yFilling,radiusFilling,quarterNum,0,0,0,0,color);
             choice=0;
     break;
         default:
            choice = LOWORD(wParam);
            break;
        }

        case WM_LBUTTONDOWN:
//**************************line choices******************************************
if(choice== LINE_DDA){
        if(i==0){i++;
         // cout<<"i0";
        }
        else if(i==1){
                  //  cout<<"i1";
                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);

                      i++;

                    }
    else if (i==2){
                  // cout<<"i2";
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);

                    DDA(hdc,x_1,y_1,x_2,y_2,color);
                    save("LINE_DDA",x_1,y_1,x_2,y_2,0,0,0,0,color);
                    i=1;
                }}

else if(choice== PARAMETRIC){
     if(i==0){i++;
        }
        else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                      i++;

                    }
    else if (i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    Parametric(hdc,x_1,y_1,x_2,y_2,color);
                    save("PARAMETRIC",x_1,y_1,x_2,y_2,0,0,0,0,color);
                    i=1;
                }}

else if(choice== MIDPOINT_LINE){

        if(i==0){i++;
        }
        else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                      i++;

                    }
    else if (i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    midPointLine(hdc,x_1,y_1,x_2,y_2,color);
                    save("MIDPOINT_LINE",x_1,y_1,x_2,y_2,0,0,0,0,color);
                    i=1;
                }
}
//**************************circle choices******************************************
else if(choice== DIRECT){
     if(i==0){i++;
        }
        else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);

                      i++;

                    }
    else if (i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    POINT p1;
                    p1.x=x_2;
                    p1.y=y_2;
                   // polygonPoints.push_back(p1);
                    myRadius=sqrt(pow((x_2-x_1),2)+pow((y_2-y_1),2));
                    circleDirect(hdc,x_1,y_1,myRadius,color);
                    //polygonPoints.clear();
                    save("DIRECT",x_1,y_1,myRadius,0,0,0,0,0,color);
                    i=1;
                }

}
else if(choice==POLAR){
            if(i==0){i++;}
    else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                      i++;

                    }
    else if (i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    myRadius=sqrt(pow((x_2-x_1),2)+pow((y_2-y_1),2));
                    Polar(hdc,x_1,y_1,myRadius,color);
                    save("POLAR",x_1,y_1,myRadius,0,0,0,0,0,color);
                    i=1;
                }
}
else if(choice==ITERATIVE_POLAR){
            if(i==0){i++;}
    else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                      i++;

                    }
    else if (i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    myRadius=sqrt(pow((x_2-x_1),2)+pow((y_2-y_1),2));
                    iterativePolar(hdc,x_1,y_1,myRadius,color);
                    save("ITERATIVE_POLAR",x_1,y_1,myRadius,0,0,0,0,0,color);
                    i=1;
                }
}
else if(choice==MIDPOINT_CIRCLE){
            if(i==0){i++;}
    else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                      i++;

                    }
    else if (i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    myRadius=sqrt(pow((x_2-x_1),2)+pow((y_2-y_1),2));
                    circleMidpoint(hdc,x_1,y_1,myRadius,color);
                    save("MIDPOINT_CIRCLE",x_1,y_1,myRadius,0,0,0,0,0,color);
                    i=1;
                }
}
else if(choice==MIDPOINT_MODIFIED){
            if(i==0){i++;}
    else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                      i++;

                    }
    else if (i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    myRadius=sqrt(pow((x_2-x_1),2)+pow((y_2-y_1),2));
                    modifiedMidpoint(hdc,x_1,y_1,myRadius,color);
                    save("MIDPOINT_MODIFIED",x_1,y_1,myRadius,0,0,0,0,0,color);
                    i=1;
                }
}

//**************************ellipse choices******************************************
else if(choice==DIRECT_ELLIPSE){
            if(i==0){i++;}
else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    i++;
                }
    else if(i==2){

                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    int r_1 = abs(x_1  - x_2) ;
                    int r_2= abs(y_1 - y_2) ;
                    directEllipse(hdc,x_1,y_1,r_1,r_2);
                    save("DIRECT_ELLIPSE",x_1,y_1,r_1,r_2,0,0,0,0,color);
                    i=1;
                }

}

//polar ellipse
else if(choice==POLAR_ELLIPSE){
            if(i==0){i++;}
else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    i++;
                }
    else if(i==2){

                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    int r_1 = abs(x_1  - x_2) ;
                    int r_2= abs(y_1 - y_2) ;
                    polarEllipse(hdc,x_1,y_1,r_1,r_2,color);
                    save("POLAR_ELLIPSE",x_1,y_1,r_1,r_2,0,0,0,0,color);
                    i=1;
                }

}
else if(choice==MIDPOINT_ELLIPSE){
            if(i==0){i++;
            }
else if(i==1){
                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    i++;
                }
    else if(i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    int r_1 = abs(x_1  - x_2) ;
                    int r_2= abs(y_1 - y_2) ;
                    midpointEllipse(hdc,x_1,y_1,r_1,r_2,color);
                    save("MIDPOINT_ELLIPSE",x_1,y_1,r_1,r_2,0,0,0,0,color);
                    i=1;
                }}
//**************************curve choices******************************************
//cardinal splines
else if(choice==CARDINAL_SPLINE){
if (i==0){i++;
cout<<"i0";
}
else{
 points[i-1] = Vector(LOWORD(lParam), HIWORD(lParam));
            if (i== 5)
            {
                hdc = GetDC(hwnd);
                DrawCardinalSpline(hdc,points,5,2,RGB(255, 0, 0));
               // save("CARDINAL_SPLINE",x_1,y_1,r_1,r_2,0,0,0,0,color);
                ReleaseDC(hwnd, hdc);
                i = 0;
            }else i++;
            }
}

//square using hermite
else if(choice==SQUARE_HERMIT){
            if(i==0){i++;
            }
            else if(i==1){
                 x_1=LOWORD(lParam);
                y_1=HIWORD(lParam);
                i++;
            }
else if(i==2){
        int a = LOWORD(lParam)-x_1;
        int b = HIWORD(lParam)-y_1;
        int RR = sqrt(a*a+b*b);
                   square_hermite(hdc,x_1,y_1,RR,color);
                   save("SQUARE_HERMITE",x_1,y_1,RR,0,0,0,0,0,color);
                    i=1;
                }
}
//rectangle using bezir curve
else if(choice==RECTANGLE_BEZIR){
            if(i==0){i++;
            }
            else if(i==1){
                 x_1=LOWORD(lParam);
                y_1=HIWORD(lParam);
                i++;
            }
else if(i==2){
         int a = LOWORD(lParam)-x_1;
         int b = HIWORD(lParam)-y_1;
         int RR = sqrt(a*a+b*b);
        int RR1=100;

                   rec_bezir(hdc,x_1,y_1,RR,RR1,color);
                    save("RECTANGLE_BEZIR",x_1,y_1,RR,RR1,0,0,0,0,color);
                    i=1;
                }
}

//**************************clipping choices******************************************
//circle point
else if(choice==CIRCLE_POINT){
            if(i==0){i++;
             modifiedMidpoint(hdc,366,222,126,color);
             save("MIDPOINT_MODIFIED",366,222,126,0,0,0,0,0,color);
            }
else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    circlePointClipping(hdc,x_1,y_1,color,366,222,126);
                    save("CIRCLE_POINT",x_1,y_1,366,222,126,0,0,0,color);
                }
 }
//circle line clipping
 else if(choice==CIRCLE_LINE){
            if(i==0){i++;
             modifiedMidpoint(hdc,366,222,126,color);
             save("MIDPOINT_MODIFIED",366,222,126,0,0,0,0,0,color);
            }
else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    i++;
                }
else if(i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    circleLineClipping(hdc,x_1,y_1,x_2,y_2,color,366,222,126);
                    save("CIRCLE_LINE",x_1,y_1,x_2,y_2,366,222,126,0,color);
                    i=1;
                }
 }
 //square point clipping
 else if(choice==SQUARE_POINT){
            if(i==0){i++;
             DrawSquare(hdc,366,222,126,color);
             save("SQUARE",366,222,126,0,0,0,0,0,color);
            }
else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    squarePointClipping(hdc,x_1,y_1,color,366,222,126);
                    save("SQUARE_POINT",x_1,y_1,366,222,126,0,0,0,color);
                }
 }
//square line clipping
 else if(choice==SQUARE_LINE){
            if(i==0){i++;
              DrawSquare(hdc,366,222,126,color);
               save("SQUARE",366,222,126,0,0,0,0,0,color);
            }
else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    i++;

                }
else if(i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    squareLineClipping(hdc,x_1,y_1,x_2,y_2,color,366,222,126);
                    save("SQUARE_LINE",x_1,y_1,x_2,y_2,366,222,126,0,color);
                    i=1;
                }
 }
 //rectangle point clipping
 else if(choice==RECTANGLE_POINT){
            if(i==0){i++;
             DrawRec(hdc,366,222,126,100,color);
             save("REC",366,222,126,100,0,0,0,0,color);
            }
else if(i==1){

                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    rectanglePointClipping(hdc,x_1,y_1,color,366,222,126,100);
                     save("RECTANGLE_POINT",x_1,y_1,366,222,126,0,0,0,color);
                }
 }
//rectangle line clipping
 else if(choice==RECTANGLE_LINE){
            if(i==0){i++;
             DrawRec(hdc,366,222,126,100,color);
             save("REC",366,222,126,100,0,0,0,0,color);
            }
else if(i==1){
                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    i++;

                }
else if(i==2){
                    x_2=LOWORD(lParam);
                    y_2=HIWORD(lParam);
                    rectangleLineClipping(hdc,x_1,y_1,x_2,y_2,color,366,222,126,100);
                    save("RECTANGLE_LINE",x_1,y_1,x_2,y_2,366,222,126,100,color);
                    i=1;
                }}

//rectangle polygon clipping
 else if(choice==RECTANGLE_POLYGON){
            if(i==0){i++;
             DrawRec(hdc,366,222,126,100,color);
             save("REC",366,222,126,100,0,0,0,0,color);
            }
else if(i==1){
            polygonRectangle[0].x = LOWORD(lParam);
            polygonRectangle[0].y = HIWORD(lParam);
                     i++;
                }

else if(i==2){

           polygonRectangle[1].x = LOWORD(lParam);
           polygonRectangle[1].y = HIWORD(lParam);
                     i++;
                }
else if(i==3){

           polygonRectangle[2].x = LOWORD(lParam);
           polygonRectangle[2].y = HIWORD(lParam);
           PolygonClip(hdc,polygonRectangle,3,366,222,366+126,222+100, color);
                     i=1;
                }
}

//**************************filling choices******************************************
//flood fill recursive
else if(choice==RECURSIVE){
            if(i==0){i++;

            }
else if(i!=0){
                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    floodFill_recursive(hdc,x_1,y_1,color,RGB(178,34,34));
                    save("RECURSIVE",x_1,y_1,color,0,0,0,0,0,RGB(178,34,34));

                 i++;

                }
}
//flood fill non-recursive
else if(choice==NON_RECURSIVE){
            if(i==0){i++;

            }
else if(i!=0){
                    x_1=LOWORD(lParam);
                    y_1=HIWORD(lParam);
                    floodFill_nonrecursive(hdc,x_1,y_1,color,RGB(178,34,34));
                   save("NON_RECURSIVE",x_1,y_1,color,0,0,0,0,0,RGB(178,34,34));
                 i++;

                }
}

else if(choice==CONVEX){
            if(i==0){i++;}
else if(i==1){
        for (int j=0 ;j<5;j++){
            polygonPoints[j].x = LOWORD(lParam);
            polygonPoints[j].y = HIWORD(lParam);
                     }
                     Polygon(hdc, polygonPoints, 5);
                     i++;
                }


else if(i==2){

           polygonPoints[1].x = LOWORD(lParam);
           polygonPoints[1].y = HIWORD(lParam);
                     i++;
                }
else if(i==3){

           polygonPoints[2].x = LOWORD(lParam);
           polygonPoints[2].y = HIWORD(lParam);
                     i++;
                }
else if(i==4){

            polygonPoints[3].x = LOWORD(lParam);
            polygonPoints[3].y = HIWORD(lParam);
                     i++;
                }
else if(i==5){

          polygonPoints[4].x = LOWORD(lParam);
           polygonPoints[4].y = HIWORD(lParam);
           i++;
            Polygon(hdc, polygonPoints, 5);
                }
else if(i==6){

                    convex(hdc,polygonPoints,5,color);
                     i=1;
                }
 }

 else if(choice==NON_CONVEX ){
            if(i==0){i++;}
else if(i==1){
            polygonPoints[0].x = LOWORD(lParam);
            polygonPoints[0].y = HIWORD(lParam);

                     i++;
                }


else if(i==2){

           polygonPoints[1].x = LOWORD(lParam);
           polygonPoints[1].y = HIWORD(lParam);
                     i++;
                }
else if(i==3){

           polygonPoints[2].x = LOWORD(lParam);
           polygonPoints[2].y = HIWORD(lParam);
                     i++;
                }
else if(i==4){

            polygonPoints[3].x = LOWORD(lParam);
            polygonPoints[3].y = HIWORD(lParam);
                     i++;
                }
else if(i==5){

          polygonPoints[4].x = LOWORD(lParam);
           polygonPoints[4].y = HIWORD(lParam);
           i++;
            Polygon(hdc, polygonPoints, 5);
                }
else if(i==6){
                    non_convex(hdc,polygonPoints,5,color);
                     i=1;
                }
 }
break;
        case WM_SETCURSOR:
            SetCursor(LoadCursor(NULL,cursorShape));
        break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
