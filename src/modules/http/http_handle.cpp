#include "http_handle.h"

namespace wcdj 
{
	namespace http
	{

		size_t recv_proc(void *ptr, size_t size, size_t nmemb, std::string *p)
		{

			if (p == NULL)
				return 0;

			if (size * nmemb == 0)
				return 0;

			std::string temp((char*)ptr, size * nmemb);
			p->append(temp);
			return (size * nmemb);
		}

		int http_proc(const std::string &strUrl, 
				unsigned iTimeout, 
				std::map<std::string, std::string> &mapPostData, 
				std::string &strRecvBuf,
				int &iResult,
				std::string &strErrmsg,
				const std::string &strCookie)
		{

			int ret         =  0;
			char cerr[1024] =  {0};

			/* comment, gerryyang
			 * You are strongly advised to not allow this automatic behaviour, by calling curl_global_init(3) yourself properly
			 * �ٷ��Ƽ�ʹ��curl_global_init��curl_global_cleanup
			 * */
			static bool bInit = false;
			if (bInit == false)
			{
				bInit = true;
				curl_global_init(CURL_GLOBAL_ALL);  
			}

			CURL *curl = curl_easy_init();
			if (!curl) 
			{
				snprintf(cerr, sizeof(cerr), "%s:%d %s", __FILE__, __LINE__, "[curl]curl_easy_init error");
				strErrmsg = cerr;
				return -501;
			}

			struct curl_slist *headerlist =  NULL;
			headerlist                    =  curl_slist_append(headerlist, "Accept: */*");
			headerlist                    =  curl_slist_append(headerlist, "Pragma: no-cache");

			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
			if (!strCookie.empty())
				curl_easy_setopt(curl, CURLOPT_COOKIE, strCookie.c_str());

			curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
			if (mapPostData.size() != 0)
			{
				std::string strPostData;
				std::map<std::string, std::string>::iterator pIt = mapPostData.begin();
				for (;;)
				{
					strPostData += pIt->first;
					strPostData += "=";
					strPostData += pIt->second;
					if (++pIt == mapPostData.end())
						break;
					else
						strPostData += "&";

				}
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
			}

			curl_easy_setopt(curl,   CURLOPT_WRITEFUNCTION,   recv_proc);
			curl_easy_setopt(curl,   CURLOPT_WRITEDATA,       &strRecvBuf);

			/* comment, gerryyang
			 * In unix-like systems, CURLOPT_TIMEOUT might cause signals to be used unless CURLOPT_NOSIGNAL is set.
			 * CURLOPT_NOSIGNAL, Pass a long. If it is 1, libcurl will not use any functions that install signal handlers or any functions that cause signals to be sent to the process. This option is mainly here to allow multi-threaded unix applications to still set/use all timeout options etc, without risking getting signals. The default value for this parameter is 0. (Added in 7.10) 
			 * ע��signal��libcurl�����̰߳�ȫ��, ����Ҫ�������е��źŴ���
			 * */
			curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

			curl_easy_setopt(curl,   CURLOPT_CONNECTTIMEOUT,   iTimeout);
			curl_easy_setopt(curl,   CURLOPT_TIMEOUT,          iTimeout);


			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK) 
			{
				ret = -502;

				sprintf(cerr, "%s:%d [curl]%s(%d)", __FILE__, __LINE__, curl_easy_strerror(res), res);
				strErrmsg = cerr;
				switch (res)
				{
				case CURLE_URL_MALFORMAT:
					;
				case CURLE_COULDNT_RESOLVE_HOST:
					;
				case CURLE_COULDNT_CONNECT: 
					iResult = -2;  
					break;
				default:
					break;
				}
			}
			else
			{
				long iRet;
				res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &iRet);
				if (res != CURLE_OK) 
				{
					ret = -503;
					sprintf(cerr, "%s:%d [curl]%s(%d)", __FILE__, __LINE__, curl_easy_strerror(res), res);
					strErrmsg = cerr;
				}
				else if (iRet != 200)// HTTP OK
				{
					ret = -504;
					sprintf(cerr, "%s:%d [curl]Http Response FAIL(%ld)", __FILE__, __LINE__, iRet);
					strErrmsg = cerr;
				}
			}

			curl_slist_free_all(headerlist);

			/* comment, gerryyang
			 * You are strongly advised to not allow this automatic behaviour, by calling curl_global_init(3) yourself properly
			 * �ٷ��Ƽ�ʹ��curl_global_init��curl_global_cleanup
			 * */
			curl_easy_cleanup(curl);

			return ret;
		}
	}
}

