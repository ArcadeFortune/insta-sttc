#include "main.h"

void on_key_down() { isRecording = true; }

void on_key_up() { isRecording = false; }

LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode == HC_ACTION) {
    KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam;

    if (kbd->vkCode == VK_F10) {
      switch (wParam) {
      case WM_KEYDOWN:
        on_key_down();
        break;

      case WM_KEYUP:
        on_key_up();
        break;
      }
    }
  }

  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

DWORD WINAPI keyboardThread(void *arg) {
  HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHook, NULL, 0);

  if (!hook) {
    printf("Failed to install hook\n");
    return 1;
  }

  MSG msg;

  printf("Listening for keybind...\n");

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hook);

  return 0;
}
