#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFileSystemModel *fileSysModel = new QFileSystemModel(this);

    fileSysModel->setRootPath(QDir::rootPath());

    ui->fileTreeView->setModel(fileSysModel);
    ui->detailsTableView->setModel(fileSysModel);
    ui->IconsListView->setModel(fileSysModel);

    ui->fileTreeView->setColumnWidth(0, 168);

    ui->IconsListView->setViewMode(QListView::IconMode); // Grid-view mode (Not completely, Items appear horizontally
                                                         // and in a form of rows.
                                                         // similar to "Small size" view on windows.
                                                         // Icons respects each file name (no wrapping)
                                                         // Icon/Items appears in the view disproportionally

    ui->IconsListView->setIconSize(QSize{32, 32});         // No need to set it, just a preference
                                                           // Sometimes Icons are bigger than the others

    ui->IconsListView->setGridSize(QSize{85, 85});       // Enforce Complete Grid-view, each item has its room.

    ui->IconsListView->setResizeMode(QListView::Adjust); // Layout of Items is resized when the view itself is resized
                                                         // Mainly by resizing the window.

    ui->IconsListView->setWordWrap(true); // Wraps filename just like what windows does.


    connect(ui->fileTreeView, &QTreeView::clicked, this, [=](const QModelIndex& index){
        ui->detailsTableView->setRootIndex(index);
        ui->IconsListView->setRootIndex(index);
    });

    connect(ui->toggleViewBtn, &QPushButton::clicked, this, [=](){
        int currIdx = ui->mainStackedWidget->currentIndex();
        int stackedWidgetPagesCount = ui->mainStackedWidget->count();

        currIdx = (currIdx + 1) % stackedWidgetPagesCount;

        ui->mainStackedWidget->setCurrentIndex(currIdx);
    });

    connect(ui->IconsListView, &QListView::doubleClicked, this, [=](const QModelIndex &index){
        ui->IconsListView->setRootIndex(index);
        ui->fileTreeView->setCurrentIndex(index);
        ui->detailsTableView->setRootIndex(index);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


