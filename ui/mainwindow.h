#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>
#include <QComboBox>
#include <QMessageBox>
#include <QPainter>
#include "firework.h"
#include "matrix_model.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

    protected:
        void paintEvent(QPaintEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;

    private slots:
        void onCreateTable();
        void onOperationChanged(int index);
        void onCompute();

    private:
        Ui::MainWindow *ui;

        QLabel *labelSize;      
        QSpinBox *spinSize;
        QLabel *labelType;       
        QComboBox *comboType;
        QLabel *labelContainer;  
        QComboBox *comboContainer;
        QLabel *labelMut;        
        QComboBox *comboMut;
        QLabel *labelOp;         
        QComboBox *comboOp;
        QPushButton *btnCreate;  
        QPushButton *btnCompute;
        
        QLabel *labelA;          
        QTableWidget *tableA;
        QLabel *labelB;          
        QTableWidget *tableB;
        QLabel *labelResultMatrix; 
        QTableWidget *tableResult;
        QLabel *labelResult;

        MatrixModel *modelA = nullptr;
        MatrixModel *modelB = nullptr;

        FireworkWidget *firework;
        bool hasError = false;
        bool validateTable(QTableWidget *tbl);
        void showModel(QTableWidget *tbl, MatrixModel *model);
};