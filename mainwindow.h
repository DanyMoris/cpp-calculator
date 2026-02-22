#pragma once

#include <QMainWindow>
#include <QString>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Operation {
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Calculator calculator_;
    QString input_number_;
    Number active_number_;
    Operation current_operation_;


    double memory_number_;
    bool is_memory_set_;


    void SetText(const QString& text);
    void AddText(const QString& suffix);
    void SetOperation(Operation op);

    QString NormalizeNumber(const QString &text);
    QString RemoveTrailingZeroes(const QString &text);
    QString OpToString(Operation op);
};
