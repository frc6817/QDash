#include "riomessage.h"


const std::string RioMessage::MSG_END = "`";
const std::string RioMessage::TAG_END = "|";


RioMessage::RioMessage(const std::string TAG, const std::string MSG) :
    m_tag(TAG) , m_msg(MSG)
{
    // Empty
}


std::string RioMessage::Message()
{
    return m_tag + TAG_END + m_msg + MSG_END;
}
