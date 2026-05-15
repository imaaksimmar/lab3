#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matrix_model.hpp"
#include <QInputDialog>
#include <QHeaderView>
#include <QPainter>
#include <QResizeEvent>


static void fillTable(QTableWidget *tbl, int n) {
    tbl->setRowCount(n);
    tbl->setColumnCount(n);
    tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tbl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tbl->setStyleSheet(
        "QTableWidget { background: rgba(0,0,0,120); color: white; "
        "gridline-color: rgba(255,255,255,80); border: 1px solid rgba(255,255,255,60); }"
        "QHeaderView::section { background: rgba(0,0,0,150); color: white; }"
    );
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(j>i) {
                QTableWidgetItem *item = new QTableWidgetItem("");
                item->setFlags(Qt::NoItemFlags); 
                item->setBackground(QColor(30, 30, 30, 180));
                tbl->setItem(i, j, item);
            } 
            else {
                QTableWidgetItem *item = new QTableWidgetItem("0");
                item->setForeground(Qt::white);
                tbl->setItem(i, j, item);
            }
        }
    }
}


void MainWindow::showModel(QTableWidget *tbl, MatrixModel *model) {
    if(!model) return;
    int n = (int)model->GetSize();
    tbl->setRowCount(n);
    tbl->setColumnCount(n);
    tbl->setVisible(true);
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(j>i) {
                QTableWidgetItem *item = new QTableWidgetItem("");
                item->setFlags(Qt::NoItemFlags);
                item->setBackground(QColor(30, 30, 30, 180));
                tbl->setItem(i, j, item);
            } 
            else {
                double val = model->GetElement(i, j);
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(val));
                item->setForeground(Qt::white);
                tbl->setItem(i, j, item);
            }
        }
    }
}


static void tableToModel(QTableWidget *tbl, MatrixModel *model) {
    int n = (int)model->GetSize();
    for(int i=0; i<n; i++)
        for(int j=0; j<=i; j++)
            model->SetElement(i, j, tbl->item(i,j)->text().toDouble());
}

static void showRight(QLabel *labelB, QTableWidget *tableB,
                      QLabel *labelRes, QTableWidget *tableResult,
                      const QString &resText) {
    labelB->setVisible(false);
    tableB->setVisible(false);
    labelRes->setText(resText);
    labelRes->setGeometry(390, 310, 370, 25);
    labelRes->setVisible(true);
    tableResult->setGeometry(390, 335, 350, 300);
}

static QString globalStyle() {
    return
        "QLabel { color: white; font-weight: bold; }"
        "QSpinBox { background: rgba(0,0,0,150); color: white; border: 1px solid rgba(255,255,255,100); border-radius: 4px; padding: 2px; }"
        "QComboBox { background: rgba(0,0,0,150); color: white; border: 1px solid rgba(255,255,255,100); border-radius: 4px; padding: 2px; }"
        "QComboBox QAbstractItemView { background: rgba(30,30,30,220); color: white; }"
        "QPushButton { background: rgba(60,60,60,180); color: white; border: 1px solid rgba(255,255,255,100); border-radius: 6px; padding: 5px; }"
        "QPushButton:hover { background: rgba(100,100,100,200); }"
        "QPushButton:pressed { background: rgba(40,40,40,200); }";
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      modelA(nullptr), modelB(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Треугольная матрица");
    resize(780, 720);
    setStyleSheet(globalStyle());

    labelSize = new QLabel("Размер:", this);
    labelSize->setGeometry(20, 20, 200, 30);
    spinSize = new QSpinBox(this);
    spinSize->setGeometry(230, 20, 80, 30);
    spinSize->setMinimum(1); spinSize->setMaximum(10); spinSize->setValue(3);

    labelType = new QLabel("Тип хранимых элементов:", this);
    labelType->setGeometry(20, 60, 200, 30);
    comboType = new QComboBox(this);
    comboType->setGeometry(230, 60, 120, 30);
    comboType->addItem("int"); comboType->addItem("double");

    labelContainer = new QLabel("Тип контейнера:", this);
    labelContainer->setGeometry(20, 100, 200, 30);
    comboContainer = new QComboBox(this);
    comboContainer->setGeometry(230, 100, 160, 30);
    comboContainer->addItem("ArraySequence"); comboContainer->addItem("ListSequence");

    labelMut = new QLabel("Режим:", this);
    labelMut->setGeometry(20, 140, 200, 30);
    comboMut = new QComboBox(this);
    comboMut->setGeometry(230, 140, 160, 30);
    comboMut->addItem("Mutable"); comboMut->addItem("Immutable");

    labelOp = new QLabel("Операция:", this);
    labelOp->setGeometry(20, 180, 200, 30);
    comboOp = new QComboBox(this);
    comboOp->setGeometry(230, 180, 200, 30);
    comboOp->addItem("Норма");
    comboOp->addItem("Умножить на скаляр");
    comboOp->addItem("Сложить матрицы");
    comboOp->addItem("Map (x*2)");
    comboOp->addItem("Where (чётные)");
    comboOp->addItem("Reduce (сумма)");

    btnCreate = new QPushButton("Готово", this);
    btnCreate->setGeometry(20, 225, 120, 35);
    btnCompute = new QPushButton("Вычислить", this);
    btnCompute->setGeometry(160, 225, 120, 35);
    btnCompute->setEnabled(false);

    labelResult = new QLabel("", this);
    labelResult->setGeometry(20, 270, 720, 30);
    labelResult->setVisible(false);

    labelA = new QLabel("Матрица A (исходная):", this);
    labelA->setGeometry(20, 310, 350, 25);
    labelA->setVisible(false);
    tableA = new QTableWidget(this);
    tableA->setGeometry(20, 335, 350, 300);
    tableA->setVisible(false);

    labelB = new QLabel("Матрица B:", this);
    labelB->setGeometry(390, 310, 350, 25);
    labelB->setVisible(false);
    tableB = new QTableWidget(this);
    tableB->setGeometry(390, 335, 350, 300);
    tableB->setVisible(false);

    labelResultMatrix = new QLabel("", this);
    labelResultMatrix->setGeometry(390, 310, 370, 25);
    labelResultMatrix->setVisible(false);
    tableResult = new QTableWidget(this);
    tableResult->setGeometry(390, 335, 350, 300);
    tableResult->setVisible(false);

    firework = new FireworkWidget(this);
    firework->setGeometry(0, 0, 780, 720);
    firework->show();

    connect(btnCreate, &QPushButton::clicked, this, &MainWindow::onCreateTable);
    connect(btnCompute, &QPushButton::clicked, this, &MainWindow::onCompute);
    connect(comboOp, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onOperationChanged);
}

MainWindow::~MainWindow()
{
    delete modelA;
    delete modelB;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(hasError) {
        QPixmap bg("/Users/yana/Desktop/lab3/ui/h5.png");
        painter.setOpacity(0.8);
        painter.drawPixmap(0, 0, width(), height(), bg);
    } 
    else {
        QPixmap bg("/Users/yana/Desktop/lab3/ui/h1 (3).jpg");
        painter.setOpacity(0.9);
        painter.drawPixmap(0, 0, width(), height(), bg);
    }
    QMainWindow::paintEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    firework->setGeometry(0, 0, width(), height());
}

void MainWindow::onCreateTable()
{
    int n = spinSize->value();
    bool needB = (comboOp->currentText() == "Сложить матрицы");

    labelResult->setVisible(false);
    tableResult->setVisible(false);
    labelResultMatrix->setVisible(false);

    labelA->setText("Матрица A (исходная):");
    labelA->setVisible(true);
    tableA->setVisible(true);
    fillTable(tableA, n);

    labelB->setVisible(needB);
    tableB->setVisible(needB);
    if (needB) fillTable(tableB, n);

    btnCompute->setEnabled(true);
}

void MainWindow::onOperationChanged(int index)
{
    Q_UNUSED(index);
    if (!tableA->isVisible()) return;
    bool needB = (comboOp->currentText() == "Сложить матрицы");
    tableResult->setVisible(false);
    labelResultMatrix->setVisible(false);
    labelResult->setVisible(false);
    labelB->setVisible(needB);
    tableB->setVisible(needB);
    if (needB) fillTable(tableB, spinSize->value());
}

bool MainWindow::validateTable(QTableWidget *tbl)
{
    bool isDouble = (comboType->currentText() == "double");
    bool foundError = false;
    int n = tbl->rowCount();
    for(int i=0; i<n; i++) {
        for(int j=0; j<= i; j++) {
            QTableWidgetItem *item = tbl->item(i, j);
            if (!item) continue;
            QString text = item->text().trimmed();
            bool ok = false;
            if(isDouble) text.toDouble(&ok);
            else text.toInt(&ok);
            if (!ok) {
                item->setBackground(Qt::red);
                foundError = true;
            } 
            else {
                item->setBackground(QColor(0, 0, 0, 0));
            }
        }
    }
    hasError = foundError;
    update();
    return !foundError;
}

void MainWindow::onCompute()
{
    if(!validateTable(tableA)) {
        QMessageBox::warning(this, "Ошибка", "Матрица A содержит некорректные значения!");
        return;
    }

    QString op = comboOp->currentText();
    QString type = comboType->currentText();
    QString container = comboContainer->currentText();
    bool isMutable = (comboMut->currentText() == "Mutable");
    bool isSumOp = (op == "Сложить матрицы");
    int n = spinSize->value();

    if(isSumOp && !validateTable(tableB)) {
        QMessageBox::warning(this, "Ошибка", "Матрица B содержит некорректные значения!");
        return;
    }

    delete modelA;
    modelA = createModel(type, container, n);
    tableToModel(tableA, modelA);

    tableResult->setVisible(false);
    labelResultMatrix->setVisible(false);

    QString result = "";

    if(op == "Норма") {
        result = "Норма = " + QString::number(modelA->Norm());
    }
    else if(op == "Reduce (сумма)") {
        result = "Сумма = " + QString::number(modelA->Reduce(0.0));
    }
    else if(op == "Умножить на скаляр") {
        bool ok;
        double scalar = QInputDialog::getDouble(this, "Скаляр", "Введите скаляр:", 1.0, -1e9, 1e9, 2, &ok);
        if(!ok) return;
        if(isMutable) {
            modelA->ScalarMultiply(scalar);
            showModel(tableA, modelA);
            result = "A умножена на " + QString::number(scalar) + " (mutable)";
        } 
        else {
            MatrixModel *res = modelA->MultiplyNew(scalar);
            showRight(labelB, tableB, labelResultMatrix, tableResult, "Результат (A не изменилась):");
            showModel(tableResult, res);
            delete res;
            result = "Новая матрица A*" + QString::number(scalar) + " (immutable)";
        }
    }
    else if(op == "Сложить матрицы") {
        delete modelB;
        modelB = createModel(type, container, n);
        tableToModel(tableB, modelB);
        if(isMutable) {
            modelA->Add(*modelB);
            showModel(tableA, modelA);
            result = "A = A+B (mutable)";
        } 
        else {
            MatrixModel *res = modelA->AddNew(*modelB);
            showRight(labelB, tableB, labelResultMatrix, tableResult, "Результат A+B (A не изменилась):");
            showModel(tableResult, res);
            delete res;
            result = "Новая матрица A+B (immutable)";
        }
    }
    else if(op == "Map (x*2)") {
        if(isMutable) {
            modelA->Map();
            showModel(tableA, modelA);
            result = "Map(x*2) к A (mutable)";
        } 
        else {
            MatrixModel *res = modelA->MapNew();
            showRight(labelB, tableB, labelResultMatrix, tableResult, "Результат Map (A не изменилась):");
            showModel(tableResult, res);
            delete res;
            result = "Новая матрица Map(x*2) (immutable)";
        }
    }
    else if (op == "Where (чётные)") {
        if(isMutable) {
            modelA->Where();
            showModel(tableA, modelA);
            result = "Where(чётные) к A (mutable)";
        } 
        else {
            MatrixModel *res = modelA->WhereNew();
            showRight(labelB, tableB, labelResultMatrix, tableResult, "Результат Where (A не изменилась):");
            showModel(tableResult, res);
            delete res;
            result = "Новая матрица Where(чётные) (immutable)";
        }
    }

    labelResult->setText(result);
    labelResult->setVisible(true);
    firework->launch();
}