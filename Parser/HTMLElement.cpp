#include <exception>
#include "HTMLElement.h"

HTMLElement::HTMLElement(const std::string& name)
: m_name(name)
{
    logger = log4cxx::Logger::getLogger("logger");
    LOG4CXX_INFO(logger, "[HTMLElement]: " << name.c_str() <<" created");
}
void HTMLElement::add_child(const HTMLElement_Ptr& child)
{
	m_children.push_back(child);
}

const std::string& HTMLElement::attribute(const std::string& name) const
{
	std::map<std::string, std::string>::const_iterator it = m_attributes.find(name);
	if(it != m_attributes.end()) return it->second;
	else throw std::exception();
}

std::vector<HTMLElement_CPtr> HTMLElement::find_in_all_subchildren(std::string & name, HTMLElement_CPtr start_node) const
{
	std::vector<HTMLElement_CPtr> result;
	
	if(name == start_node->name()) 
		result.push_back(start_node);

	for(std::vector<HTMLElement_CPtr> ::const_iterator it = start_node->m_children.begin(); it != start_node->m_children.end(); ++it)
	{		
			std::vector<HTMLElement_CPtr> sub_children = find_in_all_subchildren(name, *it);
			result.insert(result.end(), sub_children.begin(), sub_children.end());
	}
	return result;
}

const std::string& HTMLElement::name() const
{
	return m_name;
}
void HTMLElement::set_attribute(
							   const std::string& name,
							   const std::string& value)
{
	m_attributes[name] = value;
	if("data" == name)  LOG4CXX_INFO(logger, value.c_str());
}