#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QFontDatabase>
#include "checkCookie.h"
#include "mainwindow.h"
#include <QMouseEvent>

settingWindow::settingWindow(QWidget* parent, MainWindow& mainData)
    : QDialog(parent), ui(new Ui::settingWindow), mainRef(mainData)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    int id = QFontDatabase::addApplicationFont(":/fonts/Unbounded-Black.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    setWindowTitle("Настройка");
    ui->cookieLabel->setText("Голден Кей:");
    ui->phpSessidLabel->setText("Сессион айди:");
    ui->cookieLabel->setFont(font);
    ui->exceptOrderLabel->setFont(font);
    ui->saveButton->setFont(font);
    ui->phpSessidLabel->setFont(font);
    ui->imageInformationLabel->setPixmap(QPixmap(":/logo/information.png"));

    ui->cookieLabel->setStyleSheet("QLabel {"
        "color: black;"
        "font-size: 30px;"
        "}");
    ui->cookieLineEdit->setStyleSheet("QLineEdit {"
        "color: white;"
        "background-color: #504f4f;"
        "border: 1px solid black;"
        "}");
    ui->exceptOrderLabel->setStyleSheet("QLabel {"
        "color: black;"
        "font-size: 30px;"
        "}");
    ui->exceptOrdersTextEdit->setStyleSheet("QTextEdit {"
        "background-color: #504f4f;"
        "color: white;"
        "border: 1px solid black;"
        "}");
    ui->changeCookieLabel->setStyleSheet("QLabel {"
        "color: red;"
        "}");
    ui->phpSessidLabel->setStyleSheet("QLabel {"
                                   "color: black;"
                                   "font-size: 30px;"
                                   "}");
    ui->phpSessLineEdit->setStyleSheet("QLineEdit {"
                                      "color: white;"
                                      "background-color: #504f4f;"
                                      "border: 1px solid black;"
                                      "}");

    ui->exceptOrderLabel->setText("Заказы для пропуска:");
    ui->saveButton->setText("Сохранить");
    int idMontserrat = QFontDatabase::addApplicationFont(":/fonts/Montserrat-SemiBold.ttf");
    QString familyMontserrat = QFontDatabase::applicationFontFamilies(idMontserrat).at(0);
    QFont fontMontserrat(familyMontserrat);
    ui->informationTextLabel->setFont(fontMontserrat);
    ui->informationTextLabel->setText("Заказы, которые софт не отправит в поддержку, указывать через пробел");
    ui->informationTextLabel->setStyleSheet("QLabel {"
        "color: black;"
        "font-size: 11px;"
        "}");
    ui->saveButton->setStyleSheet("QPushButton {"
        "color: white;"
        "background-color: black;"
        "font-size: 11px;"
        "}"
        "QPushButton:hover {"
        "background-color: #1f231f;"
        "}"
        "QPushButton:pressed {"
        "background-color: #474847;"
        "}");

    connect(ui->saveButton, &QPushButton::clicked, this, [=]() {
        QString userText = ui->cookieLineEdit->text();
        std::string goldenKey;
        std::string phpSessId = ui->phpSessLineEdit->text().toStdString();
        if (checkGoldenKey(userText.toStdString(), goldenKey) && checkPHPSessid(goldenKey, phpSessId)) {
            mainRef.setGoldenKey(goldenKey);
            mainRef.setPhpSess(phpSessId);
            ui->changeCookieLabel->setText("");
            mainRef.setSettingFinished(true);
            this->close();
        }
        else {
            mainRef.setSettingFinished(false);
            ui->cookieLineEdit->setStyleSheet("QLineEdit {"
                                              "background-color: red;"
                                              "color: white;"
                                              "}");
            ui->phpSessLineEdit->setStyleSheet("QLineEdit {"
                                               "background-color: red;"
                                               "color: white;"
                                               "}");
            ui->changeCookieLabel->setText("Куки неправильные");
        }
        });

    connect(ui->cookieLineEdit, &QLineEdit::textChanged, this, [=]() {
        editingCookieFinished = true;
        });

    connect(ui->exceptOrdersTextEdit, &MyTextEdit::editingFinished, this, [=]() {
        mainRef.parseSkipId(ui->exceptOrdersTextEdit->toPlainText().toStdString());
        });
}

settingWindow::~settingWindow()
{
    delete ui;
}

bool settingWindow::getFillCookie() const {
    return fillCookie;
}

void settingWindow::setFillCookie(bool isItFill) {
    fillCookie = isItFill;
}

void settingWindow::mousePressEvent(QMouseEvent* event) {
    QWidget::mousePressEvent(event);
    if (!ui->cookieLineEdit->geometry().contains(event->pos()) && editingCookieFinished) {
        ui->cookieLineEdit->clearFocus();
        emit ui->cookieLineEdit->editingFinished();
        editingCookieFinished = false;
    }
}
