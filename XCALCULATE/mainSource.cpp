#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include "linkedList.h"
#include "R4DMatrix3n.h"
#include "R4DQuaternion.h"

#pragma warning(disable : 4996)

#pragma region DEFINICIONES
//MENU BUTTONS
#define BTN_ARIT 101
#define BTN_COMP 102
#define BTN_QUAT 103
//ARITMETIC FUNCTION
#define EDT_MATRIX1 110
#define EDT_MATRIX2 111
#define EDT_MATRIX3 112
#define BTN_ADD 113
#define BTN_SUB	 114
#define BTN_MULT 115
#define BTN_CLEANBOXA 116
//COMPOSITE FUNCTION
#define EDT_MATRIXC 120
#define EDT_TX 121
#define EDT_TY 122
#define EDT_TZ 123
#define EDT_RX 124
#define EDT_RY 125
#define EDT_RZ 126
#define EDT_SX 127
#define EDT_SY 128
#define EDT_SZ 129
#define EDT_PX 130
#define EDT_PY 131
#define EDT_PZ 132
#define EDT_RPOINTS 133
#define LBX_POINTS 134
#define BTN_RESTART 135
#define BTN_TRANS 136
#define BTN_ROTAT 137
#define BTN_SCALA 138
#define BTN_CLEANLIST 139
#define BTN_ADDP 140
#define BTN_DELP 141
#define BTN_CALCULATE 142
#define BTN_CLEANBOXC 143
//QUATERNION FUNCTION
#define EDT_ANGLE 150
#define EDT_VX 151
#define EDT_VY 152
#define EDT_VZ 153
#define EDT_RQ 154
#define BTN_RQ 155
#define BTN_CLEANBOXQ 156

#define PI 3.1416
#define TO_DEG(A) A*(180/PI)
#define TO_RAD(A) A*(PI/180)
#pragma endregion

#pragma region HANDLERS
HWND hwnd;
HWND hBtnArit;
HWND hBtnComp;
HWND hBtnQuat;
HWND hStMain;
//AritmeticMenu
HWND hEdtMatrix1;
HWND hEdtMatrix2;
HWND hEdtMatrix3;
HWND hBtnAdd;
HWND hBtnSub;
HWND hBtnMult;
HWND hBtnCleanBox;
HWND hStA1;
HWND hStA2;
HWND hStA3;
//CompositeMenu
HWND hEdtCompMatrix;
HWND hEdtTX;
HWND hEdtTY;
HWND hEdtTZ;
HWND hEdtRX;
HWND hEdtRY;
HWND hEdtRZ;
HWND hEdtSX;
HWND hEdtSY;
HWND hEdtSZ;
HWND hEdtPX;
HWND hEdtPY;
HWND hEdtPZ;
HWND hEdtRPoints;
HWND hLbxPoints;
HWND hBtnRestart;
HWND hBtnCleanList;
HWND hBtnAddP;
HWND hBtnDelP;
HWND hBtnTrans;
HWND hBtnRotat;
HWND hBtnScala;
HWND hBtnCalculate;
HWND hStM;
HWND hStT;
HWND hStT1;
HWND hStT2;
HWND hStT3;
HWND hStR;
HWND hStR1;
HWND hStR2;
HWND hStR3;
HWND hStS;
HWND hStS1;
HWND hStS2;
HWND hStS3;
HWND hStP;
HWND hStP1;
HWND hStP2;
HWND hStP3;
HWND hStRP;
//QuaternionMenu
HWND hEdtAngle;
HWND hEdtVX;
HWND hEdtVY;
HWND hEdtVZ;
HWND hEdtRQ;
HWND hBtnRQ;
HWND hStAngle;
HWND hStV;
HWND hStV1;
HWND hStV2;
HWND hStV3;
HWND hStRQ;
#pragma endregion

#pragma region VARIABLES GLOBALES
float compositeMatrix[4][4] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool init = true;
char windowState = 'm';
int counter = 0;
#pragma endregion

#pragma region CLASES
class Matrix {
	float** matrix = NULL;
	short columns;
	short rows;
public:
	Matrix(float** matrix, short columns, short rows) {
		this->matrix = matrix;
		this->columns = columns;
		this->rows = rows;
	}
	~Matrix() {
		if (this->matrix != NULL) {
			for (short i = 0; i < columns; i++)
				delete[] this->matrix[i];
			delete[] this->matrix;
		}
	}
	float** getMatrix() { return matrix; }
	short getColumns() { return columns; }
	short getRows() { return rows; }
	void operator =(Matrix &mat2) {
		this->matrix = mat2.matrix;
		this->columns = mat2.columns;
		this->rows = mat2.rows;
	}
	Matrix* operator +(Matrix &mat2) {
		short m = this->columns;
		short n = this->rows;
		float** r = new float*[m];
		for (short i = 0; i < m; i++)
			r[i] = new float[n];
		float** m1 = this->matrix;
		float** m2 = mat2.matrix;
		for (short y = 0; y < n; y++) {
			for (short x = 0; x < m; x++) {
				r[x][y] = m1[x][y] + m2[x][y];
			}
		}
		Matrix* ret = new Matrix(r, m, n);
		return ret;
	}
	Matrix* operator -(Matrix &mat2) {
		short m = this->columns;
		short n = this->rows;
		float** r = new float*[m];
		for (short i = 0; i < m; i++)
			r[i] = new float[n];
		float** m1 = this->matrix;
		float** m2 = mat2.matrix;
		for (short y = 0; y < n; y++) {
			for (short x = 0; x < m; x++) {
				r[x][y] = m1[x][y] - m2[x][y];
			}
		}
		Matrix* ret = new Matrix(r, m, n);
		return ret;
	}
	Matrix* operator *(Matrix &mat2) {
		short m = mat2.columns;
		short n = this->rows;
		short b = this->columns;
		float** r = new float*[m];
		for (short i = 0; i < m; i++)
			r[i] = new float[n];
		float** m1 = this->matrix;
		float** m2 = mat2.matrix;
		for (short y = 0; y < n; y++) {
			for (short x = 0; x < m; x++) {
				float acum = 0;
				for (short z = 0; z < b; z++) 
					acum += m1[z][y] * m2[x][z];
				r[x][y] = acum;
			}
		}
		Matrix* ret = new Matrix(r, m, n);
		return ret;
	}
};

class Point {
public:
	char id[10];
	int num;
	float x, xR;
	float y, yR;
	float z, zR;
	Point() {
		x = 0;
		y = 0;
		z = 0;
	}
	char* print() {
		char print[50];
		sprintf(print, "P%d (%.4f, %.4f, %.4f)", num, x, y, z);
		return print;
	}
	char* printR() {
		char print[50];
		sprintf(print, "P%d (%.4f, %.4f, %.4f)", num, xR, yR, zR);
		return print;
	}
	bool operator==(char* idComp) {
		if (strcmp(this->id, idComp) == 0)
			return true;
		else return false;
	}
};

LinkedList<Point> listPoints;
#pragma endregion

#pragma region CONSTRUCTORES VENTANAS
void DestroyMenu() {
	DestroyWindow(hStMain);
	MoveWindow(hBtnArit, 10, 10, 150, 25, true);
	MoveWindow(hBtnComp, 160, 10, 150, 25, true);
	MoveWindow(hBtnQuat, 310, 10, 150, 25, true);
}
void CreateAritmeticMenu() {
	EnableWindow(hBtnArit, false);
	hBtnCleanBox = CreateWindowEx(
		0, "BUTTON",
		"Limpiar Cuadros",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		465, 10, 150, 25,
		hwnd, (HMENU)BTN_CLEANBOXA, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStA1 = CreateWindow(
		"STATIC",
		"Matriz 1",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 40, 250, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix1 = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_WANTRETURN,
		10, 60, 250, 200,
		hwnd, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStA2 = CreateWindow(
		"STATIC",
		"Matriz 2",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		365, 40, 250, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix2 = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_WANTRETURN,
		365, 60, 250, 200,
		hwnd, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStA3 = CreateWindow(
		"STATIC",
		"Matriz Resultante",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		195, 270, 250, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix3 = CreateWindowEx(
		WS_EX_STATICEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		195, 290, 250, 200,
		hwnd, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnAdd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"+",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 60, 105, 66,
		hwnd, (HMENU)BTN_ADD, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnSub = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"-",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 126, 105, 66,
		hwnd, (HMENU)BTN_SUB, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnMult = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"x",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 192, 105, 66,
		hwnd, (HMENU)BTN_MULT, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
}
void DestroyAritmeticMenu() {
	EnableWindow(hBtnArit, true);
	DestroyWindow(hBtnCleanBox);
	DestroyWindow(hStA1);
	DestroyWindow(hEdtMatrix1);
	DestroyWindow(hStA2);
	DestroyWindow(hEdtMatrix2);
	DestroyWindow(hStA3);
	DestroyWindow(hEdtMatrix3);
	DestroyWindow(hBtnAdd);
	DestroyWindow(hBtnSub);
	DestroyWindow(hBtnMult);
	hBtnCleanBox = hEdtMatrix1 = hEdtMatrix2 = hEdtMatrix3 = hBtnAdd = hBtnSub = hBtnMult = NULL;
}
void CreateCompositeMatrixMenu() {
	EnableWindow(hBtnComp, false);
	hBtnCleanBox = CreateWindowEx(
		0, "BUTTON",
		"Limpiar Cuadros",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		465, 10, 150, 25,
		hwnd, (HMENU)BTN_CLEANBOXC, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStM = CreateWindow(
		"STATIC",
		"Matriz Compuesta",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 40, 350, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtCompMatrix = CreateWindowEx(
		WS_EX_STATICEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_CENTER | ES_MULTILINE | ES_READONLY,
		10, 60, 350, 175,
		hwnd, (HMENU)EDT_MATRIXC, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnRestart = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Reiniciar Matriz",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 240, 350, 25,
		hwnd, (HMENU)BTN_RESTART, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStT = CreateWindow(
		"STATIC",
		"Traslaci�n",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 280, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtTX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | ES_LEFT,
		10, 300, 86, 25,
		hwnd, (HMENU)EDT_TX, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtTY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		98, 300, 86, 25,
		hwnd, (HMENU)EDT_TY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtTZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		186, 300, 86, 25,
		hwnd, (HMENU)EDT_TZ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnTrans = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Aplicar",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		274, 300, 86, 25,
		hwnd, (HMENU)BTN_TRANS, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStT1 = CreateWindow(
		"STATIC",
		"Cord. X",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 325, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStT2 = CreateWindow(
		"STATIC",
		"Cord. Y",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		98, 325, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStT3 = CreateWindow(
		"STATIC",
		"Cord. Z",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		186, 325, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStR = CreateWindow(
		"STATIC",
		"Rotaci�n",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 350, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtRX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		10, 370, 86, 25,
		hwnd, (HMENU)EDT_RX, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtRY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		98, 370, 86, 25,
		hwnd, (HMENU)EDT_RY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtRZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		186, 370, 86, 25,
		hwnd, (HMENU)EDT_RZ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnRotat = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Aplicar",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		274, 370, 86, 25,
		hwnd, (HMENU)BTN_ROTAT, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStR1 = CreateWindow(
		"STATIC",
		"Ang� X",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 395, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStR2 = CreateWindow(
		"STATIC",
		"Ang� Y",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		98, 395, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStR3 = CreateWindow(
		"STATIC",
		"Ang� Z",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		186, 395, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStS = CreateWindow(
		"STATIC",
		"Escalamiento",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 420, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtSX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		10, 440, 86, 25,
		hwnd, (HMENU)EDT_SX, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtSY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		98, 440, 86, 25,
		hwnd, (HMENU)EDT_SY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtSZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		186, 440, 86, 25,
		hwnd, (HMENU)EDT_SZ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnScala = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Aplicar",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		274, 440, 86, 25,
		hwnd, (HMENU)BTN_SCALA, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStS1 = CreateWindow(
		"STATIC",
		"Mag. X",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 465, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStS2 = CreateWindow(
		"STATIC",
		"Mag. Y",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		98, 465, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStS3 = CreateWindow(
		"STATIC",
		"Mag. Z",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		186, 465, 86, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStP = CreateWindow(
		"STATIC",
		"Puntos",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		370, 40, 240, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hLbxPoints = CreateWindowEx(
		WS_EX_CLIENTEDGE, "LISTBOX",
		NULL,
		LBS_DISABLENOSCROLL | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
		370, 85, 240, 117,
		hwnd, (HMENU)LBX_POINTS, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtPX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		370, 215, 80, 25,
		hwnd, (HMENU)EDT_PX, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtPY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		450, 215, 80, 25,
		hwnd, (HMENU)EDT_PY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtPZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		530, 215, 80, 25,
		hwnd, (HMENU)EDT_PZ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStP1 = CreateWindow(
		"STATIC",
		"x",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		370, 198, 80, 16, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStP2 = CreateWindow(
		"STATIC",
		"y",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		450, 198, 80, 16, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStP3 = CreateWindow(
		"STATIC",
		"z",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		530, 198, 80, 16, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnCleanList = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Limpiar Lista",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		370, 60, 240, 25,
		hwnd, (HMENU)BTN_CLEANLIST, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnAddP = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Agregar",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		370, 240, 120, 25,
		hwnd, (HMENU)BTN_ADDP, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnDelP = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Borrar",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		490, 240, 120, 25,
		hwnd, (HMENU)BTN_DELP, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStRP = CreateWindow(
		"STATIC",
		"Puntos Resultantes",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		370, 280, 240, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnCalculate = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Calcular Puntos",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		370, 300, 240, 25,
		hwnd, (HMENU)BTN_CALCULATE, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtRPoints = CreateWindowEx(
		WS_EX_STATICEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
		370, 325, 240, 165,
		hwnd, (HMENU)EDT_RPOINTS, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
}
void DestroyCompositeMatrixMenu() {
	EnableWindow(hBtnComp, true);
	DestroyWindow(hBtnCleanBox);
	DestroyWindow(hStM);
	DestroyWindow(hEdtCompMatrix);
	DestroyWindow(hBtnRestart);
	DestroyWindow(hStT);
	DestroyWindow(hEdtTX);
	DestroyWindow(hEdtTY);
	DestroyWindow(hEdtTZ);
	DestroyWindow(hBtnTrans);
	DestroyWindow(hStT1);
	DestroyWindow(hStT2);
	DestroyWindow(hStT3);
	DestroyWindow(hStR);
	DestroyWindow(hEdtRX);
	DestroyWindow(hEdtRY);
	DestroyWindow(hEdtRZ);
	DestroyWindow(hBtnRotat);
	DestroyWindow(hStR1);
	DestroyWindow(hStR2);
	DestroyWindow(hStR3);
	DestroyWindow(hStS);
	DestroyWindow(hEdtSX);
	DestroyWindow(hEdtSY);
	DestroyWindow(hEdtSZ);
	DestroyWindow(hBtnScala);
	DestroyWindow(hStS1);
	DestroyWindow(hStS2);
	DestroyWindow(hStS3);
	DestroyWindow(hBtnCleanList);
	DestroyWindow(hLbxPoints);
	DestroyWindow(hEdtPX);
	DestroyWindow(hEdtPY);
	DestroyWindow(hEdtPZ);
	DestroyWindow(hBtnAddP);
	DestroyWindow(hBtnDelP);
	DestroyWindow(hStP);
	DestroyWindow(hStP1);
	DestroyWindow(hStP2);
	DestroyWindow(hStP3);
	DestroyWindow(hStRP);
	DestroyWindow(hBtnCalculate);
	DestroyWindow(hEdtRPoints);
	hBtnCleanBox = hStM = hEdtCompMatrix = hBtnRestart = hStT = hEdtTX = hEdtTY = hEdtTZ = hBtnTrans = hStT1 = hStT2 = hStT3 = NULL;
	hStR = hEdtRX = hEdtRY = hEdtRZ = hBtnRotat = hStR1 = hStR2 = hStR3 = NULL;
	hStS = hEdtSX = hEdtSY = hEdtSZ = hBtnScala = hStS1 = hStS2 = hStS3 = NULL;
	hStP = hBtnCleanList = hLbxPoints = hEdtPX = hEdtPY = hEdtPZ = hBtnAddP = hBtnDelP = hStP = hStP1 = hStP2 = hStP3 = hStRP = hBtnCalculate = hEdtRPoints = NULL;
}
void CreateQuaternionMenu() {
	EnableWindow(hBtnQuat, false);
	hBtnCleanBox = CreateWindowEx(
		0, "BUTTON",
		"Limpiar Cuadros",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		465, 10, 150, 25,
		hwnd, (HMENU)BTN_CLEANBOXQ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtAngle = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | ES_LEFT,
		10, 80, 100, 25,
		hwnd, (HMENU)EDT_ANGLE, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStAngle = CreateWindow(
		"STATIC",
		"�ngulo �",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 60, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtVX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		10, 170, 100, 25,
		hwnd, (HMENU)EDT_VX, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtVY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		110, 170, 100, 25,
		hwnd, (HMENU)EDT_VY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtVZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		210, 170, 100, 25,
		hwnd, (HMENU)EDT_VZ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStV = CreateWindow(
		"STATIC",
		"Vector",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 150, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStV1 = CreateWindow(
		"STATIC",
		"i",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 195, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStV2 = CreateWindow(
		"STATIC",
		"j",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		110, 195, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStV3 = CreateWindow(
		"STATIC",
		"k",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		210, 195, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtPX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		10, 260, 100, 25,
		hwnd, (HMENU)EDT_PX, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtPY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		110, 260, 100, 25,
		hwnd, (HMENU)EDT_PY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtPZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
		210, 260, 100, 25,
		hwnd, (HMENU)EDT_PZ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStP = CreateWindow(
		"STATIC",
		"Punto",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 240, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStP1 = CreateWindow(
		"STATIC",
		"x",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 285, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStP2 = CreateWindow(
		"STATIC",
		"y",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		110, 285, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hStP3 = CreateWindow(
		"STATIC",
		"z",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		210, 285, 100, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hBtnRQ = CreateWindowEx(
		0, "BUTTON",
		"Vector Resultante",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		370, 80, 240, 25,
		hwnd, (HMENU)BTN_RQ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
	hEdtRQ = CreateWindowEx(
		WS_EX_STATICEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
		370, 105, 240, 165,
		hwnd, (HMENU)EDT_RQ, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
	);
}
void DestroyQuaternionMenu() {
	EnableWindow(hBtnQuat, true);
	DestroyWindow(hBtnCleanBox);
	DestroyWindow(hEdtAngle);
	DestroyWindow(hEdtVX);
	DestroyWindow(hEdtVY);
	DestroyWindow(hEdtVZ);
	DestroyWindow(hStV);
	DestroyWindow(hStV1);
	DestroyWindow(hStV2);
	DestroyWindow(hStV3);
	DestroyWindow(hEdtPX);
	DestroyWindow(hEdtPY);
	DestroyWindow(hEdtPZ);
	DestroyWindow(hStP);
	DestroyWindow(hStP1);
	DestroyWindow(hStP2);
	DestroyWindow(hStP3);
	DestroyWindow(hBtnRQ);
	DestroyWindow(hEdtRQ);
	hBtnCleanBox = hEdtAngle = hStAngle = hEdtVX = hEdtVY = hEdtVZ = hStV = hStV1 = hStV2 = hStV3 = NULL;
	hEdtPX = hEdtPY = hEdtPZ = hStP = hStP1 = hStP2 = hStP3 = hBtnRQ = hEdtRQ = NULL;
}
#pragma endregion

#pragma region ARITMETICAS
void initializeMatrix(float** mat, short columns, short rows) {
	for (short x = 0; x < columns; x++) 
		for (short y = 0; y < rows; y++)
			mat[x][y] = 0;
}
bool validMatrix(char* string) {
	while (*string != NULL) {
		if (!((*string > 47 & *string < 58) | *string == 10 | *string == 13 | *string == 32 | *string == 43 | *string == 45 | *string == 46 | *string == 9))
			return false;
		string++;
	}
	return true;
}
short getColumns(HWND hWindow) {
	int length = GetWindowTextLength(hWindow);
	if (length == 0) return 0;
	char buff[MAX_PATH];
	GetWindowText(hWindow, buff, length + 1);
	char* string = buff;
	char prev = 32;
	short columns = 0;
	while (*string != 13 & *string != NULL) {
		if (((*string > 47 & *string < 58) | (*string == 43 | *string == 45 | *string == 46)) & prev == 32)
			columns++;
		prev = *string;
		string++;
	}
	return columns;
}
short getRows(HWND hWindow) {
	int length = GetWindowTextLength(hWindow);
	if (length == 0) return 0;
	char buff[MAX_PATH];
	GetWindowText(hWindow, buff, length + 1);
	char* string = buff;
	short rows = 1;
	while (*string != NULL) {
		if (*string == 13) {
			while (!((*string > 47 & *string < 58) | (*string == 43 | *string == 45 | *string == 46 | *string == NULL)))
				string++;
			if (((*string > 47 & *string < 58) | (*string == 43 | *string == 45 | *string == 46))) rows++;
		}
		if (*string == NULL) break;
		string++;
	}
	return rows;
}
void printMatrixOnWindow(HWND hWindow, Matrix* matrix) {
	char buff[MAX_PATH] = "";
	char mat[24];
	float** pMatrix = matrix->getMatrix();
	for (short y = 0; y < matrix->getRows(); y++) {
		for (short x = 0; x < matrix->getColumns(); x++) {
			sprintf(mat, "%.2f", pMatrix[x][y]);
			strcat(buff, mat); strcat(buff, "   ");
		}
		strcat(buff, "\r\n\r\n");
	}
	SetWindowText(hWindow, buff);
}
Matrix* buildMatrix(HWND hWindow) {
	int length = GetWindowTextLength(hWindow);
	if (length == 0) return NULL;
	char buff[MAX_PATH];
	GetWindowText(hWindow, buff, length + 1);
	if (!validMatrix(buff)) return NULL;
	char* string = buff;
	char prev = 0;
	short m = getColumns(hWindow);
	short n = getRows(hWindow);
	float** matrix = new float*[m];
	for (short i = 0; i < m; i++)
		matrix[i] = new float[n];
	initializeMatrix(matrix, m, n);
	for (short y = 0; y < n; y++) {
		for (short x = 0; x < m; x++) {
			while (!((*string > 47 & *string < 58) | (*string == 43 | *string == 45 | *string == 46 | *string == 13))) {
				string++;
			}
			if (*string == 13) break;
			sscanf(string, "%f", &matrix[x][y]);
			while (*string != 32 & *string != 13 & *string != NULL) 
				string++;
		}
		while (!((*string > 47 & *string < 58) | (*string == 43 | *string == 45 | *string == 46 | *string == NULL))) {
			string++;
		}
	}
	Matrix *r = new Matrix(matrix, m, n);
	return r;
}
#pragma endregion

#pragma region COMPUESTAS
void printCompositeMatrix() {
	char buff[MAX_PATH] = "\r\n\r\n";
	char mat[30];
	for (short y = 0; y < 4; y++) {
		for (short x = 0; x < 4; x++) {
			sprintf(mat, "%.4f", compositeMatrix[y][x]);
			strcat(buff, mat); strcat(buff, "   ");
		}
		strcat(buff, "\r\n\r\n");
	}
	SetWindowText(hEdtCompMatrix, buff);
}
void restartCompositeMatrix() {
	for (short y = 0; y < 4; y++)
		for (short x = 0; x < 4; x++)
			compositeMatrix[y][x] = 0;
	init = true;
	printCompositeMatrix();
}
bool validString(char* string) {
	while (*string != NULL) {
		if (!((*string > 47 & *string < 58) | (*string == 43 | *string == 45 | *string == 46)))
			return false;
		string++;
	}
	return true;
}
void translate(float x, float y, float z) {
	float tras[4][4] = { 1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1 };
	if (init) {
		for (short j = 0; j < 4; j++)
			for (short i = 0; i < 4; i++)
				compositeMatrix[j][i] = tras[j][i];
		init = false;
		return;
	}
	float result[4][4];
	for (short j = 0; j < 4; j++) {
		for (short i = 0; i < 4; i++) {
			float acum = 0;
			for (short k = 0; k < 4; k++)
				acum += compositeMatrix[j][k] * tras[k][i];
			result[j][i] = acum;
		}
	}
	for (short j = 0; j < 4; j++)
		for (short i = 0; i < 4; i++)
			compositeMatrix[j][i] = result[j][i];
}
void rotate(float x, float y, float z) {
	if (x != 0) {
		float rotx[4][4] = { 1, 0, 0, 0, 0, cos(TO_RAD(x)), -(sin(TO_RAD(x))), 0, 0, sin(TO_RAD(x)), cos(TO_RAD(x)), 0, 0, 0, 0, 1 };
		if (init) {
			for (short j = 0; j < 4; j++)
				for (short i = 0; i < 4; i++)
					compositeMatrix[j][i] = rotx[j][i];
			init = false;
			return;
		}
		float result[4][4];
		for (short j = 0; j < 4; j++) {
			for (short i = 0; i < 4; i++) {
				float acum = 0;
				for (short k = 0; k < 4; k++)
					acum += compositeMatrix[j][k] * rotx[k][i];
				result[j][i] = acum;
			}
		}
		for (short j = 0; j < 4; j++)
			for (short i = 0; i < 4; i++)
				compositeMatrix[j][i] = result[j][i];
	}
	else if (y != 0) {
		float roty[4][4] = { cos(TO_RAD(y)), 0, sin(TO_RAD(y)), 0, 0, 1, 0, 0, -(sin(TO_RAD(y))), 0, cos(TO_RAD(y)), 0, 0, 0, 0, 1 };
		if (init) {
			for (short j = 0; j < 4; j++)
				for (short i = 0; i < 4; i++)
					compositeMatrix[j][i] = roty[j][i];
			init = false;
			return;
		}
		float result[4][4];
		for (short j = 0; j < 4; j++) {
			for (short i = 0; i < 4; i++) {
				float acum = 0;
				for (short k = 0; k < 4; k++)
					acum += compositeMatrix[j][k] * roty[k][i];
				result[j][i] = acum;
			}
		}
		for (short j = 0; j < 4; j++)
			for (short i = 0; i < 4; i++)
				compositeMatrix[j][i] = result[j][i];
	}
	else if (z != 0) {
		float rotz[4][4] = { cos(TO_RAD(z)), -(sin(TO_RAD(z))), 0, 0, sin(TO_RAD(z)), cos(TO_RAD(z)), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		if (init) {
			for (short j = 0; j < 4; j++)
				for (short i = 0; i < 4; i++)
					compositeMatrix[j][i] = rotz[j][i];
			init = false;
			return;
		}
		float result[4][4];
		for (short j = 0; j < 4; j++) {
			for (short i = 0; i < 4; i++) {
				float acum = 0;
				for (short k = 0; k < 4; k++)
					acum += compositeMatrix[j][k] * rotz[k][i];
				result[j][i] = acum;
			}
		}
		for (short j = 0; j < 4; j++)
			for (short i = 0; i < 4; i++)
				compositeMatrix[j][i] = result[j][i];
	}
}
void scale(float x, float y, float z) {
	float scale[4][4] = { x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1 };
	if (init) {
		for (short j = 0; j < 4; j++)
			for (short i = 0; i < 4; i++)
				compositeMatrix[j][i] = scale[j][i];
		init = false;
		return;
	}
	float result[4][4];
	for (short j = 0; j < 4; j++) {
		for (short i = 0; i < 4; i++) {
			float acum = 0;
			for (short k = 0; k < 4; k++)
				acum += compositeMatrix[j][k] * scale[k][i];
			result[j][i] = acum;
		}
	}
	for (short j = 0; j < 4; j++)
		for (short i = 0; i < 4; i++)
			compositeMatrix[j][i] = result[j][i];
}
template <typename T> void resultPoints() {
	Node<T>* aux = listPoints.getFirst();
	while (aux != NULL) {
		Point temp = aux->getData();
		float point[4] = {temp.x, temp.y, temp.z, 1};
		float result[4];
		for (short j = 0; j < 4; j++) {
			float acum = 0;
			for (short k = 0; k < 4; k++)
				acum += compositeMatrix[j][k] * point[k];
			result[j] = acum;
		}
		temp.xR = result[0];
		temp.yR = result[1];
		temp.zR = result[2];
		aux->setData(temp);
		aux = aux->getNext();
	}
	aux = listPoints.getFirst();
	char buff[450] = "";
	while (aux != NULL) {
		strcat(buff, aux->getData().printR()); strcat(buff, "\r\n\r\n");
		aux = aux->getNext();
	}
	SetWindowText(hEdtRPoints, buff);
}
#pragma endregion

#pragma region QUATERNIONES
void quaternion(float angle, float vx, float vy, float vz, float px, float py, float pz) {
	using namespace R4DEngine;
	//Rp = Q * P * Q^-1

	//Paso 1 Identificar mis datos.
	// Ang� = 30, v = <3, 2, 0>, P(0, 3, 0)
	R4DVector3n vec(vx, vy, vz); // Esto ser�a el vector: v = <3, 2, 0>
	R4DQuaternion vecAng(angle, vec); //Lo guardo como quaternion para usar el m�todo convertToUintNormQuaternion();
	R4DVector3n point(px, py, pz); // Esto es un vector, pero lo uso como mi P(0, 3, 0)
	R4DQuaternion P(0, point); // Lo guardo como quaternion

	//Paso 2 Obtener el vector unitario y Paso 3 Obtener el valor de Q.
	R4DQuaternion Q(vecAng);
	Q.convertToUnitNormQuaternion(); //Convierto vecAng a quaternion normal unitario, esto ser�a Q.

	//Paso 4 Obtener el valor de Q^-1.
	R4DQuaternion Qinv(Q.conjugate());  // Convierto Q a su inverso, Q^-1. Se guarda en Qinv

	//Multiplicar Q por P por Q inversa. Se guarda en RQ
	R4DQuaternion RQ((Q*P) * Qinv);

	//Imprimir valor en arreglo char
	char buff[86];
	char s[20];
	char vi[22];
	char vj[22];
	char vk[22];
	sprintf(s, "%.4f", RQ.s);
	RQ.v.x >= 0 ? sprintf(vi, " + %.4fi", RQ.v.x) : sprintf(vi, " - %.4fi", (RQ.v.x)*-1);
	RQ.v.y >= 0 ? sprintf(vj, " + %.4fj", RQ.v.y) : sprintf(vj, " - %.4fj", (RQ.v.y)*-1);
	RQ.v.z >= 0 ? sprintf(vk, " + %.4fk", RQ.v.z) : sprintf(vk, " - %.4fk", (RQ.v.z)*-1);
	strcpy(buff, s); strcat(buff, vi); strcat(buff, vj); strcat(buff, vk);
	SetWindowText(hEdtRQ, buff);
}
#pragma endregion

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE: {
		hStMain = CreateWindow(
			"STATIC",
			"�Con qu� desea trabajar?",
			WS_CHILD | WS_VISIBLE | ES_CENTER,
			170, 60, 300, 20, hWnd, NULL, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
		);
		hBtnArit = CreateWindowEx(
			0, "BUTTON", 
			"Matrices Aritm�ticas", 
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
			245, 100, 150, 90, 
			hWnd, (HMENU)BTN_ARIT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
		);
		hBtnComp = CreateWindowEx(
			0,"BUTTON",
			"Matrices Compuestas",
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			245, 200, 150, 90,
			hWnd, (HMENU)BTN_COMP, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
		);
		hBtnQuat = CreateWindowEx(
			0, "BUTTON",
			"Quaterniones",
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			245, 300, 150, 90,
			hWnd, (HMENU)BTN_QUAT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
		);
		break;
	}
	case WM_COMMAND: {
		switch (wParam) {
		//MENU BUTTONS
		case BTN_ARIT:
			switch (windowState) {
			case 'a':
				DestroyAritmeticMenu();
				break;
			case 'c':
				DestroyCompositeMatrixMenu();
				break;
			case 'm':
				DestroyMenu();
				break;
			case 'q':
				DestroyQuaternionMenu();
				break;
			}
			CreateAritmeticMenu();
			windowState = 'a';
			break;
		case BTN_COMP:
			switch (windowState) {
			case 'a':
				DestroyAritmeticMenu();
				break;
			case 'c':
				DestroyCompositeMatrixMenu();
				break;
			case 'm':
				DestroyMenu();
				break;
			case 'q':
				DestroyQuaternionMenu();
				break;
			}
			CreateCompositeMatrixMenu();
			windowState = 'c';
			printCompositeMatrix();
			listPoints.PrintOnWindow(hLbxPoints, 0);
			break;
		case BTN_QUAT:
			switch (windowState) {
			case 'a':
				DestroyAritmeticMenu();
				break;
			case 'c':
				DestroyCompositeMatrixMenu();
				break;
			case 'm':
				DestroyMenu();
				break;
			case 'q':
				DestroyQuaternionMenu();
				break;
			}
			CreateQuaternionMenu();
			windowState = 'q';
			break;
		case BTN_CLEANBOXA:
			SetWindowText(hEdtMatrix1, "");
			SetWindowText(hEdtMatrix2, "");
			SetWindowText(hEdtMatrix3, "");
			break;
		case BTN_CLEANBOXC:
			restartCompositeMatrix();
			listPoints.EraseList();
			counter = 0;
			SendMessage(hLbxPoints, LB_RESETCONTENT, 0, 0);
			SetWindowText(hEdtRPoints, "");
			break;
		case BTN_CLEANBOXQ:
			SetWindowText(hEdtAngle, "");
			SetWindowText(hEdtVX, "");
			SetWindowText(hEdtVY, "");
			SetWindowText(hEdtVZ, "");
			SetWindowText(hEdtPX, "");
			SetWindowText(hEdtPY, "");
			SetWindowText(hEdtPZ, "");
			SetWindowText(hEdtRQ, "");
			break;
		//ARITMETIC BUTTONS
		case BTN_ADD: {
			Matrix* matrix1 = buildMatrix(hEdtMatrix1);
			if (matrix1 == NULL) {
				MessageBox(hWnd, "La matriz 1 contiene caracteres invalidos o esta vac�a.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			Matrix* matrix2 = buildMatrix(hEdtMatrix2);
			if (matrix2 == NULL) {
				MessageBox(hWnd, "La matriz 2 contiene caracteres invalidos o esta vac�a.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			if (matrix1->getColumns() == matrix2->getColumns() & matrix1->getRows() == matrix2->getRows()) {
				Matrix* res = *matrix1 + *matrix2;
				printMatrixOnWindow(hEdtMatrix3, res);
				delete res;
			}
			else MessageBox(hWnd, "Las matrices tienen orden desigual. No se puede realizar la suma.", "Orden Diferente", MB_ICONEXCLAMATION);
			delete matrix1;
			delete matrix2;
			break;
		}
		case BTN_SUB: {
			Matrix* matrix1 = buildMatrix(hEdtMatrix1);
			if (matrix1 == NULL) {
				MessageBox(hWnd, "La matriz 1 contiene caracteres invalidos o esta vac�a.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			Matrix* matrix2 = buildMatrix(hEdtMatrix2);
			if (matrix2 == NULL) {
				MessageBox(hWnd, "La matriz 2 contiene caracteres invalidos o esta vac�a.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			if (matrix1->getColumns() == matrix2->getColumns() & matrix1->getRows() == matrix2->getRows()) {
				Matrix* res = *matrix1 - *matrix2;
				printMatrixOnWindow(hEdtMatrix3, res);
				delete res;
			}
			else MessageBox(hWnd, "Las matrices tienen orden desigual. No se puede realizar la resta.", "Orden Diferente", MB_ICONEXCLAMATION);
			delete matrix1;
			delete matrix2;
			break;
		}
		case BTN_MULT: {
			Matrix* matrix1 = buildMatrix(hEdtMatrix1);
			if (matrix1 == NULL) {
				MessageBox(hWnd, "La matriz 1 contiene caracteres invalidos o esta vac�a.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			Matrix* matrix2 = buildMatrix(hEdtMatrix2);
			if (matrix2 == NULL) {
				MessageBox(hWnd, "La matriz 2 contiene caracteres invalidos o esta vac�a.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			if (matrix1->getColumns() == matrix2->getRows()) {
				Matrix* res = *matrix1 * *matrix2;
				printMatrixOnWindow(hEdtMatrix3, res);
				delete res;
			}
			else MessageBox(hWnd, "Columnas de matriz 1 y renglones de matriz 2 son desiguales. No se puede realizar el producto.", "Orden Incorrecto", MB_ICONEXCLAMATION);
			delete matrix1;
			delete matrix2;
			break;
		}
		//COMPOSITE BUTTONS
		case BTN_RESTART:
			restartCompositeMatrix();
			break;
		case BTN_TRANS: {
			char buff[30];
			float x = 0, y = 0, z = 0;
			short lengthX = GetWindowTextLength(hEdtTX);
			short lengthY = GetWindowTextLength(hEdtTY);
			short lengthZ = GetWindowTextLength(hEdtTZ);
			if (lengthX == 0 & lengthY == 0 & lengthZ == 0) break;
			if (lengthX > 0) {
				GetWindowText(hEdtTX, buff, lengthX + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &x);
			}
			if (lengthY > 0) {
				GetWindowText(hEdtTY, buff, lengthY + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &y);
			}
			if (lengthZ > 0) {
				GetWindowText(hEdtTZ, buff, lengthZ + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &z);
			}
			translate(x, y, z);
			printCompositeMatrix();
			SetWindowText(hEdtTX, "");
			SetWindowText(hEdtTY, "");
			SetWindowText(hEdtTZ, "");
			break;
		}
		case BTN_ROTAT: {
			char buff[30];
			float x = 0, y = 0, z = 0;
			int lengthX = GetWindowTextLength(hEdtRX);
			int lengthY = GetWindowTextLength(hEdtRY);
			int lengthZ = GetWindowTextLength(hEdtRZ);
			if (lengthZ == 0) {
				if (lengthY == 0) {
					if (lengthX == 0) {
						break;
					}
					else {
						GetWindowText(hEdtRX, buff, lengthX + 1);
						if (!validString(buff)) {
							MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
							break;
						}
						sscanf(buff, "%f", &x);
					}
				}
				else {
					GetWindowText(hEdtRY, buff, lengthY + 1);
					if (!validString(buff)) {
						MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
						break;
					}
					sscanf(buff, "%f", &y);
				}
			}
			else {
				GetWindowText(hEdtRZ, buff, lengthZ + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &z);
			}
			rotate(x, y, z);
			printCompositeMatrix();
			SetWindowText(hEdtRX, "");
			SetWindowText(hEdtRY, "");
			SetWindowText(hEdtRZ, "");
			break;
		}
		case BTN_SCALA: {
			char buff[30];
			float x = 0, y = 0, z = 0;
			short lengthX = GetWindowTextLength(hEdtSX);
			short lengthY = GetWindowTextLength(hEdtSY);
			short lengthZ = GetWindowTextLength(hEdtSZ);
			if (lengthX == 0 & lengthY == 0 & lengthZ == 0) break;
			if (lengthX > 0) {
				GetWindowText(hEdtSX, buff, lengthX + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &x);
			}
			if (lengthY > 0) {
				GetWindowText(hEdtSY, buff, lengthY + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &y);
			}
			if (lengthZ > 0) {
				GetWindowText(hEdtSZ, buff, lengthZ + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &z);
			}
			scale(x, y, z);
			printCompositeMatrix();
			SetWindowText(hEdtSX, "");
			SetWindowText(hEdtSY, "");
			SetWindowText(hEdtSZ, "");
			break;
		}
		case BTN_ADDP: {
			Point temp;
			char buff[30];
			short lengthX = GetWindowTextLength(hEdtPX);
			short lengthY = GetWindowTextLength(hEdtPY);
			short lengthZ = GetWindowTextLength(hEdtPZ);
			if (lengthX == 0 & lengthY == 0 & lengthZ == 0) break;
			if (lengthX > 0) {
				GetWindowText(hEdtPX, buff, lengthX + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &temp.x);
			}
			if (lengthY > 0) {
				GetWindowText(hEdtPY, buff, lengthY + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &temp.y);
			}
			if (lengthZ > 0) {
				GetWindowText(hEdtPZ, buff, lengthZ + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &temp.z);
			}
			counter++;
			snprintf(buff, 30, "P%d", counter);
			strcpy(temp.id, buff);
			temp.num = counter;
			listPoints.AddNode(temp);
			listPoints.PrintOnWindow(hLbxPoints, 0);
			SetWindowText(hEdtPX, "");
			SetWindowText(hEdtPY, "");
			SetWindowText(hEdtPZ, "");
			break;
		}
		case BTN_DELP: {
			char buff[MAX_PATH];
			char* string;
			int i = SendMessage(hLbxPoints, LB_GETCURSEL, 0, 0);
			if (i == -1) break;
			SendMessage(hLbxPoints, LB_GETTEXT, i, (LPARAM)buff);
			string = buff;
			while (*string != 32) string++;
			*string = NULL;
			listPoints.DeleteNode(listPoints.SearchNode(buff));
			listPoints.PrintOnWindow(hLbxPoints, 0);
			if (listPoints.CountList() == 0) counter = 0;
			break;
		}
		case BTN_CLEANLIST:
			listPoints.EraseList();
			SendMessage(hLbxPoints, LB_RESETCONTENT, 0, 0);
			counter = 0;
			break;
		case BTN_CALCULATE:
			if (init) {
				MessageBox(hWnd, "No se puede realizar el calculo. La matriz a�n no ha sido transformada.", "Matriz Inicializada", MB_ICONEXCLAMATION);
				break;
			}
			resultPoints<Point>();
			break;
		//QUATERNION BUTTONS
		case BTN_RQ: {
			char buff[30];
			float ang = 0, i = 0, j = 0, k = 0, x = 0, y = 0, z = 0;
			short lengthA = GetWindowTextLength(hEdtAngle);
			short lengthI = GetWindowTextLength(hEdtVX);
			short lengthJ = GetWindowTextLength(hEdtVY);
			short lengthK = GetWindowTextLength(hEdtVZ);
			short lengthX = GetWindowTextLength(hEdtPX);
			short lengthY = GetWindowTextLength(hEdtPY);
			short lengthZ = GetWindowTextLength(hEdtPZ);
			if (lengthA > 0) {
				GetWindowText(hEdtAngle, buff, lengthA + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &ang);
			}
			if (lengthI > 0) {
				GetWindowText(hEdtVX, buff, lengthI + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &i);
			}
			if (lengthJ > 0) {
				GetWindowText(hEdtVY, buff, lengthJ + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &j);
			}
			if (lengthK > 0) {
				GetWindowText(hEdtVZ, buff, lengthK + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &k);
			}
			if (lengthX > 0) {
				GetWindowText(hEdtPX, buff, lengthX + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &x);
			}
			if (lengthY > 0) {
				GetWindowText(hEdtPY, buff, lengthY + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &y);
			}
			if (lengthZ > 0) {
				GetWindowText(hEdtPZ, buff, lengthZ + 1);
				if (!validString(buff)) {
					MessageBox(hWnd, "Solo puede ingresar n�meros y signos de puntuaci�n.", "Caracteres inv�lidos", MB_ICONEXCLAMATION);
					break;
				}
				sscanf(buff, "%f", &z);
			}
			quaternion(ang, i, j, k, x, y, z);
			break;
		}
		}
		break;
	}
	case WM_GETMINMAXINFO: {
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 640;
		lpMMI->ptMinTrackSize.y = 540;
		lpMMI->ptMaxTrackSize.x = 640;
		lpMMI->ptMaxTrackSize.y = 540;
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int showCmd) {
	WNDCLASSEX wClass; 
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbClsExtra = NULL; 
	wClass.cbWndExtra = NULL; 
	wClass.cbSize = sizeof(WNDCLASSEX); 
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW; 
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wClass.hIcon = NULL;
	wClass.hIconSm = NULL;
	wClass.hInstance = hInstance; 
	wClass.lpfnWndProc = (WNDPROC)WinProc; 
	wClass.lpszClassName = "Window Class"; 
	wClass.lpszMenuName = NULL;
	wClass.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClassEx(&wClass)){
		int nResult = GetLastError();
		char buff[124];
		snprintf(buff, 124, "Window class creation failed. Last error code %i.", nResult);
		MessageBox(NULL, buff, "Window Class Failed", MB_ICONERROR);
	}

	hwnd = CreateWindowEx(NULL, "Window Class", "XCALCULATE by CYANx86", WS_OVERLAPPEDWINDOW, 300, 200, 640, 540, NULL, NULL, hInstance, NULL);
	if (!hwnd){
		int nResult = GetLastError();
		char buff[124];
		snprintf(buff, 124, "Window creation failed. Last error code %i", nResult);
		MessageBox(NULL, buff, "Window Creation Failed", MB_ICONERROR);
	}
	ShowWindow(hwnd, showCmd);

	MSG msg; 
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, NULL, 0, 0)){
		if (!IsDialogMessage(hwnd, &msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}