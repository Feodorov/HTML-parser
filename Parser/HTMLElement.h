#ifndef HTML_ELEMENT_H_
#define HTML_ELEMENT_H_

#include <string>
#include <vector>
#include <map>
#include <log4cxx/log4cxx.h>
#include <log4cxx/rollingfileappender.h>
#include <log4cxx/patternlayout.h>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<class HTMLElement> HTMLElement_Ptr;
typedef boost::shared_ptr<const class HTMLElement> HTMLElement_CPtr;

class HTMLElement
{
public:
	HTMLElement(const std::string& name);
	void add_child(const HTMLElement_Ptr& child);
	const std::string& attribute(const std::string& name) const;
	std::vector<HTMLElement_CPtr> find_in_all_subchildren(std::string & name, HTMLElement_CPtr start_node) const;
	const std::string& name() const;
	void set_attribute(const std::string& name,	const std::string& value);
private:
	std::string m_name;
	std::map<std::string, std::string> m_attributes;
	std::vector<HTMLElement_CPtr> m_children;
    log4cxx::LoggerPtr logger;
};

#endif //HTML_ELEMENT_H_