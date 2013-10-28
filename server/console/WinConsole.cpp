#include "WinConsole.h"

#include <QtCore/QTextStream>
#include <QtCore/QThread>

#ifndef Q_OS_WIN
#include <unistd.h>
#else
#include "Windows.h"
#endif

WinConsole::WinConsole(QObject *parent)
    : QObject(parent)
{
}

void WinConsole::beginPolling()
{
    while(true)
    {
        poll();
#ifndef Q_OS_WIN
        usleep(100000); // Sleep 100 ms
#else
        Sleep(100);
#endif
    }
}

void WinConsole::poll()
{
    QTextStream stream(stdin);

    // Do we have a new line to be read ?
    QString line = stream.readLine();

    if (!line.isEmpty())
        emit lineRead(line);
    else
        emit lineRead("help");
}
