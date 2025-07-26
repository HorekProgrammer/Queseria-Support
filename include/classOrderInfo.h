#pragma once
#include <string>

class orderInfoClass {
public:
    orderInfoClass(const std::string& partHtml);

    std::string getStatus() const;
    std::string getOrderId() const;
    std::string getTime() const;
    bool getIsValid() const;
private:
    bool setStatus(const std::string& partHtml);
    bool setOrderId(const std::string& partHtml);
    bool setTime(const std::string& partHtml);

    std::string status_;
    std::string orderId_;
    std::string time_;
    bool isValid_ = false;
};