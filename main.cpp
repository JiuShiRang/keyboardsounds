#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include "soundplayer.h"
// code from Jeffrey Holmes's answer at
// https://stackoverflow.com/questions/2167876/is-it-possible-to-use-win32-hooks-in-qt-applications
//extern "C"
//{
#include <windows.h>
//#include <mmsystem.h>
//}
#include <QChar>
#include <QDebug>
#include <QTime>
#include <iostream>
//#pragma comment(lib, "user32.lib")
//#pragma comment(lib, "winmm.lib")

HHOOK hHook = NULL;

using namespace std;

void UpdateKeyState(BYTE* keystate, int keycode) {
  keystate[keycode] = GetKeyState(keycode);
}

LRESULT CALLBACK MyLowLevelKeyBoardProc(int nCode,
                                        WPARAM wParam,
                                        LPARAM lParam) {
  // WPARAM is WM_KEYDOWn, WM_KEYUP, WM_SYSKEYDOWN, or WM_SYSKEYUP
  // LPARAM is the key information

//  qDebug() << "Key Pressed!";

  if (wParam == WM_KEYDOWN) {
    // Get the key information
    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);

    wchar_t buffer[5];

    // get the keyboard state
    BYTE keyboard_state[256];
    GetKeyboardState(keyboard_state);
    UpdateKeyState(keyboard_state, VK_SHIFT);
    UpdateKeyState(keyboard_state, VK_CAPITAL);
    UpdateKeyState(keyboard_state, VK_CONTROL);
    UpdateKeyState(keyboard_state, VK_MENU);

    // Get keyboard layout
    HKL keyboard_layout = GetKeyboardLayout(0);

    // Get the name
    char lpszName[0X100] = {0};

    DWORD dwMsg = 1;
    dwMsg += cKey.scanCode << 16;
    dwMsg += cKey.flags << 24;

    int i = GetKeyNameText(dwMsg, (LPTSTR)lpszName, 255);

    // Try to convert the key information
    int result = ToUnicodeEx(cKey.vkCode, cKey.scanCode, keyboard_state, buffer,
                             4, 0, keyboard_layout);
    buffer[4] = L'\0';

    // Print the output
//    PlaySound(TEXT("a.mp3"), NULL, SND_FILENAME | SND_ASYNC);

//    static QMediaPlayer mp(NULL, QMediaPlayer::LowLatency);
//    static bool init = true;
//    if(init) {
//        mp.setMedia(QUrl::fromLocalFile("a.mp3"));
//        mp.play();
//        init = false;
//    }
////    mp.stop();
//    mp.play();

    SoundPlayer::getInstance().playByCode(0);
  }

  return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);



  hHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelKeyBoardProc, NULL, 0);
  if (hHook == NULL) {
    qDebug() << "Hook Failed" << endl;
  }

  return a.exec();
}
