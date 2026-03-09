#pragma once

#include "ui_mainwindow.h"
#include "calculator.h"
#include "enums.h"

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <functional>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb) {
        controller_callback_ = cb;
    }

private:

    Ui::MainWindow* ui;
    std::function<void(int key)> digit_key_callback_;
    std::function<void(Operation key)> process_operation_key_callback_;
    std::function<void(ControlKey key)> process_control_key_callback_;
    std::function<void(ControllerType controller)> controller_callback_;
};