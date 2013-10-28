#ifndef WINCONSOLE_H
#define WINCONSOLE_H

#include <QtCore/QObject>

/*
  Class: WinConsole
  This class provides an interactive stdin interface for
  Windows. By default, Windows' stdin implementation cannot
  notify us of new input via POSIX-compliant methods. (It is
  not a file, pipe or socket.) To work around this, we must
  poll every 100 ms in a separate thread for input.
*/
class WinConsole : public QObject
{
    Q_OBJECT
public:
    WinConsole(QObject *parent = 0);

public slots:
    void beginPolling();

private slots:
    void poll();

signals:
    void lineRead(const QString &line);
};

#endif // WINCONSOLE_H
