#include "Web_Request.h"

WebResponse Web_Request::Download_URL_Text(std::string& url)
{
    WebResponse webResponse;

    try
    {

        std::ostringstream web_request_str;
        curlpp::Easy web_request_object;

        web_request_object.setOpt(new curlpp::options::Url(url));
        web_request_object.setOpt(new curlpp::options::Verbose(false));
        web_request_object.setOpt(new curlpp::options::SslVerifyHost(false));
        web_request_object.setOpt(new curlpp::options::SslVerifyPeer(false));

        // std::list<std::string> header;
        // header.push_back(std::string("User-Agent: {Custom User Agent Goes Here}"));
        // web_request_object.setOpt(new curlpp::options::HttpHeader(header));
        web_request_object.setOpt(new curlpp::options::HttpGet(true));
        web_request_object.setOpt(new curlpp::options::FollowLocation(true));
        web_request_object.setOpt(new curlpp::options::ConnectTimeout(10));
        web_request_object.setOpt(cURLpp::Options::WriteStream(&web_request_str));
        web_request_object.perform();
        webResponse.Response = web_request_str.str();
        webResponse.StatusCode = curlpp::infos::ResponseCode::get(web_request_object);
    }

    catch (curlpp::RuntimeError& e)
    {
        std::string error_msg = e.what();
        std::cout << e.what() << std::endl;
    }

    catch (curlpp::LogicError& e)
    {
        std::string error_msg = e.what();
        std::cout << e.what() << std::endl;
    }

    return webResponse;
}
