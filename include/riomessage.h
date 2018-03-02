#ifndef RIOMESSAGE_H
#define RIOMESSAGE_H


#include <iostream>


class RioMessage
{
public:
    const static std::string MSG_END;
    const static std::string TAG_END;


    RioMessage(const std::string TAG , const std::string MSG);


    /**
     * @brief Converts current message to a more usable string literal
     *
     * @return String literal representation of message
     */
    std::string Message();


private:
    std::string m_tag;
    std::string m_msg;
};


#endif // RIOMESSAGE_H
