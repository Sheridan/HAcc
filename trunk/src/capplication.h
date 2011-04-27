/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef CAPPLLICATION_H
#define CAPPLLICATION_H

#include <QPixmap>
#include <QByteArray>
#include <QApplication>

//! Класс приложения
class CApplication : public QApplication
{
    Q_OBJECT
public:
    int run();
    CApplication(int & argc, char ** argv);
    virtual ~CApplication();
    void refreshStyleSheets();

private:
    void setAuthor();
};
#endif
