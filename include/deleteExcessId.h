#pragma once
#include <unordered_set>
#include <string>

std::unordered_set<std::string> removeExcessId(const std::unordered_set<std::string>& funpayId, const std::unordered_set<std::string>& recurringId);