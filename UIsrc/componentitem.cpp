#include "componentitem.h"

ComponentItem::ComponentItem(QWidget *parent)
    : QWidget{parent}
{}

void ComponentItem::mousePressEvent(QMouseEvent *event)
{

}

void ComponentItem::setTitle(const QString title)
{
    this->title=title;
}

void ComponentItem::setPicmap(const QPixmap pic)
{
    this->pic=pic;
}
