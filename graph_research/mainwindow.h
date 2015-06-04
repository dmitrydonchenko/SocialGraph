#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Graph graph;
    QMap<int, Node> nodes;

private slots:
    void exportNodesFile();
    void exportEdgesFile();
    void executeAlgorithm();
};

#endif // MAINWINDOW_H
