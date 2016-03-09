#ifndef MYGAZEQTWIDGET_H
#define MYGAZEQTWIDGET_H

#include <QWidget>
#include <myGazeAPI.h>

namespace Ui {
    class MyGazeQTWidget;
}

class MyGazeQTWidget : public QWidget {
    Q_OBJECT

public:
    explicit MyGazeQTWidget(QWidget *parent = 0);
    ~MyGazeQTWidget();


protected:
    void connectEyetracker();
    void calibrateEyetracker();
    void displayErrorMessageBox();

private slots:
    void on_quitButton_clicked();
    void on_connectButton_clicked();
    void on_startSessionButton_clicked();
    void on_settingsButton_clicked();


private:
    Ui::MyGazeQTWidget *ui;
    static int sampleCallbackFunction(SampleStruct);
    static int eventCallbackFunction(EventStruct);
    void numDisplayUpdater();
};

#endif // MYGAZEQTWIDGET_H
