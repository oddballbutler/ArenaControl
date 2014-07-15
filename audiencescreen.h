#ifndef AUDIENCESCREEN_H
#define AUDIENCESCREEN_H

#include <QWidget>
#include <QShortcut>
#include "timer.h"

namespace Ui {
    class Form;
}

class AudienceScreen : public QWidget
{
    Q_OBJECT
public:
    explicit AudienceScreen(QWidget *parent = 0);
    ~AudienceScreen();

protected:
void closeEvent(QCloseEvent *event);

signals:
void closed(bool);

public slots:
    void updateTimer(const Timer *n);
    void enterFullScreen();
    void exitFullScreen();

private:
    Ui::Form *ui;
    QShortcut *toggleFullscreenSC;
    QShortcut *exitFullScreenSC;

};

#endif // AUDIENCESCREEN_H
