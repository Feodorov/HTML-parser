#include <string>
#include <locale>

#include "HTMLLexer.h"

HTMLToken_Ptr HTMLLexer::next_token()
{
	std::locale loc ("rus_rus.1251");
	if(m_state == LEX_EOF) return HTMLToken_Ptr();
	else m_state = LEX_START;
	std::string value;
	unsigned char c;
	for(;;)
	{
		switch(m_state)
		{
		case LEX_START:
			{
				c = next_char();
				if(m_eof) { m_state = LEX_EOF; }
				else if(c == '=') {
					m_state = LEX_EQUALS; }
				else if(c == '/') {
					m_state = LEX_HALF_RSLASH; }
				else if(c == '"') {
					m_state = LEX_HALF_VALUE_QUOTED; }
				else if(c == '<') {
					m_state = LEX_LBRACKET; }
				else if(c == '>') {
					m_state = LEX_RBRACKET; }
				else if(isalpha(c, loc) || isdigit(c, loc) ||
					c == '.' || c == ';' || c == '&') 
				{
					if(m_lookback[0] == '=') 
						m_state = LEX_HALF_VALUE_UNQUOTED;
					else if(m_lookback[0] == '>') m_state = LEX_HALF_DATA; 
					else m_state = LEX_IDENT;
					value += c;
				}
				break;
			}
		case LEX_EOF:
			{
				return HTMLToken_Ptr();
			}
		case LEX_EQUALS:
			{
				return HTMLToken_Ptr(
					new HTMLToken(HTMLT_EQUALS, ""));
			}
		case LEX_HALF_RSLASH:
			{
				c = next_char();
				if(m_eof) {
					m_state = LEX_BAD; value = ">"; }
				else if(c == '>') {
					m_state = LEX_RSLASH; }
				else { m_state = LEX_BAD; value = ">"; }
				break;
			}
		case LEX_HALF_VALUE_QUOTED:
			{
				c = next_char();				
				if(m_eof) 
				{
					m_state = LEX_BAD;
					value = "\""; 
				}
				else if(c == '"') { m_state = LEX_VALUE; }
				else { value += c; }
				break;
			}
		case LEX_HALF_VALUE_UNQUOTED:
			{
				c = next_char();				
				if(m_eof) 
				{
					m_state = LEX_BAD; 
					value = "\""; 
				}
				else if(c == ' ') { m_state = LEX_VALUE; }
				else if(c == '>') { 
					m_lookahead.push_back(c);
					m_state = LEX_VALUE; }
				else { value += c; }
				break;
			}
		case LEX_HALF_DATA:
			{
				c = next_char();				
				if(m_eof) 
				{
					m_state = LEX_BAD; 
					value = "\""; 
				}
				else if(c == '<') { 
					m_lookahead.push_back(c);
					m_state = LEX_DATA; }
				else { value += c; }
				break;
			}
		case LEX_IDENT:
			{
				c = next_char();
				if(m_eof)
				{
					m_state = LEX_EOF;
					return HTMLToken_Ptr(new HTMLToken(
						HTMLT_IDENT,value));
				}
				else if(isalpha(c, loc) || isdigit(c, loc) ||
					c == '.' || c == '_' || c =='-')
				{
					value += c;
				}
				else
				{
					m_lookahead.push_back(c);
					return HTMLToken_Ptr(new HTMLToken(
						HTMLT_IDENT, value));
				}
				break;
			}
		case LEX_LBRACKET:
			{
				c = next_char();
				if(m_eof)
				{
					m_state = LEX_EOF;
					return HTMLToken_Ptr(new HTMLToken(
						HTMLT_LBRACKET, ""));
				}
				else if(c == '/')
				{
					m_state = LEX_LSLASH;
				}
				else
				{
					m_lookahead.push_back(c);
					return HTMLToken_Ptr(new HTMLToken(
						HTMLT_LBRACKET, ""));
				}
				break;
			}
		case LEX_LSLASH:
			{
				return HTMLToken_Ptr(new HTMLToken(
					HTMLT_LSLASH, ""));
			}
		case LEX_RBRACKET:
			{
				return HTMLToken_Ptr(new HTMLToken(
					HTMLT_RBRACKET, ""));
			}
		case LEX_RSLASH:
			{
				return HTMLToken_Ptr(new HTMLToken(
					HTMLT_RSLASH, ""));
			}
		case LEX_VALUE:
			{
				return HTMLToken_Ptr(new HTMLToken(
					HTMLT_VALUE, value));
			}
		case LEX_DATA:
			{
				return HTMLToken_Ptr(new HTMLToken(
					HTMLT_DATA, value));
			}
		default: // case LEX_BAD
			{
				throw std::exception();
			}
		}
		if(!isspace(c) & !iscntrl(c)) 
		{
			m_lookback.clear();
			m_lookback += c;
		}
	}
}
unsigned char HTMLLexer::next_char()
{
	unsigned char c = 0;
	if(m_lookahead.empty())
	{
		try
		{
			c = m_is->get();
		}
		catch (std::exception &)
		{
			m_eof = true;
		}
	}
	else
	{
		c = m_lookahead.front();
		m_lookahead.pop_front();
		m_eof = false;
	}
	return c;
}

HTMLLexer::HTMLLexer(DataStream_Ptr data_source):m_is(data_source)
{
	m_eof = false;
	m_state = LEX_START;
}