#include <cpr/cpr.h>
#include <chrono>
#include "workWithCout.h"
#include <thread>
#include <QProgressBar>

bool makeSupportAppeal(const std::string& goldenKey, std::unordered_set<std::string> idFunpayClear, const std::string& phpSessId, QProgressBar* progressBar) {
    cpr::Response rName = cpr::Get(cpr::Url{ "https://funpay.com" }, cpr::Header{ {"Cookie", goldenKey} });

    int attemps = 0;
    while (rName.status_code != 200 && attemps < 3) {
        attemps++;
        rName = cpr::Get(cpr::Url{ "https://funpay.com" }, cpr::Header{ {"Cookie", goldenKey} });
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    if (rName.status_code != 200) {
        throw std::runtime_error("Не смог получить никнейм фанпея перед отправкой в поддержку");
    }

    progressBar->setValue(35);

    std::string resName = rName.text;
    size_t startName = resName.find("<div class=\"user-link-name\">");
    size_t finishName = resName.find("</div>", startName);

    if (startName == std::string::npos || finishName == std::string::npos) throw std::runtime_error("Страница для получения никнейма фанпей не загрузились");

    startName += 28;

    progressBar->setValue(45);

    std::string nicknameFunpay = resName.substr(startName, finishName - startName);

    std::string requestBody = "<p>1)</p>";

    for (const auto& it : idFunpayClear) {
        requestBody += "<p>";
        requestBody += it;
        requestBody += "</p>";
    }

    progressBar->setValue(60);

    std::string fullCookie = goldenKey + "; " + phpSessId;
    
    cpr::Response rToken = cpr::Get(cpr::Url{ "https://support.funpay.com/tickets/new/1" }, cpr::Header{ {"Cookie", fullCookie} });
    
    attemps = 0;
    while (rToken.status_code != 200 && attemps < 3) {
        attemps++;
        rToken = cpr::Get(cpr::Url{ "https://support.funpay.com/tickets/new/1" }, cpr::Header{ {"Cookie", fullCookie} });
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    if (rToken.status_code != 200) {
        throw std::runtime_error("Не смог получить токен запроса перед отправкой в поддержку");
    }

    std::string resToken = rToken.text;
    size_t startToken = resToken.find("data-controller=\"csrf-protection\" value=\"");
    size_t finishToken = resToken.find("\" />", startToken);

    if (startToken == std::string::npos || finishToken == std::string::npos) throw std::runtime_error("Страница для получения токена запроса не загрузилась");

    startToken += 41;

    std::string tokenRequest = resToken.substr(startToken, finishToken - startToken);

    progressBar->setValue(80);

    cpr::Response finalResponse = cpr::Post(
        cpr::Url{ "https://support.funpay.com/tickets/create/1" }, 
        cpr::Header{
        {"Cookie", fullCookie},
        {"Content-Type", "application/x-www-form-urlencoded"},
        {"User-Agent", "Mozilla/5.0"},
        {"Referer", "https://support.funpay.com/tickets/create/1"}
        },
        cpr::Payload{
        {"ticket[fields][1]", nicknameFunpay},
        {"ticket[fields][2]", *idFunpayClear.begin()},
        {"ticket[fields][3]", "2"},
        {"ticket[fields][5]", "201"},
        {"ticket[comment][body_html]", requestBody},
        {"ticket[comment][attachments]", ""},
        {"ticket[_token]", tokenRequest}
        });

    progressBar->setValue(100);

    if (finalResponse.status_code == 200) {
        logTxt("Успешно отправил лоты в поддержку");
        return true;
    }
    else {
        logTxt("Не смог отправить лоты в поддержку: " + finalResponse.text);
        return false;
    }
}
