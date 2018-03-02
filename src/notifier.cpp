#include "notifier.h"
#include "riomessage.h"
#include <iostream>


void Notifier::NotifyUI(std::string message)
{
    std::string currentBlock;       // Block refers to tag, message, and terminating symbols
    std::string currentTag;
    std::string currentMessage;

    while(message.size() != 0)
    {
        currentBlock = message.substr(0 , message.find(RioMessage::MSG_END));
        currentTag = currentBlock.substr(0 , currentBlock.find(RioMessage::TAG_END));
        currentMessage = currentBlock.substr(message.find(RioMessage::TAG_END) + 1);
        message = message.substr(message.find(RioMessage::MSG_END) + 1);

//        std::cout << "CurrentBlock: " << currentBlock << std::endl;
//        std::cout << "CurrentTag: " << currentTag << std::endl;
//        std::cout << "CurrentMsg: " << currentMessage << std::endl;
//        std::cout << "Message: " << message << std::endl << std::endl;


        if(currentTag == "LEnc")
        {
            emit NotifyLeftEncoder(std::stoi(currentMessage));
        }
        else if(currentTag == "REnc")
        {
            emit NotifyRightEncoder(std::stoi(currentMessage));
        }
        else if(currentTag == "FEnc")
        {
            emit NotifyFlipperEncoder(std::stoi(currentMessage));
        }
        else if(currentTag == "Yaw")
        {
            emit NotifyYaw(std::stod(currentMessage));
        }
        else if(currentTag == "Roll")
        {
            emit NotifyRoll(std::stod(currentMessage));
        }
        else if(currentTag == "Pitch")
        {
            emit NotifyPitch(std::stod(currentMessage));
        }
        else
        {
            emit NotifyLog(currentTag + ": " + currentMessage);
        }
    }
}
