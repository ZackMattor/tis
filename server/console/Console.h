#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>

#include "ConsoleCommands.h"

/*
  Class: Console
  A class that provides an I/O interface to stdout/stdin,
  as well as primitive shell services for the server.
*/
class Console : public QObject
{
    Q_OBJECT
public:
    /*
      Constructor: Console

      Initializes a Console object

      Parameters:

          parent - The Console's parent in the QObject heirarchy.
    */
    explicit Console(QObject *parent = 0);

private:
    void displayHelp(const QStringList &cmds);
    void displayAliases(const QString &cmd);
    
public slots:
    /*
      Function: write

      Prints the given string to stdout verbatim.

      Parameters:

          data - The string data to be printed

      See Also:
          <writeLine>
    */
    void write(const QString &data);

    /*
      Function: writeLine

      Prints the given string to stdout, appending a newline.

      Parameters:

          line - The line of text to be printed

      See Also:
          <write>
    */
    void writeLine(const QString &line);

private slots:
    void readStdin(int socket);
    void parseCommand(const QString &command);

signals:
    /*
      Signal: commandEntered

      Emitted when a valid command has been issued when the user
      presses "Enter" on the keyboard.

      Parameters:

      type - The type of the issued command.
      args - A list of additional arguments, if any that were
             entered separated by spaces.
    */
    void commandEntered(CommandType type, QStringList args);
};

#endif // CONSOLE_H
