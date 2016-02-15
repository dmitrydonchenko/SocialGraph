#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QQueue>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    graph = Graph();
    connect(ui->actionExport_Edges_File, SIGNAL(triggered()), this, SLOT(exportEdgesFile()));
    connect(ui->actionExport_Nodes_File, SIGNAL(triggered()), this, SLOT(exportNodesFile()));
    connect(ui->executeAlgorithmButton, SIGNAL(clicked()), this, SLOT(executeAlgorithm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exportNodesFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose a file to open", "", "CSV graph(*.csv)");
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd())
    {
        lines.append(in.readLine());
    }
    graph.exportNodes(lines);
    nodes = graph.getNodes();

    QMap<int, Node>::iterator i;
    for (i = nodes.begin(); i != nodes.end(); i++)
    {
        ui->nodesTableWidget->setRowCount(ui->nodesTableWidget->rowCount() + 1);
        ui->nodesTableWidget->setItem(ui->nodesTableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::number(i.key())));
        ui->nodesTableWidget->setItem(ui->nodesTableWidget->rowCount() - 1, 1, new QTableWidgetItem(i.value().getLabel()));
    }
}

void MainWindow::exportEdgesFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose a file to open", "", "CSV graph(*.csv)");
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd())
    {
        lines.append(in.readLine());
    }
    graph.exportEdges(lines);
    nodes = graph.getNodes();

    QMap<int, Node>::iterator i;
    QMap<int, Edge>::iterator j;
    for (i = nodes.begin(); i != nodes.end(); i++)
    {
        QMap<int, Edge> edges = i.value().getEdges();
        for(j = edges.begin(); j != edges.end(); j++)
        {
            ui->edgesTableWidget->setRowCount(ui->edgesTableWidget->rowCount() + 1);
            ui->edgesTableWidget->setItem(ui->edgesTableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::number(j.key())));
            ui->edgesTableWidget->setItem(ui->edgesTableWidget->rowCount() - 1, 1, new QTableWidgetItem(j.value().getSource()));
            ui->edgesTableWidget->setItem(ui->edgesTableWidget->rowCount() - 1, 2, new QTableWidgetItem(j.value().getTarget()));
            ui->edgesTableWidget->setItem(ui->edgesTableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString::number(j.value().getWeight())));
        }
    }
}

void MainWindow::executeAlgorithm()
{
    Node n;
    int index = 0;
    foreach(n, nodes)
    {
        QQueue<int> queue = QQueue<int>();
        queue.push_front(n.getId());
        double weight = 0.0;
        QMap<int, char> used = QMap<int, char>();
        used[n.getId()] = 1;
        double d = 0.85;
        while(!queue.empty())
        {
            int v = queue.front();
            queue.pop_back();
            QMap<int, Edge> edges = nodes[v].getEdges();
            Edge e;
            double localSum = 0.0;
            foreach(e, edges)
            {
                int to = e.getTargetId();
                if(to != n.getId())
                {
                    if(!used[to])
                    {
                        used[to] = 1;
                        queue.push_back(to);
                        localSum += e.getWeight();
                    }
                }
            }
            localSum *= d;
            weight += localSum;
            d *= 0.85;
        }
        n.setWeight(weight);
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, QString::number(weight));
        ui->nodesTableWidget->setItem(index, 2, item);
        index++;
    }
    ui->nodesTableWidget->sortByColumn(2, Qt::DescendingOrder);
}

