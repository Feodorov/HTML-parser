#include "HTMLParser.h"

HTMLParser::HTMLParser(HTMLLexer_Ptr lexer):m_lexer(lexer)
{
	m_unpaired_tags.insert(std::string("base"));
	m_unpaired_tags.insert(std::string("meta"));
	m_unpaired_tags.insert(std::string("br"));
	m_unpaired_tags.insert(std::string("input"));
	m_unpaired_tags.insert(std::string("img"));
}

HTMLElement_CPtr HTMLParser::parse()
{
	HTMLElement_Ptr root(new HTMLElement("<root>"));
	std::list<HTMLElement_Ptr> children =
		parse_elements();
	for(std::list<HTMLElement_Ptr>::
		const_iterator it=children.begin(),
		iend=children.end(); it!=iend; ++it)
	{
		root->add_child(*it);
	}
	return root;
}
std::list<HTMLElement_Ptr>
HTMLParser::parse_elements()
{
	std::list<HTMLElement_Ptr> elements;
	HTMLElement_Ptr element;
	while(element = parse_element())
	{
		elements.push_back(element);
	}
	return elements;
}
HTMLElement_Ptr HTMLParser::parse_element()
{
	HTMLToken_Ptr token;        
	token = read_token();
	if(!token)
	{
		// If there are no tokens left, we're done.
		return HTMLElement_Ptr();
	}
	if(token->type() == HTMLT_DATA)
	{
		//we found the data
		HTMLElement_Ptr element(new HTMLElement(
			std::string("data")));
		element->set_attribute(std::string("data"), token->value());
		token = read_token();
		switch(token->type())
		{
			case HTMLT_LSLASH:
			case HTMLT_LBRACKET:
				{
					m_lookahead.push_back(token);
					return element;					
				}			
			default:
				{
					throw std::exception();
				}
		}
	}
	if(token->type() != HTMLT_LBRACKET)
	{
		// If the token isn't '<' now, we're reading
		// something other than an element.
		m_lookahead.push_back(token);
		return HTMLElement_Ptr();
	}
	HTMLToken_Ptr ident_token = read_checked_token(HTMLT_IDENT);
	HTMLElement_Ptr element(new HTMLElement(
		ident_token->value()));
	token = read_token();
	while(token && token->type() == HTMLT_IDENT)
		// while there are attributes to be processed
	{
		std::string attribName = token->value();
		read_checked_token(HTMLT_EQUALS);
		token = read_checked_token(HTMLT_VALUE);
		std::string attribValue = token->value();
		element->set_attribute(attribName, attribValue);
		token = read_token();
	}
	if(!token) throw std::exception();

	//check if this tag is unpaired and doesn't contain slash
	if(m_unpaired_tags.find(ident_token->value()) != m_unpaired_tags.end())
		return element;

	switch(token->type())
	{
	case HTMLT_RBRACKET:
		{
			// This element has sub-elements, so parse
			// them recursively and add them to the
			// current element. 
			std::list<HTMLElement_Ptr> children =
				parse_elements();
			for(std::list<HTMLElement_Ptr>::
				const_iterator it=children.begin(),
				iend=children.end(); it!=iend; ++it)
			{
				element->add_child(*it);
			}
			// Read the element closing tag.
			read_checked_token(HTMLT_LSLASH);
			token = read_checked_token(HTMLT_IDENT);
			if(token->value() != element->name()) throw
				std::exception();
			read_checked_token(HTMLT_RBRACKET);
			break;
		}
	case HTMLT_RSLASH:
		{
			// The element is complete, so just break
			// and return it.
			break;
		}
	default:
		{
			throw std::exception();
		}
	}
	return element;
}
void HTMLParser::check_token_and_type(const HTMLToken_Ptr& token,	HTMLTokenType expectedType)
{
	if(!token)
	{
		throw std::exception();
	}
	if(token->type() != expectedType)
	{
		throw std::exception();
	}
}
HTMLToken_Ptr HTMLParser::read_checked_token(
	HTMLTokenType expectedType)
{
	HTMLToken_Ptr token = read_token();
	check_token_and_type(token, expectedType);
	return token;
}
HTMLToken_Ptr HTMLParser::read_token()
{
	if(m_lookahead.empty())
	{
		return m_lexer->next_token();
	}
	else
	{
		HTMLToken_Ptr token = m_lookahead.front();
		m_lookahead.pop_front();
		return token;
	}
}