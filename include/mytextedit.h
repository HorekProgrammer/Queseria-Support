#pragma once
#include <QTextEdit>
#include <QFocusEvent>

class MyTextEdit : public QTextEdit {
    Q_OBJECT
public:
    using QTextEdit::QTextEdit;
signals:
    void editingFinished();
protected:
    void focusOutEvent(QFocusEvent* e) override {
        emit editingFinished();
        QTextEdit::focusOutEvent(e);
    }
};