#include "mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCalendarWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    loadTasks();
}

MainWindow::~MainWindow()
{
    saveTasks();
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Календарь
    calendar = new QCalendarWidget(this);
    calendar->setGridVisible(true);
    connect(calendar, &QCalendarWidget::selectionChanged, this, &MainWindow::onDateSelected);

    // Метка с выбранной датой
    selectedDateLabel = new QLabel(this);
    currentDate = calendar->selectedDate();
    selectedDateLabel->setText("Выбрана дата: " + currentDate.toString("dd.MM.yyyy"));

    // Список задач
    taskList = new QListWidget(this);

    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Добавить", this);
    editButton = new QPushButton("Редактировать", this);
    deleteButton = new QPushButton("Удалить", this);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editTask);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteTask);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    // Компоновка
    mainLayout->addWidget(calendar);
    mainLayout->addWidget(selectedDateLabel);
    mainLayout->addWidget(taskList);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);
    resize(600, 500);
    setWindowTitle("Планировщик задач");
}

void MainWindow::onDateSelected()
{
    currentDate = calendar->selectedDate();
    selectedDateLabel->setText("Выбрана дата: " + currentDate.toString("dd.MM.yyyy"));
    updateTaskList();
}

void MainWindow::addTask()
{
    bool ok;
    QString task = QInputDialog::getText(this, "Добавить задачу",
                                         "Описание задачи:", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !task.isEmpty()) {
        tasks[currentDate].append(task);
        updateTaskList();
    }
}

void MainWindow::editTask()
{
    if (taskList->currentRow() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите задачу для редактирования");
        return;
    }

    int index = taskList->currentRow();
    bool ok;
    QString task = QInputDialog::getText(this, "Редактировать задачу",
                                         "Описание задачи:", QLineEdit::Normal,
                                         tasks[currentDate][index], &ok);
    if (ok && !task.isEmpty()) {
        tasks[currentDate][index] = task;
        updateTaskList();
    }
}

void MainWindow::deleteTask()
{
    if (taskList->currentRow() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите задачу для удаления");
        return;
    }

    int index = taskList->currentRow();
    tasks[currentDate].removeAt(index);
    updateTaskList();
}

void MainWindow::updateTaskList()
{
    taskList->clear();
    if (tasks.contains(currentDate)) {
        taskList->addItems(tasks[currentDate]);
    }
}

void MainWindow::saveTasks()
{
    QJsonObject json;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        QJsonArray taskArray;
        for (const QString &task : it.value()) {
            taskArray.append(task);
        }
        json[it.key().toString("yyyy-MM-dd")] = taskArray;
    }

    QFile file("tasks.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(json).toJson());
        file.close();
    }
}

void MainWindow::loadTasks()
{
    QFile file("tasks.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject json = doc.object();

        for (auto it = json.begin(); it != json.end(); ++it) {
            QDate date = QDate::fromString(it.key(), "yyyy-MM-dd");
            QJsonArray taskArray = it.value().toArray();
            QStringList taskList;
            for (const QJsonValue &value : taskArray) {
                taskList.append(value.toString());
            }
            tasks[date] = taskList;
        }
        file.close();
    }

    updateTaskList();
}