#ifndef RIOMESSAGE_H
#define RIOMESSAGE_H


#include <iostream>


class RioMessage
{
public:
    const static std::string MSG_END;
    const static std::string TAG_END;


    /**
     * @brief Converts the tag and message into a RioMessage. A RioMessage
     * consists of the tag, followed by a tag end character, followed by the
     * message, followed by a message end character. If the message is empty,
     * A zero will automatically be appended to the tag end character.
     *
     * @param TAG Message tag- this is usually a brief categorization of the
     * message content. Usually acts as an identifier of the data.
     * @param MSG Raw message content- usually, this is the data we're most
     * concerned with.
     */
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
