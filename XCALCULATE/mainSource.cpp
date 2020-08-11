#include <Windows.h>
#include <stdio.h>
#include <math.h>

#pragma warning(disable : 4996)

#pragma region DEFINICIONES
#define BTN_ARIT 101
#define BTN_COMP 102
#define EDT_MATRIX1 103
#define EDT_MATRIX2 104
#define EDT_MATRIX3 105
#define BTN_ADD 106
#define BTN_SUB	 107
#define BTN_MULT 108
#define BTN_CLEAN 109
#define EDT_MATRIXC 110
#define EDT_TX 111
#define EDT_TY 112
#define EDT_TZ 113
#define EDT_RX 114
#define EDT_RY 115
#define EDT_RZ 116
#define EDT_SX 117
#define EDT_SY 118
#define EDT_SZ 119
#define EDT_RPOINTS 120
#define LBX_POINTS 121
#define BTN_RESTART 122
#define BTN_ADDP 123
#define BTN_DELP 124
#define BTN_TRANS 125
#define BTN_ROTAT 126
#define BTN_SCALA 127
#define BTN_CALCULATE 128

#define PI 3.1416
#define TO_DEG(A) A*(180/PI)
#define TO_RAD(A) A*(PI/180)
#pragma endregion

#pragma region HANDLERS
HWND hBtnArit;
HWND hBtnComp;
//AritmeticMenu
HWND hEdtMatrix1;
HWND hEdtMatrix2;
HWND hEdtMatrix3;
HWND hBtnAdd;
HWND hBtnSub;
HWND hBtnMult;
HWND hBtnClean;
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
HWND hEdtRPoints;
HWND hLbxPoints;
HWND hBtnRestart;
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
HWND hStRP;
#pragma endregion

#pragma region VARIABLES GLOBALES
float compositeMatrix[4][4] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool init = true;
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
#pragma endregion

#pragma region CONSTRUCTORES VENTANAS
void CreateAritmeticMenu(HWND hWindow) {
	EnableWindow(hBtnArit, false); EnableWindow(hBtnComp, true);
	hStA1 = CreateWindow(
		"STATIC",
		"Matriz 1",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 40, 250, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix1 = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL,
		10, 60, 250, 200,
		hWindow, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStA2 = CreateWindow(
		"STATIC",
		"Matriz 2",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		365, 40, 250, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix2 = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL,
		365, 60, 250, 200,
		hWindow, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStA3 = CreateWindow(
		"STATIC",
		"Matriz Resultante",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		195, 270, 250, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix3 = CreateWindowEx(
		WS_EX_STATICEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		195, 290, 250, 200,
		hWindow, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnAdd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"+",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 60, 105, 66,
		hWindow, (HMENU)BTN_ADD, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnSub = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"-",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 126, 105, 66,
		hWindow, (HMENU)BTN_SUB, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnMult = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"x",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 192, 105, 66,
		hWindow, (HMENU)BTN_MULT, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
}
void DestroyAritmeticMenu() {
	DestroyWindow(hStA1);
	DestroyWindow(hEdtMatrix1);
	DestroyWindow(hStA2);
	DestroyWindow(hEdtMatrix2);
	DestroyWindow(hStA3);
	DestroyWindow(hEdtMatrix3);
	DestroyWindow(hBtnAdd);
	DestroyWindow(hBtnSub);
	DestroyWindow(hBtnMult);
	hEdtMatrix1 = hEdtMatrix2 = hEdtMatrix3 = hBtnAdd = hBtnSub = hBtnMult = NULL;
}
void CreateCompositeMatrixMenu(HWND hWindow) {
	EnableWindow(hBtnComp, false); EnableWindow(hBtnArit, true);
	hStM = CreateWindow(
		"STATIC",
		"Matriz Compuesta",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 40, 350, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtCompMatrix = CreateWindowEx(
		WS_EX_STATICEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_CENTER | ES_MULTILINE | ES_READONLY,
		10, 60, 350, 175,
		hWindow, (HMENU)EDT_MATRIXC, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnRestart = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Reiniciar Matriz",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 240, 350, 25,
		hWindow, (HMENU)BTN_RESTART, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStT = CreateWindow(
		"STATIC",
		"Traslaci�n",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 280, 100, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtTX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 300, 86, 25,
		hWindow, (HMENU)EDT_TX, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtTY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		98, 300, 86, 25,
		hWindow, (HMENU)EDT_TY, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtTZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		186, 300, 86, 25,
		hWindow, (HMENU)EDT_TZ, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnTrans = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Aplicar",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		274, 300, 86, 25,
		hWindow, (HMENU)BTN_TRANS, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStT1 = CreateWindow(
		"STATIC",
		"x",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 325, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStT2 = CreateWindow(
		"STATIC",
		"y",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		98, 325, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStT3 = CreateWindow(
		"STATIC",
		"z",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		186, 325, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStR = CreateWindow(
		"STATIC",
		"Rotaci�n",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 350, 100, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtRX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 370, 86, 25,
		hWindow, (HMENU)EDT_RX, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtRY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		98, 370, 86, 25,
		hWindow, (HMENU)EDT_RY, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtRZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		186, 370, 86, 25,
		hWindow, (HMENU)EDT_RZ, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnRotat = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Aplicar",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		274, 370, 86, 25,
		hWindow, (HMENU)BTN_ROTAT, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStR1 = CreateWindow(
		"STATIC",
		"x",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 395, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStR2 = CreateWindow(
		"STATIC",
		"y",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		98, 395, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStR3 = CreateWindow(
		"STATIC",
		"z",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		186, 395, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStS = CreateWindow(
		"STATIC",
		"Escalamiento",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 420, 100, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtSX = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		10, 440, 86, 25,
		hWindow, (HMENU)EDT_SX, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtSY = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		98, 440, 86, 25,
		hWindow, (HMENU)EDT_SY, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtSZ = CreateWindowEx(
		WS_EX_CLIENTEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		186, 440, 86, 25,
		hWindow, (HMENU)EDT_SZ, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnScala = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Aplicar",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		274, 440, 86, 25,
		hWindow, (HMENU)BTN_SCALA, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStS1 = CreateWindow(
		"STATIC",
		"x",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		10, 465, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStS2 = CreateWindow(
		"STATIC",
		"y",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		98, 465, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStS3 = CreateWindow(
		"STATIC",
		"z",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		186, 465, 86, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStP = CreateWindow(
		"STATIC",
		"Puntos",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		370, 40, 240, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hLbxPoints = CreateWindowEx(
		WS_EX_CLIENTEDGE, "LISTBOX",
		NULL,
		LBS_DISABLENOSCROLL | LBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
		370, 60, 240, 180,
		hWindow, (HMENU)LBX_POINTS, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnAddP = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Agregar",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		370, 240, 120, 25,
		hWindow, (HMENU)BTN_ADDP, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnDelP = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Borrar",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		490, 240, 120, 25,
		hWindow, (HMENU)BTN_DELP, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStRP = CreateWindow(
		"STATIC",
		"Puntos Resultantes",
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		370, 280, 240, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnCalculate = CreateWindowEx(
		WS_EX_CLIENTEDGE, "BUTTON",
		"Calcular Puntos",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		370, 300, 240, 25,
		hWindow, (HMENU)BTN_CALCULATE, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtRPoints = CreateWindowEx(
		WS_EX_STATICEDGE, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_READONLY,
		370, 325, 240, 205,
		hWindow, (HMENU)EDT_RPOINTS, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
}
void DestroyCompositeMatrixMenu() {
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
	DestroyWindow(hLbxPoints);
	DestroyWindow(hBtnAddP);
	DestroyWindow(hBtnDelP);
	DestroyWindow(hStRP);
	DestroyWindow(hBtnCalculate);
	DestroyWindow(hEdtRPoints);
	hStM = hEdtCompMatrix = hBtnRestart = hStT = hEdtTX = hEdtTY = hEdtTZ = hBtnTrans = hStT1 = hStT2 = hStT3 = NULL;
	hStR = hEdtRX = hEdtRY = hEdtRZ = hBtnRotat = hStR1 = hStR2 = hStR3 = NULL;
	hStS = hEdtSX = hEdtSY = hEdtSZ = hBtnScala = hStS1 = hStS2 = hStS3 = NULL;
	hStP = hLbxPoints = hBtnAddP = hBtnDelP = hStRP = hBtnCalculate = hEdtRPoints = NULL;
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
					acum += compositeMatrix[k][j] * rotx[i][k];
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
	else {
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
					acum += compositeMatrix[k][j] * rotz[i][k];
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
#pragma endregion

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE: {
		hBtnArit = CreateWindowEx(
			0, "BUTTON", 
			"Matrices Aritm�ticas", 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
			10, 10, 150, 25, 
			hWnd, (HMENU)BTN_ARIT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
		);
		hBtnComp = CreateWindowEx(
			0,"BUTTON",
			"Matrices Compuestas",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			165, 10, 150, 25,
			hWnd, (HMENU)BTN_COMP, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
		);
		hBtnClean = CreateWindowEx(
			0, "BUTTON",
			"Limpiar Cuadros",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			465, 10, 150, 25,
			hWnd, (HMENU)BTN_CLEAN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
		);
		CreateAritmeticMenu(hWnd);
		break;
	}
	case WM_COMMAND: {
		switch (wParam) {
		case BTN_ARIT:
			DestroyCompositeMatrixMenu();
			CreateAritmeticMenu(hWnd);
			break;
		case BTN_COMP:
			DestroyAritmeticMenu();
			CreateCompositeMatrixMenu(hWnd);
			printCompositeMatrix();
			break;
		case BTN_CLEAN:
			SetWindowText(hEdtMatrix1, "");
			SetWindowText(hEdtMatrix2, "");
			SetWindowText(hEdtMatrix3, "");
			break;
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
		case BTN_RESTART:
			restartCompositeMatrix();
			break;
		case BTN_TRANS: {
			char buff[30];
			float x = 0, y = 0, z = 0;
			int length = GetWindowTextLength(hEdtTX);
			if (length > 0) {
				GetWindowText(hEdtTX, buff, length + 1);
				sscanf(buff, "%f", &x);
			}
			length = GetWindowTextLength(hEdtTY);
			if (length > 0) {
				GetWindowText(hEdtTY, buff, length + 1);
				sscanf(buff, "%f", &y);
			}
			length = GetWindowTextLength(hEdtTZ);
			if (length > 0) {
				GetWindowText(hEdtTZ, buff, length + 1);
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
			int length = GetWindowTextLength(hEdtRX);
			if (length > 0) {
				GetWindowText(hEdtRX, buff, length + 1);
				sscanf(buff, "%f", &x);
			}
			length = GetWindowTextLength(hEdtRY);
			if (length > 0) {
				GetWindowText(hEdtRY, buff, length + 1);
				sscanf(buff, "%f", &y);
			}
			length = GetWindowTextLength(hEdtRZ);
			if (length > 0) {
				GetWindowText(hEdtRZ, buff, length + 1);
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
			int length = GetWindowTextLength(hEdtSX);
			if (length > 0) {
				GetWindowText(hEdtSX, buff, length + 1);
				sscanf(buff, "%f", &x);
			}
			length = GetWindowTextLength(hEdtSY);
			if (length > 0) {
				GetWindowText(hEdtSY, buff, length + 1);
				sscanf(buff, "%f", &y);
			}
			length = GetWindowTextLength(hEdtSZ);
			if (length > 0) {
				GetWindowText(hEdtSZ, buff, length + 1);
				sscanf(buff, "%f", &z);
			}
			scale(x, y, z);
			printCompositeMatrix();
			SetWindowText(hEdtSX, "");
			SetWindowText(hEdtSY, "");
			SetWindowText(hEdtSZ, "");
			break;
		}
		}
		if (LOWORD(wParam) == EDT_RX & HIWORD(wParam) == EN_SETFOCUS) {
			SetWindowText(hEdtRY, "");
			SetWindowText(hEdtRZ, "");
		}
		if (LOWORD(wParam) == EDT_RY & HIWORD(wParam) == EN_SETFOCUS) {
			SetWindowText(hEdtRX, "");
			SetWindowText(hEdtRZ, "");
		}
		if (LOWORD(wParam) == EDT_RZ & HIWORD(wParam) == EN_SETFOCUS) {
			SetWindowText(hEdtRX, "");
			SetWindowText(hEdtRY, "");
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

	HWND hWnd = CreateWindowEx(NULL, "Window Class", "XCALCULATE by CYANx86", WS_OVERLAPPEDWINDOW, 300, 200, 640, 540, NULL, NULL, hInstance, NULL);
	if (!hWnd){
		int nResult = GetLastError();
		char buff[124];
		snprintf(buff, 124, "Window creation failed. Last error code %i", nResult);
		MessageBox(NULL, buff, "Window Creation Failed", MB_ICONERROR);
	}
	ShowWindow(hWnd, showCmd);

	MSG msg; 
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return 0;
}