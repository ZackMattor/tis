#ifndef PROTOCOLGLOBALS_H
#define PROTOCOLGLOBALS_H

namespace Protocol {
    enum ProtocolIds {
        InvalidVersion = 0,
        VersionOne = 0x74697331, // "tis1" in ascii/hex
        CurrentVersion = VersionOne
    };

    enum Commands {
        InvalidCommand = 0,
        // Client Commands
        PlayerConnect,
        PlayerDisconnect,
        PlayerHeartbeat,
        PlayerThrustFoward,
        PlayerThrustReverse,
        PlayerRotateRight,
        PlayerRotateLeft,
        PlayerFireWeapon,
        PlayerSelectWeapon,
        // Server Responses
        PlayerConnectResponse,
        PlayerDisconnected,
        GameUpdate,
        PlayerDead
    };

    enum ErrorCodes {
        InvalidCode = 0,
        Successful = -1,
        PermissionDenied = 1,
        LoginFailed = 2,
        ServerFull = 3
    };
}

#endif // PROTOCOLGLOBALS_H
