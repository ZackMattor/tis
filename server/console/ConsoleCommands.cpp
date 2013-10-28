#include "ConsoleCommands.h"

#include "qglobal.h"

Q_GLOBAL_STATIC(ConsoleCommands, singletonInstance)

ConsoleCommands *ConsoleCommands::singleton()
{
    return singletonInstance();
}

ConsoleCommands::ConsoleCommands()
    : m_commandHash(commandHash())
    , m_helpTexts(helpTexts())
{
}

CommandType ConsoleCommands::commandType(const QString &str) const
{
    return m_commandHash.value(str);
}

QString ConsoleCommands::commandString(CommandType type) const
{
    return m_commandHash.key(type);
}

QString ConsoleCommands::help(const QString &cmd) const
{
    return help(commandType(cmd));
}

QString ConsoleCommands::help(CommandType type) const
{
    return m_helpTexts.at(type);
}

QStringList ConsoleCommands::aliases(const QString &cmd) const
{
    return aliases(commandType(cmd));
}

QStringList ConsoleCommands::aliases(CommandType type) const
{
    return m_commandHash.keys(type);
}

QHash<QString, CommandType> ConsoleCommands::commandHash()
{
    QHash<QString, CommandType> hash;

    // Quit aliases
    hash["quit"] = QuitCommand;
    hash["q"] = QuitCommand;

    // Help aliases
    hash["help"] = HelpCommand;
    hash["?"] = HelpCommand;

    // Generic Server Commands
    hash["start"] = StartCommand;
    hash["stop"] = StopCommand;
    hash["bind"] = BindCommand;
    hash["aliases"] = AliasesCommand;

    // Kick aliases
    hash["kick"] = KickCommand;
    hash["boot"] = KickCommand;
    hash["kline"] = KickCommand;

    // Who aliases
    hash["who"] = WhoCommand;

    return hash;
}

QVector<QString> ConsoleCommands::helpTexts()
{
    QVector<QString> help(CommandTypeSize);

    help[QuitCommand]    = "quit:\t\t\tStops the server and quits.";
    help[HelpCommand]    = "help <cmd>:\t\tShows help for a specific item. If blank, it shows the whole list.";
    help[StartCommand]   = "start:\t\t\tStarts the server. Binds to the most-recently bound port.";
    help[StopCommand]    = "stop:\t\t\tStops the server, but does not quit.";
    help[BindCommand]    = "bind <port>:\t\tSets the server to use the given port.";
    help[AliasesCommand] = "aliases <cmd>:\t\tShows aliases for the given command, if any.";
    help[KickCommand]    = "kick <user> <reason>:\tKicks <user> for <reason>.";
    help[WhoCommand]     = "who:\tShows a list of who is online.";

    return help;
}
