#pragma once
#include <unordered_set>
#include <string>
#include <QProgressBar>

bool makeSupportAppeal(const std::string& goldenKey, std::unordered_set<std::string> idFunpayClear, const std::string& phpSessId, QProgressBar* progressBar);
