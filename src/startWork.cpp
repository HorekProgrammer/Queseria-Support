#include "startWork.h"
#include "parseFunpay.h"
#include "deleteExcessId.h"
#include "supportAppeal.h"
#include "workWithCout.h"
#include <string>

bool startWork(std::string goldenKey, const std::unordered_set<std::string>& dataSkipId, const std::string& phpSessId) {
    try {
        std::unordered_set<std::string> idFunpayRaw = parseOrdersFunpay(goldenKey);

        std::unordered_set<std::string> idFunpayClear = removeExcessId(idFunpayRaw, dataSkipId);

        if (makeSupportAppeal(goldenKey, idFunpayClear, phpSessId, nullptr)) return true;
        else return false;
    }
    catch (const std::exception& errorMessage) {
        logTxt("Произошла ошибка при попытке отправления лотов в поддержку: " + std::string(errorMessage.what()));
    }
    catch (...) {
        logTxt("Произошла неизвестная ошибка при попытке отправления лотов в поддержку");
    }
}