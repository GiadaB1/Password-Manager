#ifndef CLICKABLETEXT_H
#define CLICKABLETEXT_H
#include <QApplication>
#include <QLabel>
#include <QMouseEvent>

class ClickableText : public QLabel
{
    Q_OBJECT

public:
    ClickableText(const QString &text, QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif