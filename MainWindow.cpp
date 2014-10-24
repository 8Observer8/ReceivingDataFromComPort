#include <QDebug>
#include <QMessageBox>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SettingsDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize( this->size() );
    m_receiver = new Receiver;

    // Status Label
    m_statusLabel = new QLabel;
    m_statusLabel->setText( tr( "Select the COM-port" ) );
    ui->statusBar->addPermanentWidget( m_statusLabel, 1 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog dialog;
    dialog.setModal( true );
    connect( &dialog, SIGNAL( signalSetSettings( Receiver ) ),
             this, SLOT( slotSetSettings( Receiver ) ) );
    dialog.exec();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::runReceiver()
{
    try {
        m_receiver->run();
        connect( m_receiver, SIGNAL( signalReceivedData( QByteArray ) ),
                 this, SLOT( slotReceivedData( QByteArray ) ) );
        QString text = QString( "Port Name: %1, BaudRate: %2" ).
                arg( m_receiver->getPortName() ).arg( m_receiver->getBaudRate() );

        m_statusLabel->setText( text );
    } catch ( const PortError &e ) {
        QString message( e.what() );
        QMessageBox::information( this, tr( "Error" ), message );
        return;
    } catch( ... ) {
        QString message( "Error: unknown exception" );
        QMessageBox::information( this, tr( "Error" ), message );
        return;
    }
}

void MainWindow::slotSetSettings( const Receiver &receiver )
{
    delete m_receiver;

    m_receiver = new Receiver( receiver );

    runReceiver();
}

void MainWindow::slotReceivedData( const QByteArray &data )
{
    ui->textEdit->append( QString( data ) );
}
