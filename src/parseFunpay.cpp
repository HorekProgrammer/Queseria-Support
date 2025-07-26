#include "parseFunpay.h"
#include <cpr/cpr.h>
#include "workWithCout.h"
#include "classOrderInfo.h"
#include <chrono>

std::unordered_set<std::string> parseOrdersFunpay(const std::string& goldenKey) {
    cpr::Response r;
    r.status_code = 404;
    int attempts = 0;
    static std::unordered_set<std::string> ordersFunpay;

    while (r.status_code != 200 && attempts < 3) {
        attempts++;
        r = cpr::Get(cpr::Url{ "https://funpay.com/orders/trade" }, cpr::Header{ {"Cookie", goldenKey} });
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    if (r.status_code != 200) throw std::runtime_error("Не получилось сделать запрос к фанпею, проблема с айпи или интернетом");

    std::string response = r.text;

    size_t startOrderInfo = response.find("class=\"tc-item info\">");
    size_t finishOrderInfo = response.find("</a>", startOrderInfo);

    while (startOrderInfo != std::string::npos && finishOrderInfo != std::string::npos) {
        std::string orderInfo = response.substr(startOrderInfo, finishOrderInfo - startOrderInfo);
        orderInfoClass orderClass(orderInfo);

        if (orderClass.getIsValid()) {
            std::string time = orderClass.getTime();
            if (time.find("сек") == std::string::npos && time.find("мин") == std::string::npos && time.find("час") == std::string::npos) {
                ordersFunpay.insert(orderClass.getOrderId());
            }
        }
        else {
            throw std::runtime_error("Не получилось отпарсить айди заказов");
        }

        startOrderInfo = response.find("class=\"tc-item info\">", finishOrderInfo);
        finishOrderInfo = response.find("</a>", startOrderInfo);
    }

    return ordersFunpay;
}