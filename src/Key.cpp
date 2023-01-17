#include "Key.hpp"

bool Key::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    bool inActivatorDirections = false;
    Position curPos = current->getPosition();
    Direction curDirInv = invertDirection(current->getDirection());

    for(auto &d : m_activatorDirections)
    {
        if(d == curDirInv)
        {
            inActivatorDirections = true;
            break;
        }
    }

    if(inActivatorDirections)
    {
        m_sourceCode[curPos.y][curPos.x] = m_transformTo;
        defaultLogger.log(LogType::INFO, "Key is activated...");
        return true;
    }

    if(!Cable::work(current, currentVector))
        return false;
    
    // If not in activator directions move the current back
    Position newPos = curPos + directionToPosition(curDirInv);
    current->setPosition(newPos);
    defaultLogger.log(LogType::INFO, "Key is not activated. Moving back...");

    return true;
}