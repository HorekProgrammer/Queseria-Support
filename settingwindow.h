#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H
#include <QDialog>
#include <QTextEdit>

namespace Ui {
class settingWindow;
}

class MainWindow;

class settingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit settingWindow(QWidget *parent, MainWindow& mainData);
    ~settingWindow();
    bool getFillCookie() const;
    void setFillCookie(bool isItFill);
    bool editingCookieFinished = false;
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::settingWindow *ui;
    bool fillCookie = false;
    MainWindow& mainRef;
};

#endif // SETTINGWINDOW_H