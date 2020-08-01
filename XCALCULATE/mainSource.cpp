#include <Windows.h>
#include <stdio.h>

#define BTN_ARIT 101
#define BTN_COMP 102
#define EDT_MATRIX1 103
#define EDT_MATRIX2 104
#define EDT_MATRIX3 105
#define BTN_ADD 106
#define BTN_SUB	 107
#define BTN_MULT 108

HWND hBtnArit;
HWND hBtnComp;
HWND hEdtMatrix1;
HWND hEdtMatrix2;
HWND hEdtMatrix3;
HWND hBtnAdd;
HWND hBtnSub;
HWND hBtnMult;
HWND hStA1;
HWND hStA2;
HWND hStA3;

void CreateAritmeticMenu(HWND hWindow) {
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
		hWindow, (HMENU)EDT_MATRIX1,
		(HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
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
		hWindow, (HMENU)EDT_MATRIX1,
		(HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
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
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL,
		195, 290, 250, 200,
		hWindow, (HMENU)EDT_MATRIX1,
		(HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnAdd = CreateWindowEx(
		0, "BUTTON",
		"+",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 60, 105, 66,
		hWindow, (HMENU)BTN_ADD,
		(HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnSub = CreateWindowEx(
		0, "BUTTON",
		"-",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 126, 105, 66,
		hWindow, (HMENU)BTN_SUB,
		(HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
	);
	hBtnMult = CreateWindowEx(
		0, "BUTTON",
		"x",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 192, 105, 66,
		hWindow, (HMENU)BTN_MULT,
		(HINSTANCE)GetWindowLongPtr(hWindow, GWLP_HINSTANCE), NULL
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

}
void DestroyCompoundMatrixMenu() {

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
		EnableWindow(hBtnArit, false);
		CreateAritmeticMenu(hWnd);
		break;
	}
	case WM_COMMAND:
		
		break;
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