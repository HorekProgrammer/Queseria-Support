#include "classOrderInfo.h"
#include "workWithCout.h"

orderInfoClass::orderInfoClass(const std::string& partHtml) {
    isValid_ = setStatus(partHtml) && setOrderId(partHtml) && setTime(partHtml);
}

std::string orderInfoClass::getStatus() const {
    return status_;
}

std::string orderInfoClass::getOrderId() const {
    return orderId_;
}

std::string orderInfoClass::getTime() const {
    return time_;
}

bool orderInfoClass::getIsValid() const {
    return isValid_;
}

bool orderInfoClass::setStatus(const std::string& partHtml) {
    size_t startPos = partHtml.find("<div class=\"tc-status text-primary\">");
    if (startPos == std::string::npos) {
        logTxt("Ошибка std::string::npos в setStatus");
        return false;
    }

    startPos += 36;
    size_t finishPos = partHtml.find("</div>");

    if (finishPos == std::string::npos) {
        logTxt("Ошибка std::string::npos в setStatus");
        return false;
    }

    status_ = partHtml.substr(startPos, finishPos - startPos);
    return true;
}

bool orderInfoClass::setOrderId(const std::string& partHtml) {
    size_t startPos = partHtml.find("<div class=\"tc-order\">");
    if (startPos == std::string::npos) {
        logTxt("Ошибка std::string::npos в setOrderId");
        return false;
    }

    startPos += 22;
    size_t finishPos = partHtml.find("</div>", startPos);

    if (finishPos == std::string::npos) {
        logTxt("Ошибка std::string::npos в setOrderId");
        return false;
    }

    orderId_ = partHtml.substr(startPos, finishPos - startPos);
    return true;
}

bool orderInfoClass::setTime(const std::string& partHtml) {
    size_t startPos = partHtml.find("<div class=\"tc-date-left\">");
    if (startPos == std::string::npos) {
        logTxt("Ошибка std::string::npos в setTime");
        return false;
    }

    startPos += 26;
    size_t finishPos = partHtml.find("</div>", startPos);

    if (finishPos == std::string::npos) {
        logTxt("Ошибка std::string::npos в setTime");
        return false;
    }

    time_ = partHtml.substr(startPos, finishPos - startPos);
    return true;
}