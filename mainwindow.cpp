#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , current_operation_(Operation::NO_OPERATION)
    , memory_number_(0.0)
    , is_memory_set_(false)
{
    ui->setupUi(this);

    ui->l_memory->setText("");
    ui->l_formula->setText("");

    connect(ui->tb_zero, &QPushButton::clicked, this, [this](){ AddText("0"); });
    connect(ui->tb_one, &QPushButton::clicked, this, [this](){ AddText("1"); });
    connect(ui->tb_two, &QPushButton::clicked, this, [this](){ AddText("2"); });
    connect(ui->tb_three, &QPushButton::clicked, this, [this](){ AddText("3"); });
    connect(ui->tb_four, &QPushButton::clicked, this, [this](){ AddText("4"); });
    connect(ui->tb_five, &QPushButton::clicked, this, [this](){ AddText("5"); });
    connect(ui->tb_six, &QPushButton::clicked, this, [this](){ AddText("6"); });
    connect(ui->tb_seven, &QPushButton::clicked, this, [this](){ AddText("7"); });
    connect(ui->tb_eight, &QPushButton::clicked, this, [this](){ AddText("8"); });
    connect(ui->tb_nine, &QPushButton::clicked, this, [this](){ AddText("9"); });

    connect(ui->tb_comma, &QPushButton::clicked, this, [this](){
        if (!input_number_.contains('.')) {
            AddText(".");
        }
    });

    connect(ui->tb_negate, &QPushButton::clicked, this, [this](){
        if (input_number_.startsWith("-")) {
            SetText(input_number_.mid(1));
        } else {
            SetText("-" + input_number_);
        }
    });

    connect(ui->tb_backspace, &QPushButton::clicked, this, [this](){
        if (!input_number_.isEmpty()) {
            input_number_.chop(1);
            SetText(input_number_);
        }
    });

    connect(ui->tb_add, &QPushButton::clicked, this, [this](){ SetOperation(Operation::ADDITION); });
    connect(ui->tb_substract, &QPushButton::clicked, this, [this](){ SetOperation(Operation::SUBTRACTION); });
    connect(ui->tb_multiplicate, &QPushButton::clicked, this, [this](){ SetOperation(Operation::MULTIPLICATION); });
    connect(ui->tb_divide, &QPushButton::clicked, this, [this](){ SetOperation(Operation::DIVISION); });
    connect(ui->tb_power, &QPushButton::clicked, this, [this](){ SetOperation(Operation::POWER); });

    connect(ui->tb_equal, &QPushButton::clicked, this, [this](){
        if (current_operation_ == Operation::NO_OPERATION) {
            return;
        }

        ui->l_formula->setText(QString::number(calculator_.GetNumber()) + " " +
                               OpToString(current_operation_) + " " +
                               QString::number(active_number_) + " =");

        switch (current_operation_) {
        case Operation::ADDITION:       calculator_.Add(active_number_); break;
        case Operation::SUBTRACTION:    calculator_.Sub(active_number_); break;
        case Operation::MULTIPLICATION: calculator_.Mul(active_number_); break;
        case Operation::DIVISION:       calculator_.Div(active_number_); break;
        case Operation::POWER:          calculator_.Pow(active_number_); break;
        default: break;
        }

        active_number_ = calculator_.GetNumber();
        ui->l_result->setText(QString::number(active_number_));

        input_number_ = "";
        current_operation_ = Operation::NO_OPERATION;
    });

    connect(ui->tb_reset, &QPushButton::clicked, this, [this](){
        current_operation_ = Operation::NO_OPERATION;
        ui->l_formula->setText("");
        SetText("0");
    });

    connect(ui->tb_ms, &QPushButton::clicked, this, [this](){
        memory_number_ = active_number_;
        is_memory_set_ = true;
        ui->l_memory->setText("M");
    });

    connect(ui->tb_mc, &QPushButton::clicked, this, [this](){
        is_memory_set_ = false;
        ui->l_memory->setText("");
    });

    connect(ui->tn_mr, &QPushButton::clicked, this, [this](){
        if (is_memory_set_) {
            active_number_ = memory_number_;
            ui->l_result->setText(QString::number(active_number_));
            input_number_ = "";
        }
    });

    SetText("0");
}

MainWindow::~MainWindow() {
    delete ui;
}


QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

QString MainWindow::OpToString(Operation op) {
    switch(op) {
    case Operation::ADDITION:       return "+";
    case Operation::SUBTRACTION:    return "−";
    case Operation::MULTIPLICATION: return "×";
    case Operation::DIVISION:       return "÷";
    case Operation::POWER:          return "^";
    default: return "";
    }
}


void MainWindow::SetText(const QString& text) {
    input_number_ = NormalizeNumber(text);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::AddText(const QString& suffix) {
    SetText(input_number_ + suffix);
}

void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }
    current_operation_ = op;
    ui->l_formula->setText(QString::number(calculator_.GetNumber()) + " " + OpToString(op));

    input_number_ = "";
}
