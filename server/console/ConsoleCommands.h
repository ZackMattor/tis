#ifndef CONSOLECOMMANDS_H
#define CONSOLECOMMANDS_H

#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVector>

enum CommandType {
    HelpCommand = 0,
    QuitCommand,
    StartCommand,
    StopCommand,
    BindCommand,
    AliasesCommand,
    KickCommand,
    WhoCommand,
    CommandTypeSize // Used to keep track of enum size, not a command
};

class ConsoleCommands
{
public:
    ConsoleCommands();
    static ConsoleCommands* singleton();

    CommandType commandType(const QString &str) const;
    QString commandString(CommandType type) const;

    QString help(const QString &cmd) const;
    QString help(CommandType type) const;
    QStringList aliases(const QString &cmd) const;
    QStringList aliases(CommandType type) const;

private:
    QHash<QString, CommandType> m_commandHash;
    QVector<QString> m_helpTexts;

    QHash<QString, CommandType> commandHash();
    QVector<QString> helpTexts();
};

#endif // CONSOLECOMMANDS_H
