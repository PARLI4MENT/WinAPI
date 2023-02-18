#include <Windows.h>
#include <iostream>
#include <conio.h>

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
    setlocale(0, "");
    MSG msg{};
    HWND hwnd{};
    WNDCLASSEX wc{sizeof(WNDCLASSEX)};

    /// дополнительное выделение памяти в классе окна
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;

    /// дескриптор кисти -> окрасить окно
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

    /// Подгрузка курсора, иконки и маленькой иконки
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    wc.hInstance = hInstance;
    wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        switch (uMsg)
        {
        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS);
        }
            return 0;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    };

    /// уникальное имя класса
    wc.lpszClassName = L"MyFirstApp";

    /// указатель на Меню
    wc.lpszMenuName = nullptr;

    /// стили окна с default значениями флагов
    wc.style = CS_VREDRAW | CS_HREDRAW;

    /// Ругистрация класс окна
    if (!RegisterClassEx(&wc))
        return EXIT_FAILURE;

    //if (hwnd = CreateWindow(wc.lpszClassName, L"Заголовок!", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
    if ((hwnd = CreateWindow(wc.lpszClassName, L"Заголовок!", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr)) == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
    // return EXIT_SUCCESS;
}