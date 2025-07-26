#include "isItCorrect.h"
#include <string>

bool checkHtmlDefineCookie(const std::string& html) {
    if (html.find("user-link-name") != std::string::npos) {
        return true;
    }
    else {
        return false;
    }
}