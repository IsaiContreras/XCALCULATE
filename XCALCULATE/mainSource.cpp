#include <Windows.h>
#include <stdio.h>

#pragma warning(disable : 4996)

#define BTN_ARIT 101
#define BTN_COMP 102
#define EDT_MATRIX1 103
#define EDT_MATRIX2 104
#define EDT_MATRIX3 105
#define BTN_ADD 106
#define BTN_SUB	 107
#define BTN_MULT 108
#define BTN_CLEAN 109

HWND hBtnArit;
HWND hBtnComp;
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
		float acum = 0;
		for (short y = 0; y < n; y++) {
			for (short x = 0; x < m; x++) {
				acum = 0;
				for (short z = 0; z < b; z++) {
					acum = acum + (m1[z][y] * m2[x][z]);
				}
				r[x][y] = acum;
			}
		}
		Matrix* ret = new Matrix(r, m, n);
		return ret;
	}
};

void CreateAritmeticMenu(HWND hWindow) {
	EnableWindow(hBtnArit, false); EnableWindow(hBtnComp, true);
	hStA1 = CreateWindow(
		"STATIC",
		"Matriz 1",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		80, 40, 100, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix1 = CreateWindowEx(
		0, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL,
		10, 60, 250, 200,
		hWindow, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStA2 = CreateWindow(
		"STATIC",
		"Matriz 2",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		440, 40, 100, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix2 = CreateWindowEx(
		0, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL,
		365, 60, 250, 200,
		hWindow, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hStA3 = CreateWindow(
		"STATIC",
		"Matriz Resultante",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		240, 270, 160, 20, hWindow, NULL, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hEdtMatrix3 = CreateWindowEx(
		0, "EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		195, 290, 250, 200,
		hWindow, (HMENU)EDT_MATRIX1, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnAdd = CreateWindowEx(
		0, "BUTTON",
		"+",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 60, 105, 66,
		hWindow, (HMENU)BTN_ADD, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnSub = CreateWindowEx(
		0, "BUTTON",
		"-",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 126, 105, 66,
		hWindow, (HMENU)BTN_SUB, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnMult = CreateWindowEx(
		0, "BUTTON",
		"x",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 192, 105, 66,
		hWindow, (HMENU)BTN_MULT, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnClean = CreateWindowEx(
		0, "BUTTON",
		"Limpiar Cuadros",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		465, 10, 150, 25,
		hWindow, (HMENU)BTN_CLEAN, (HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
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

void CreateCompoundMatrixMenu(HWND hWindow) {
	EnableWindow(hBtnComp, false); EnableWindow(hBtnArit, true);
}
void DestroyCompoundMatrixMenu() {

}

void initializeMatrix(float** mat, short columns, short rows) {
	for (short x = 0; x < columns; x++) {
		for (short y = 0; y < rows; y++) {
			mat[x][y] = 0;
		}
	}
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
			sprintf(mat, "%.2f",pMatrix[x][y]);
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

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE: {
		hBtnArit = CreateWindowEx(
			0, "BUTTON", 
			"Matrices Aritméticas", 
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
		CreateAritmeticMenu(hWnd);
		break;
	}
	case WM_COMMAND: {
		switch (wParam) {
		case BTN_ARIT:
			DestroyCompoundMatrixMenu();
			CreateAritmeticMenu(hWnd);
			break;
		case BTN_COMP:
			DestroyAritmeticMenu();
			CreateCompoundMatrixMenu(hWnd);
			break;
		case BTN_CLEAN:
			SetWindowText(hEdtMatrix1, "");
			SetWindowText(hEdtMatrix2, "");
			SetWindowText(hEdtMatrix3, "");
			break;
		case BTN_ADD: {
			Matrix* matrix1 = buildMatrix(hEdtMatrix1);
			if (matrix1 == NULL) {
				MessageBox(hWnd, "La matriz 1 contiene caracteres invalidos o esta vacía.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			Matrix* matrix2 = buildMatrix(hEdtMatrix2);
			if (matrix2 == NULL) {
				MessageBox(hWnd, "La matriz 2 contiene caracteres invalidos o esta vacía.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
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
				MessageBox(hWnd, "La matriz 1 contiene caracteres invalidos o esta vacía.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			Matrix* matrix2 = buildMatrix(hEdtMatrix2);
			if (matrix2 == NULL) {
				MessageBox(hWnd, "La matriz 2 contiene caracteres invalidos o esta vacía.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
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
		case BTN_MULT:
			Matrix* matrix1 = buildMatrix(hEdtMatrix1);
			if (matrix1 == NULL) {
				MessageBox(hWnd, "La matriz 1 contiene caracteres invalidos o esta vacía.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
				break;
			}
			Matrix* matrix2 = buildMatrix(hEdtMatrix2);
			if (matrix2 == NULL) {
				MessageBox(hWnd, "La matriz 2 contiene caracteres invalidos o esta vacía.", "No se pudo capturar la matriz", MB_ICONEXCLAMATION);
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