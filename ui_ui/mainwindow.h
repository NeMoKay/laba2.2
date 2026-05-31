#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onContainerChanged();
    void onOperationChanged();
    void onRun();

private:
    void setupOperationsTab();
    QString mainStyle();
    void updateOperations();

    template <typename T, template <typename> class Container>
    void executeStandard();

    template <typename T>
    void executeBit();

    QTabWidget *tabs;
    QWidget *tabOps;

    QGroupBox *groupSettings;
    QComboBox *comboDataType;
    QComboBox *comboContainer;
    QComboBox *comboOperation;

    QGroupBox *groupSeqA;
    QLineEdit *lineSeqA;

    QGroupBox *groupSeqB;
    QLineEdit *lineSeqB;

    QGroupBox *groupArgs;
    QLabel *labelValue;
    QLineEdit *lineValue;
    QLabel *labelIndex;
    QLineEdit *lineIndex;
    QLabel *labelStart;
    QLineEdit *lineStart;
    QLabel *labelEnd;
    QLineEdit *lineEnd;

    QPushButton *btnRun;

    QGroupBox *groupResult;
    QLabel *labelResultTitle;
    QTextEdit *textResult;
};

#endif