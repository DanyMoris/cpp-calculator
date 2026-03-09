#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->cmb_controller, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index) {
                controller_callback_(static_cast<ControllerType>(index));
            });

    QObject::connect(ui->tb_zero, &QPushButton::clicked, [this] {
        digit_key_callback_(0);
    });
    QObject::connect(ui->tb_one, &QPushButton::clicked, [this] {
        digit_key_callback_(1);
    });
    QObject::connect(ui->tb_two, &QPushButton::clicked, [this] {
        digit_key_callback_(2);
    });
    QObject::connect(ui->tb_three, &QPushButton::clicked, [this] {
        digit_key_callback_(3);
    });
    QObject::connect(ui->tb_four, &QPushButton::clicked, [this] {
        digit_key_callback_(4);
    });
    QObject::connect(ui->tb_five, &QPushButton::clicked, [this] {
        digit_key_callback_(5);
    });
    QObject::connect(ui->tb_six, &QPushButton::clicked, [this] {
        digit_key_callback_(6);
    });
    QObject::connect(ui->tb_seven, &QPushButton::clicked, [this] {
        digit_key_callback_(7);
    });
    QObject::connect(ui->tb_eight, &QPushButton::clicked, [this] {
        digit_key_callback_(8);
    });
    QObject::connect(ui->tb_nine, &QPushButton::clicked, [this] {
        digit_key_callback_(9);
    });

    QObject::connect(ui->tb_add, &QPushButton::clicked, [this] {
        process_operation_key_callback_(Operation::ADDITION);
    });
    QObject::connect(ui->tb_substract, &QPushButton::clicked, [this] {
        process_operation_key_callback_(Operation::SUBTRACTION);
    });
    QObject::connect(ui->tb_multiplicate, &QPushButton::clicked, [this] {
        process_operation_key_callback_(Operation::MULTIPLICATION);
    });
    QObject::connect(ui->tb_divide, &QPushButton::clicked, [this] {
        process_operation_key_callback_(Operation::DIVISION);
    });
    QObject::connect(ui->tb_power, &QPushButton::clicked, [this] {
        process_operation_key_callback_(Operation::POWER);
    });

    QObject::connect(ui->tb_reset, &QPushButton::clicked, [this] {
        process_control_key_callback_(ControlKey::CLEAR);
    });
    QObject::connect(ui->tb_ms, &QPushButton::clicked, [this] {
        process_control_key_callback_(ControlKey::MEM_SAVE);
    });
    QObject::connect(ui->tn_mr, &QPushButton::clicked, [this] {
        process_control_key_callback_(ControlKey::MEM_LOAD);
    });
    QObject::connect(ui->tb_mc, &QPushButton::clicked, [this] {
        process_control_key_callback_(ControlKey::MEM_CLEAR);
    });
    QObject::connect(ui->tb_negate, &QPushButton::clicked, [this] {
        process_control_key_callback_(ControlKey::PLUS_MINUS);
    });
    QObject::connect(ui->tb_backspace, &QPushButton::clicked, [this] {
        process_control_key_callback_(ControlKey::BACKSPACE);
    });
    QObject::connect(ui->tb_equal, &QPushButton::clicked, [this] {
        process_control_key_callback_(ControlKey::EQUALS);
    });
    QObject::connect(ui->tb_extra, &QPushButton::clicked, [this] {
        process_control_key_callback_(ControlKey::EXTRA_KEY);
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setText(QString::fromStdString(text));
    ui->l_result->setStyleSheet("");
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setText(QString::fromStdString(text));
    ui->l_result->setStyleSheet("color: red;");
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key) {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->show();
    } else {
        ui->tb_extra->hide();
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_key_callback_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    process_operation_key_callback_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    process_control_key_callback_ = cb;
}
