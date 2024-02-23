#pragma once
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include <sstream>

struct WebResponse
{
    std::string Response;
    int StatusCode;
};

class Web_Request
{
public:
    WebResponse Download_URL_Text(std::string& url);
};
