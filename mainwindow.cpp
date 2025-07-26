#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFontDatabase>
#include <QApplication>
#include <QKeyEvent>
#include <QDesktopServices>
#include "settingwindow.h"
#include "workWithCout.h"
#include "processwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->queseriaSupportLabel->setText("Queseria Support");
    int id = QFontDatabase::addApplicationFont(":/fonts/Unbounded-Black.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    ui->queseriaSupportLabel->setFont(font);
    ui->queseriaSupportLabel->setStyleSheet("color: black; font-size: 55px;");
    ui->centralwidget->setStyleSheet("background-color: white;");
    ui->settingButton->setFocusPolicy(Qt::NoFocus);
    ui->startButton->setFocusPolicy(Qt::NoFocus);
    ui->githubButton->setFocusPolicy(Qt::NoFocus);
    ui->telegramButton->setFocusPolicy(Qt::NoFocus);
    ui->startButton->setFont(font);
    ui->settingButton->setFont(font);
    ui->githubButton->setFont(font);
    ui->telegramButton->setFont(font);
    setWindowTitle("Queseria Support");
    ui->settingButton->setText("Настроить");
    ui->startButton->setText("Запустить");
    ui->githubButton->setText("гитхаб");
    ui->telegramButton->setText("тг канал");
    ui->startButton->setStyleSheet("QPushButton {"
                                   "background-color: red;"
                                   "color: white;"
                                   "font-size: 38px;"
                                   "border: 1px solid black;"
                                   "border-radius: 0px"
                                   "}"
                                   "QPushButton:hover {"
                                   "background-color: darkred;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "background-color: #a00000;"
                                   "}");
    ui->settingButton->setStyleSheet("QPushButton {"
                                     "background-color: red;"
                                     "color: white;"
                                     "font-size: 38px;"
                                     "border: 1px solid black;"
                                     "border-radius: 0px;"
                                     "}"
                                     "QPushButton:hover {"
                                     "background-color: darkred;"
                                     "}"
                                     "QPushButton:pressed {"
                                     "background-color: #a00000;"
                                     "}");
    ui->githubButton->setStyleSheet("QPushButton {"
                                    "background-color: black;"
                                    "color: white;"
                                    "font-size: 50px;"
                                    "border-radius: 20px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #2B2B2B;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: #3D3D3D;"
                                    "}");
    ui->telegramButton->setStyleSheet("QPushButton {"
                                      "background-color: black;"
                                      "color: white;"
                                      "font-size: 50px;"
                                      "border-radius: 20px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: #2B2B2B;"
                                      "}"
                                      "QPushButton:pressed {"
                                      "background-color: #3D3D3D;"
                                      "}");
    ui->needSettingLabel->setStyleSheet("QLabel {"
                                        "color: red;"
                                        "font-size: 20px;"
                                        "}");
    QIcon iconGithub(":/logo/github.png");
    ui->githubButton->setIcon(iconGithub);
    ui->githubButton->setIconSize(QSize(40,40));
    QIcon iconTelegram(":/logo/telegram.png");
    ui->telegramButton->setIcon(iconTelegram);
    ui->telegramButton->setIconSize(QSize(40,40));

    connect(ui->githubButton, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl{"https://github.com/HorekProgrammer/Queseria-Support"});
    });

    connect(ui->telegramButton, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl{"https://t.me/queseriaSoft"});
    });

    connect(ui->settingButton, &QPushButton::clicked, this, [=](){
        settingWin = new settingWindow(this, *this);
        settingWin->setAttribute(Qt::WA_AttributeCount);
        settingWin->show();
    });

    connect(ui->startButton, &QPushButton::clicked, this, [=]() {
        if (settingReady) {
            ProcessWindow processWin(this, golden_key, dataSkipId, phpSessId);
            processWin.show();
            QApplication::processEvents();
            if (processWin.startWork()) {
                ui->startButton->setStyleSheet("QPushButton {"
                                               "background-color: green;"
                                               "color: white;"
                                               "font-size: 38px;"
                                               "border: 1px solid black;"
                                               "border-radius: 0px"
                                               "}"
                                               "QPushButton:hover {"
                                               "background-color: #3e6a1c;"
                                               "}"
                                               "QPushButton:pressed {"
                                               "background-color: #2a6100;"
                                               "}");
            }
            else {
                ui->startButton->setStyleSheet("QPushButton {"
                                               "background-color: red;"
                                               "color: white;"
                                               "font-size: 38px;"
                                               "border: 1px solid black;"
                                               "border-radius: 0px"
                                               "}"
                                               "QPushButton:hover {"
                                               "background-color: darkred;"
                                               "}"
                                               "QPushButton:pressed {"
                                               "background-color: #a00000;"
                                               "}");
            }
            processWin.close();
        }
        else {
            ui->needSettingLabel->setText("Вначале необходимо настроить");
        }
        });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        // Включаем фокус у кнопок при первом Tab
        ui->settingButton->setFocusPolicy(Qt::StrongFocus);
        ui->startButton->setFocusPolicy(Qt::StrongFocus);
        ui->telegramButton->setFocusPolicy(Qt::StrongFocus);
        ui->githubButton->setFocusPolicy(Qt::StrongFocus);

        // Передаём управление стандартной обработке
        QMainWindow::keyPressEvent(event);
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::setGoldenKey(const std::string& cookie) {
    golden_key = cookie;
}

std::string MainWindow::getGoldenKey() const {
    return golden_key;
}

void MainWindow::setSettingFinished(bool ready) {
    if (ready) {
        ui->settingButton->setStyleSheet("QPushButton {"
                                         "background-color: green;"
                                         "color: white;"
                                         "font-size: 38px;"
                                         "border: 1px solid black;"
                                         "border-radius: 0px"
                                         "}"
                                         "QPushButton:hover {"
                                         "background-color: #3e6a1c;"
                                         "}"
                                         "QPushButton:pressed {"
                                         "background-color: #2a6100;"
                                         "}");
        settingReady = true;
        ui->needSettingLabel->setText("");
    }
    else {
        ui->settingButton->setStyleSheet("QPushButton {"
                                         "background-color: red;"
                                         "color: white;"
                                         "font-size: 38px;"
                                         "border: 1px solid black;"
                                         "border-radius: 0px"
                                         "}"
                                         "QPushButton:hover {"
                                         "background-color: darkred;"
                                         "}"
                                         "QPushButton:pressed {"
                                         "background-color: #a00000;"
                                         "}");
        ui->startButton->setStyleSheet("QPushButton {"
                                         "background-color: red;"
                                         "color: white;"
                                         "font-size: 38px;"
                                         "border: 1px solid black;"
                                         "border-radius: 0px"
                                         "}"
                                         "QPushButton:hover {"
                                         "background-color: darkred;"
                                         "}"
                                         "QPushButton:pressed {"
                                         "background-color: #a00000;"
            "}");
        settingReady = false;
    }
}

bool MainWindow::parseSkipId(std::string strOffers) {
    strOffers += " ";
    try {
        dataSkipId.clear();
        size_t startPos = 0;
        size_t finishPos = strOffers.find(" ");
        while (startPos != std::string::npos && finishPos != std::string::npos) {
            std::string idSkip = strOffers.substr(startPos, finishPos - startPos);
            if (idSkip[0] != '#') {
                idSkip.insert(0, 1, '#');
            }
            dataSkipId.insert(idSkip);
            
            startPos = finishPos + 1;
            finishPos = strOffers.find(" ", startPos);
        }
        return true;
    }
    catch (const std::exception& errorMessage) {
        logTxt("Ошибка при парсинге айди офферов, которые надо пропустить " + std::string(errorMessage.what()));
        return false;
    }
    catch (...) {
        logTxt("При парсинге айди офферов произошла неизвестная ошибка");
        return false;
    }
}

void MainWindow::setPhpSess(const std::string& sessIdPure) {
    phpSessId = sessIdPure;
}

std::string MainWindow::getPhpSessid() const {
    return phpSessId;
}
