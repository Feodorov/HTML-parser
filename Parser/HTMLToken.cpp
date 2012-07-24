#include "HTMLToken.h"


std::string HTMLTokenTypeString[] =
{
    std::string("HTMLT_EQUALS"),
    std::string("HTMLT_IDENT"),
    std::string("HTMLT_LBRACKET"),
    std::string("HTMLT_LSLASH"),
    std::string("HTMLT_RBRACKET"),
    std::string("HTMLT_RSLASH"),
    std::string("HTMLT_VALUE")
};

HTMLToken::HTMLToken(HTMLTokenType token, std::string value) : m_token_type(token),
m_value(value)
{   
    logger = log4cxx::Logger::getLogger("logger");
    /*if(value.empty())
        LOG4CXX_INFO(logger, "[HTMLToken]: " << HTMLTokenTypeString[token].c_str())
    else
        LOG4CXX_INFO(logger, "[HTMLToken]: " << HTMLTokenTypeString[token].c_str() << ": "<< value.c_str());*/
}

std::string HTMLToken::value()
{
    return m_value;
}

HTMLTokenType HTMLToken::type()
{
    return m_token_type;
}