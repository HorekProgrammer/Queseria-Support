#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QKeyEvent>
#include <QMainWindow>
#include "settingwindow.h"
#include <unordered_set>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void setGoldenKey(const std::string& cookiePure);
    std::string getGoldenKey() const;
    void setPhpSess(const std::string& sessIdPure);
    std::string getPhpSessid() const;
    bool settingReady = false;
    void setSettingFinished(bool ready);
    std::unordered_set<std::string> dataSkipId;
    bool parseSkipId(std::string strOffers);

private slots:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    settingWindow* settingWin;
    std::string golden_key;
    std::string phpSessId;
};

#endif
