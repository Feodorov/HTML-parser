#include <vector>
#include <log4cxx/log4cxx.h>
#include <log4cxx/XML/domconfigurator.h>
#include <locale>
#include "HTMLLexer.h"
#include "HTMLParser.h"
#include "HTMLElement.h"
#include "DataStream.h"

int main(int argc, char **argv) 
{
	log4cxx::xml::DOMConfigurator::configure("log4cxx.xml");
	log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("logger");	
	LOG4CXX_INFO(logger, "Init");
	
	try{
		DataStream_Ptr data_source(new DataStream());
		HTMLLexer_Ptr lexer(new HTMLLexer(data_source));
		HTMLParser parser(lexer);
		HTMLElement_CPtr root = parser.parse();
		std::vector<HTMLElement_CPtr> children = root->find_in_all_subchildren(std::string("data"), root);
		for(std::vector<HTMLElement_CPtr>::const_iterator it = children.begin(); it != children.end(); ++it)
		{
			std::string answer = (*it)->attribute(std::string("data"));
			LOG4CXX_INFO(logger, answer);
			data_source->write(answer.c_str(), answer.length());
		}
		return 0;
	}
	catch (std::exception)
	{
		return -1;
	}
}