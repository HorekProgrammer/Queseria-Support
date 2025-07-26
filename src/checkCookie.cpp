#include "checkCookie.h"
#include <cpr/cpr.h>
#include "isItCorrect.h"

bool checkGoldenKey(const std::string& rawCookie, std::string& cookie) {
	if (rawCookie.find("golden_key=") == std::string::npos) {
		cookie = "golden_key=" + rawCookie;
	}
	else cookie = rawCookie;
	cpr::Response response = cpr::Get(cpr::Url{ "https://funpay.com/" }, cpr::Header{ {"Cookie", cookie} });
	return checkHtmlDefineCookie(response.text);
}

bool checkPHPSessid(const std::string& goldenkey, std::string& phpSessId) {
    std::string cookie;
    if (phpSessId.find("PHPSESSID=") == std::string::npos) {
        phpSessId = "PHPSESSID=" + phpSessId;
    }

    cookie = goldenkey + "; " + phpSessId;

    auto r = cpr::Get(cpr::Url{ "https://support.funpay.com/tickets/new" }, cpr::Header{ {"Cookie", cookie}, {"User-Agent", "Mozilla/5.0"}, {"Referer", "https://funpay.com/"} });
    std::string res = r.text;
    if (res.find("ticket_select_form") != std::string::npos) return true;
    else return false;
}
