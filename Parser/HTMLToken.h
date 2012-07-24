#ifndef HTMLTOKEN_H_
#define	HTMLTOKEN_H_

#include <string>

#include <log4cxx/log4cxx.h>
#include <log4cxx/rollingfileappender.h>
#include <log4cxx/patternlayout.h>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<class HTMLToken> HTMLToken_Ptr;

enum HTMLTokenType{
    HTMLT_EQUALS,
    HTMLT_IDENT,
    HTMLT_LBRACKET,
    HTMLT_LSLASH,
    HTMLT_RBRACKET,
    HTMLT_RSLASH,
    HTMLT_VALUE,
	HTMLT_DATA
};

class HTMLToken
{
public:
    HTMLToken(HTMLTokenType token, std::string value);
    std::string value();
    HTMLTokenType type();
private:
    HTMLTokenType m_token_type;
    std::string m_value;
    log4cxx::LoggerPtr logger;
};

#endif	//HTMLTOKEN_H_

