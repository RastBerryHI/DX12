#include "pch\pch.h"

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

#define EXIT_SUCCESS 0

WCHAR WindowClass[MAX_NAME_STRING];
WCHAR WindowTitle[MAX_NAME_STRING];

INT WindowWidth;
INT WindowHeight;


LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return DefWindowProc(hWnd, message, wparam, lparam);
}


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
    // Initializing Global Variables
    wcscpy_s(WindowClass, TEXT("TutorialOneClass"));
    wcscpy_s(WindowTitle, TEXT("First Window"));
    WindowWidth = 1366;
    WindowHeight = 768;
    
    // Creating window class
    WNDCLASSEX wcex;
    
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(GetStockObject(NULL_BRUSH));
    
    wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
    wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

    wcex.lpszClassName = WindowClass;
    
    wcex.lpszMenuName = nullptr;

    wcex.hInstance = HInstance();

    // Defines default behaviour for window - program will run even after closing window
    //wcex.lpfnWndProc = DefWindowProc;

    wcex.lpfnWndProc = WindowProcess;
    
    RegisterClassEx(&wcex);

    // Create and display window
    HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);

    if (!hWnd)
    {
        MessageBox(0, L"Failed to Create Window!.", 0, 0);
        return 0;
    }
    
    ShowWindow(hWnd, SW_SHOW);

    // Listen for message events

    MSG msg = {0};
    while (msg.message != WM_QUIT)
    {
        // If there are window messages then process them
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    
    return 0;
}