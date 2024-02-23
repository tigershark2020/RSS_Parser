#pragma once
#include <string>
#include <vector>
#include "Web_Request.h"
#include <html/ParserDom.h>

struct RSS_Item
{
	std::string title;
	std::string description;
	std::string link;
	std::string guid;
	std::string pubDate;
	std::string category;
	std::string author;
};

class RSS_Parser
{
private:
	inline void ltrim(std::string& s);
	inline void rtrim(std::string& s);
	inline void trim(std::string& s);
public:
	RSS_Item Get_RSS_Item(tree<htmlcxx::HTML::Node> const& dom);
	std::vector<RSS_Item> XML_To_RSS_Items(std::string xml);
	std::vector<RSS_Item> Parse_XML_Feed(std::string rss_url);
};
