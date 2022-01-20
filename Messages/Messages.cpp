#include "framework.h"
#include "Messages.h"
#include <windowsx.h>

#define MAX_LOADSTRING 100
#define CMD_BUTTON_CLEAR 1001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND static1;
HWND static2;
HWND static3;
HWND list1;
HWND list2;
HWND list3;
HWND but1;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MESSAGES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MESSAGES));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MESSAGES));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MESSAGES);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        static1 = CreateWindow(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 10, 90, 15, hWnd, 0, hInst, NULL);
        static2 = CreateWindow(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
            110, 10, 90, 15, hWnd, 0, hInst, NULL);
        static3 = CreateWindow(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
            210, 10, 90, 15, hWnd, 0, hInst, NULL);
        list1 = CreateWindow(L"Listbox", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            10, 35, 90, 400, hWnd, 0, hInst, NULL);
        list2 = CreateWindow(L"Listbox", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            110, 35, 90, 400, hWnd, 0, hInst, NULL);
        //but1 = CreateWindow(L"Button", L"Clear", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        //    180, 35, 75, 23, hWnd, (HMENU)CMD_BUTTON_CLEAR, hInst, NULL);
        break;
    case WM_MOUSEMOVE:
        GET_X_LPARAM(lParam);
        GET_Y_LPARAM(lParam);
        break;
    case WM_KEYDOWN:
    {
        WCHAR str[100];
        _snwprintf_s(str, 100, L"%d %u %u", wParam, (lParam >> 16) & 255, (lParam >> 24) & 63);
        SendMessageW(static1, WM_SETTEXT, 100, (LPARAM)str);
        SendMessageW(list1, LB_ADDSTRING, 100, (LPARAM)str);
        break;
    }
    case WM_KEYUP:
        WCHAR str[100];
        _snwprintf_s(str, 100, L"%d %u %u", wParam, (lParam >> 16) & 255, (lParam >> 24) & 63);
        SendMessageW(static2, WM_SETTEXT, 100, (LPARAM)str);
        SendMessageW(list2, LB_ADDSTRING, 100, (LPARAM)str);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case CMD_BUTTON_CLEAR:
            SendMessageW(list1, LB_RESETCONTENT, 0, 0);
            SendMessageW(list2, LB_RESETCONTENT, 0, 0);
            SendMessageW(but1, WM_KILLFOCUS, 0, 0);
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}