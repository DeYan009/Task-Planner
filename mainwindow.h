#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QDate>
#include <QStringList>
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

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDateSelected();
    void addTask();
    void editTask();
    void deleteTask();

private:
    void setupUI();
    void updateTaskList();
    void saveTasks();
    void loadTasks();

    QCalendarWidget *calendar;
    QListWidget *taskList;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QLabel *selectedDateLabel;
    
    QDate currentDate;
    QMap<QDate, QStringList> tasks;
};

#endif // MAINWINDOW_H