#ifndef HTML_LEXER_H_
#define HTML_LEXER_H_

#include <list>
#include <boost/shared_ptr.hpp>

#include "HTMLToken.h"
#include "DataStream.h"

typedef boost::shared_ptr<class HTMLLexer> HTMLLexer_Ptr;

enum HTMLState
{
	LEX_START,
	LEX_EOF,
	LEX_EQUALS,
	LEX_HALF_RSLASH,
	LEX_HALF_VALUE_QUOTED,
	LEX_HALF_VALUE_UNQUOTED,
	LEX_LBRACKET,
	LEX_RBRACKET,
	LEX_IDENT,
	LEX_BAD,
	LEX_RSLASH,
	LEX_LSLASH,
	LEX_VALUE,
	LEX_HALF_DATA,
	LEX_DATA
};

class HTMLLexer
{
public:
	HTMLLexer(DataStream_Ptr data_source);
	HTMLToken_Ptr next_token();
private:
	unsigned char next_char();
	bool m_eof;
	HTMLState m_state;
	std::list<unsigned char> m_lookahead;
	std::string m_lookback;
	DataStream_Ptr m_is;
};

#endif //HTML_LEXER_H_
