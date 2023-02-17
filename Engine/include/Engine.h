//
// Created by madahin on 10/03/2021.
//

#ifndef CHESSENGINE_ENGINE_H
#define CHESSENGINE_ENGINE_H

#include <array>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

#include "Board.h"
#include "Logger.h"

class Engine;

typedef void (Engine::*FnCommand)(const std::string &strCmd);

class Engine
{
private:
    struct stCommands
    {
        std::string strCommandName;
        FnCommand pfnCommand;
    };

    std::istream& m_inputStream;
    std::ostream& m_outputStream;

    bool m_bDebug;
    bool m_bMustQuit;
    bool m_bIsReady;

    Board m_board;
    std::vector<stCommands> m_vecKnownCommand;

public:
    Engine();
    Engine(std::istream& inputStream, std::ostream& outputStream);
    void Start();

private:
    std::vector<std::string> ParseArgs(const std::string& strArgs);

    void CmdUCI(const std::string &strCmd);
    void CmdQuit(const std::string &strCmd);
    void CmdDebug(const std::string &strCmd);
    void CmdOption(const std::string &strCmd);
    void CmdIsReady(const std::string &strCmd);
    void CmdICUNewGame(const std::string &strCmd);

    void Debug(const std::string &strDebugString) const;

    auto SendCommand(std::string_view command) const -> void;
};


#endif //CHESSENGINE_ENGINE_H
