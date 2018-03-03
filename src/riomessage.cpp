#include "riomessage.h"


const std::string RioMessage::MSG_END = "`";
const std::string RioMessage::TAG_END = "|";


RioMessage::RioMessage(const std::string TAG, const std::string MSG) :
    m_tag(TAG) , m_msg(MSG)
{
    // Add something so that things don't break
    if(m_msg == "")
    {
        m_msg = "0";
    }
}


std::string RioMessage::Message()
{
    return m_tag + TAG_END + m_msg + MSG_END;
}
