#include "audiencescreen.h"
#include "ui_audiencescreen.h"
#include <iostream>
#include <QCloseEvent>
using namespace std;

AudienceScreen::AudienceScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    toggleFullscreenSC = new QShortcut(QKeySequence(QKeySequence::Find),this);
    connect(toggleFullscreenSC, SIGNAL(activated()), this, SLOT(enterFullScreen()));
    exitFullScreenSC = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    connect(ui->fullScreenPushButton,SIGNAL(clicked()),this,SLOT(enterFullScreen()));

    this->setFocusPolicy(Qt::ClickFocus);
}

AudienceScreen::~AudienceScreen()
{
    delete ui;
}

void AudienceScreen::updateTimer(const Timer *n)
{
    int currentSeconds = n->getCurrentSeconds();

    int min = currentSeconds / 60;
    QString minString = QString::number(min);

    int sec = currentSeconds % 60;
    QString secString = QString::number(sec);
    if(sec < 10)
        secString.prepend("0");

    QString text = minString + ":" + secString;
    ui->lcdNumber->display(text);
    ui->lcdNumber->setStyleSheet(n->styleSheet());
}

void AudienceScreen::enterFullScreen()
{
    disconnect(toggleFullscreenSC,SIGNAL(activated()),this,SLOT(enterFullScreen()));
    connect(toggleFullscreenSC,SIGNAL(activated()),this,SLOT(exitFullScreen()));
    connect(exitFullScreenSC,SIGNAL(activated()),this,SLOT(exitFullScreen()));
    this->showFullScreen();
    ui->fullScreenPushButton->hide();
}

void AudienceScreen::exitFullScreen()
{
    disconnect(toggleFullscreenSC,SIGNAL(activated()),this,SLOT(exitFullScreen()));
    connect(toggleFullscreenSC,SIGNAL(activated()),this,SLOT(enterFullScreen()));
    exitFullScreenSC->disconnect();
    this->showNormal();
    ui->fullScreenPushButton->show();
}

void AudienceScreen::closeEvent(QCloseEvent *event)
 {
    event->accept();
    emit closed(true);
 }
