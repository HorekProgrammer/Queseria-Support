#include <string>

bool checkGoldenKey(const std::string& rawCookie, std::string& cookie);

bool checkPHPSessid(const std::string& goldenkey, std::string& phpSessId);