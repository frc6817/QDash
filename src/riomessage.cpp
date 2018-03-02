#include "riomessage.h"


RioMessage::RioMessage(const std::string TAG, const std::string MSG) :
    m_tag(TAG) , m_msg(MSG) , MSG_END("`") , TAG_END("|")
{
    // Empty
}


std::string RioMessage::Message()
{
    return m_tag + TAG_END + m_msg + MSG_END;
}
