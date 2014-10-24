#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "Receiver.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSettings_triggered();
    void on_actionExit_triggered();
    void slotSetSettings( const Receiver &receiver );
    void slotReceivedData( const QByteArray &data );

private:
    void runReceiver();

private:
    Ui::MainWindow *ui;
    Receiver *m_receiver;
    QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H
