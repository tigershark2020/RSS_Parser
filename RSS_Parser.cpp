#include "RSS_Parser.h"

inline void RSS_Parser::ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
inline void RSS_Parser::rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends
inline void RSS_Parser::trim(std::string& s) {
	rtrim(s);
	ltrim(s);
}

RSS_Item RSS_Parser::Get_RSS_Item(tree<htmlcxx::HTML::Node> const& dom)
{
	RSS_Item rss_item;

	tree<htmlcxx::HTML::Node>::iterator it = dom.begin();

	for (; it != dom.end(); ++it)
	{
		if (it->isTag() && it->text() == "<description>")
		{
			++it;
			rss_item.description = it->text();
		}

		if (it->isTag() && it->text().find("<guid") != std::string::npos)
		{
			++it;
			rss_item.guid = it->text();
		}

		if (it->isTag() && it->text() == "<link>")
		{
			++it;
			rss_item.link = it->text();
		}

		if (it->isTag() && it->text() == "<pubDate>")
		{
			++it;
			rss_item.pubDate = it->text();
		}

		if (it->isTag() && it->text() == "<title>")
		{
			++it;
			rss_item.title = it->text();
			trim(rss_item.title);
		}

		if (it->isTag() && it->text() == "<dc:creator>")
		{
			++it;
			rss_item.author = it->text();
		}

		if (it->isTag() && it->text() == "<category>")
		{
			++it;
			rss_item.category = it->text();
		}

	}
	// cout << it->closingText();

	return rss_item;
}

std::vector<RSS_Item> RSS_Parser::XML_To_RSS_Items(std::string xml)
{
	std::vector<RSS_Item> rss_items;

	htmlcxx::HTML::ParserDom parser;
	tree<htmlcxx::HTML::Node> dom = parser.parseTree(xml);

	tree<htmlcxx::HTML::Node>::iterator it = dom.begin();
	tree<htmlcxx::HTML::Node>::iterator end = dom.end();


	for (; it != end; ++it)
	{
		// std::cout << dom.number_of_children(it) << std::endl;

		if (it->isTag() && it->text() == "<item>")
		{
			RSS_Item rss_item = Get_RSS_Item(it);
			rss_items.push_back(rss_item);
		}


		/*
		if ((!it->isTag()) && (!it->isComment()))
		{
			std::cout << it->text() << std::endl;
		}
		*/
	}

	return rss_items;
}

std::vector<RSS_Item> RSS_Parser::Parse_XML_Feed(std::string rss_url)
{
	std::vector<RSS_Item> rss_items;

	Web_Request web_request;
	WebResponse web_response = web_request.Download_URL_Text(rss_url);

	if (web_response.StatusCode == 200)
	{
		rss_items = XML_To_RSS_Items(web_response.Response);
	}

	return rss_items;
}
