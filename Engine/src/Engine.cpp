//
// Created by madahin on 10/03/2021.
//

#include "Engine.h"

Engine::Engine() :
    Engine(std::cin, std::cout)
{
}

Engine::Engine(std::istream& inputStream, std::ostream& outputStream) :
    m_inputStream(inputStream),
    m_outputStream(outputStream),
    m_bDebug(true),
    m_bMustQuit(false),
    m_bIsReady(true)
{
    m_vecKnownCommand = {
            {"ucinewgame", &Engine::CmdICUNewGame},
            {"uci"       , &Engine::CmdUCI       },
            {"quit"      , &Engine::CmdQuit      },
            {"debug"     , &Engine::CmdDebug     },
            {"option"    , &Engine::CmdOption    },
            {"isready"   , &Engine::CmdIsReady   },
    };

    CmdICUNewGame("");
}


void Engine::Start()
{
    Log::Info("------------ Engine Start ------------");

    Move::Init();

    while(!m_bMustQuit)
    {
        std::string strInput;
        getline(m_inputStream, strInput);

        Log::Info("GUI -> Engine: {}", strInput);

        for(const stCommands& command : m_vecKnownCommand)
        {
            if (strInput.rfind(command.strCommandName, 0) == 0)
            {
                std::invoke(command.pfnCommand, this, strInput);
                break;
            }
        }
    }
}

std::vector<std::string> Engine::ParseArgs(const std::string &strArgs)
{
    std::vector<std::string> vecArgs;
    std::stringstream ssArgs(strArgs);
    std::string strToken;
    bool bFirst = true;

    while(getline(ssArgs, strToken, ' '))
    {
        if (bFirst)
        {
            bFirst = false;
        }
        else
        {
            vecArgs.push_back(strToken);
        }
    }

    return vecArgs;
}

void Engine::CmdUCI(const std::string &strCmd)
{
    SendCommand("id name BobTheChessEngine");
    SendCommand("id author Madahin"  );
    SendCommand("icuok"              );
    SendCommand("readyok"            );
}

void Engine::CmdQuit(const std::string&)
{
    m_bMustQuit = true;
}

void Engine::CmdDebug(const std::string &strCmd)
{
    std::vector<std::string> vecArgs = ParseArgs(strCmd);

    if (!vecArgs.empty())
    {
        if (vecArgs[0] == "on")
        {
            m_bDebug = true;
        } else if (vecArgs[0] == "off")
        {
            m_bDebug = false;
        }
        else
        {
            Log::Warn("debug [on|off]: Invalid argument\n");
        }
    }
    else
    {
        Log::Warn("debug [on|off]: No argument given\n");
    }
}

void Engine::CmdOption(const std::string &strCmd)
{

}

void Engine::CmdIsReady(const std::string &strCmd)
{
    SendCommand("readyok");
}

void Engine::CmdICUNewGame(const std::string&)
{
    m_board.LoadFenString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

auto Engine::SendCommand(std::string_view command) const -> void
{
    Log::Info("Engine -> GUI: {}", command);
    m_outputStream << command << std::endl;
}

void Engine::Debug(const std::string &strDebugString) const
{
    if (m_bDebug)
    {
        SendCommand(fmt::format("info string {}", strDebugString));
    }
}

