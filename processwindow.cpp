#include "processwindow.h"
#include "parseFunpay.h"
#include "deleteExcessId.h"
#include "supportAppeal.h"
#include "workWithCout.h"
#include <string>

ProcessWindow::ProcessWindow(QWidget *parent, const std::string& goldenKey, const std::unordered_set<std::string>& dataSkipId, const std::string& phpSessId) : QDialog(parent),
    goldenKey(goldenKey),
    dataSkipId(dataSkipId),
    phpSessId(phpSessId) {
    setWindowTitle("Выполнение...");
    setFixedSize(300, 100);

    QVBoxLayout *layout = new QVBoxLayout(this);

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100); // бесконечный индикатор
    progressBar->setTextVisible(false);

    layout->addWidget(progressBar);
    setLayout(layout);
}

bool ProcessWindow::startWork() {
    try {
        std::unordered_set<std::string> idFunpayRaw = parseOrdersFunpay(goldenKey);

        progressBar->setValue(10);

        std::unordered_set<std::string> idFunpayClear = removeExcessId(idFunpayRaw, dataSkipId);

        progressBar->setValue(20);

        if (makeSupportAppeal(goldenKey, idFunpayClear, phpSessId, progressBar)) return true;
        else return false;
    }
    catch (const std::exception& errorMessage) {
        logTxt("Произошла ошибка при попытке отправления лотов в поддержку: " + std::string(errorMessage.what()));
    }
    catch (...) {
        logTxt("Произошла неизвестная ошибка при попытке отправления лотов в поддержку");
    }
    return false;
}
