#ifndef HTML_PARSER_H_
#define HTML_PARSER_H_

#include <list>
#include <set>
#include "HTMLToken.h"
#include "HTMLElement.h"
#include "HTMLParser.h"
#include "HTMLLexer.h"

class HTMLParser
{
public:
	HTMLParser(HTMLLexer_Ptr lexer);
	HTMLElement_CPtr parse();
	std::list<HTMLElement_Ptr> parse_elements();
        HTMLElement_Ptr parse_element();
	void check_token_and_type(
		const HTMLToken_Ptr& token,
		HTMLTokenType expectedType);
	HTMLToken_Ptr read_checked_token(HTMLTokenType expectedType);
	HTMLToken_Ptr read_token();
private:
	HTMLLexer_Ptr m_lexer;
        std::list<HTMLToken_Ptr> m_lookahead;
        std::set<std::string> m_unpaired_tags;
};
#endif //HTML_PARSER_H_
