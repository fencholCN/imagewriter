#include <comutil.h>

#include <QApplication>

#include "maindialog.h"

// For now, only Windows platform is supported
// Non-cross-platform code:
//  1. USB devices enumeration;
//  2. reading/writig the image file;
//  3. unmounting of USB device volumes before writing;
//  4. CoInitializeSecurity in main();
//  5. WinAPI-specific headers, libraries, resources (icon, manifest), drag&drop MIME types (?).
#ifndef Q_OS_WIN32
#error Only Win32 is supported!
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // CoInitialize() seems to be called by Qt automatically, so only set security attributes
    HRESULT res = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, 0);
    if (res != S_OK)
    {
        printf("CoInitializeSecurity failed! (Code: 0x%08x)\n", res);
        return res;
    }

    MainDialog w;
    w.show();
    
    return a.exec();
}
