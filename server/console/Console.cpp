#include "Console.h"

#include <QtCore/QSocketNotifier>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <QtCore/QThread>

#ifdef Q_WS_WIN
#include "WinConsole.h"
#endif

const char *inPrompt = "<< ";
const char *outPrompt = ">> ";

Console::Console(QObject *parent)
    : QObject(parent)
{
#ifdef Q_WS_WIN
    WinConsole *console = new WinConsole(0);
    connect(console, SIGNAL(lineRead(QString)), SLOT(parseCommand(QString)));

    QThread *consoleThread = new QThread(this);
    console->moveToThread(consoleThread);
    consoleThread->start();
    QMetaObject::invokeMethod(console, "beginPolling", Qt::QueuedConnection);
#else
    QSocketNotifier *notifier = new QSocketNotifier(0, QSocketNotifier::Read, this);
    connect(notifier, SIGNAL(activated(int)), this, SLOT(readStdin(int)));
#endif
    write(inPrompt);
}

void Console::readStdin(int socket)
{
    Q_UNUSED(socket);

    QTextStream qin(stdin);
    QString line = qin.readLine();

    // Process line
    parseCommand(line);
}

void Console::parseCommand(const QString &line)
{
    QStringList args = line.trimmed().split(' ');
    QString command = args.first();
    args.removeAll(args.first());

    ConsoleCommands *commands = ConsoleCommands::singleton();
    CommandType type = commands->commandType(command);

    switch (type)
    {
    case HelpCommand:
        displayHelp(args);
        break;
    case AliasesCommand:
        if (args.size())
            displayAliases(args.first());
        break;
    default:
        emit commandEntered(type, args);
        break;
    }

    // Show new prompt
    write(inPrompt);
}

void Console::write(const QString &data)
{
    QTextStream qout(stdout);
    qout << data;
}

void Console::writeLine(const QString &line)
{
    QTextStream qout(stdout);
    qout << line << '\n';
}

void Console::displayHelp(const QStringList &cmds)
{
    ConsoleCommands *commands = ConsoleCommands::singleton();

    if (cmds.count())
    {
        QString help;
        foreach (const QString &cmd, cmds)
        {
            help = commands->help(cmd);
            if (!help.isEmpty())
                writeLine(help);
        }
    }
    else
    {
        // Print help for all commands
        writeLine("Help:");
        writeLine("============");

        for (int i = 0; i < CommandTypeSize; i++)
        {
            writeLine(commands->help((CommandType)i));
        }
    }
}

void Console::displayAliases(const QString &cmd)
{
    ConsoleCommands *commands = ConsoleCommands::singleton();
    QStringList aliases = commands->aliases(cmd);

    if (aliases.isEmpty())
        return;

    writeLine("Aliases for " + cmd + ':');
    foreach (const QString &alias, aliases)
    {
        writeLine('\"' + alias + '\"');
    }
}
