#include <QLabel>
#include "ClickableText.h"
#include <iostream>
ClickableText::ClickableText(const QString &text, QWidget *parent) : QLabel(text, parent)
{
    setStyleSheet("QLabel { color : blue; }");
    setCursor(Qt::PointingHandCursor);
}

void ClickableText::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
}