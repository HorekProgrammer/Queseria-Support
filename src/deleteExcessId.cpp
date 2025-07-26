#include "deleteExcessId.h"

std::unordered_set<std::string> removeExcessId(const std::unordered_set<std::string>& funpayId, const std::unordered_set<std::string>& recurringId) {
    std::unordered_set<std::string> funpayIdClear;

    for (const auto& it : funpayId) {
        if (recurringId.find(it) == recurringId.end()) {
            funpayIdClear.insert(it);
        }
    }

    return funpayIdClear;
}