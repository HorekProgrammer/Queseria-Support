#ifndef PROCESSWINDOW_H
#define PROCESSWINDOW_H
#include <QDialog>
#include <QProgressBar>
#include <QVBoxLayout>
#include <string>

class ProcessWindow : public QDialog {
    Q_OBJECT
public:
    explicit ProcessWindow(QWidget *parent,
                           const std::string &goldenKey,
                           const std::unordered_set<std::string> &dataSkipId,
                           const std::string &phpSessId);
    bool startWork();

private:
    QProgressBar *progressBar;
    std::string goldenKey;
    std::unordered_set<std::string> dataSkipId;
    std::string phpSessId;
};

#endif
