#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>
#include <random>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetRandomGen(const std::mt19937& random_gen);

private slots:
    void on_list_widget_currentRowChanged(int currentRow);

//Workpieces
    void on_pb_tea_clicked();
    void on_pb_cakes_clicked();
//working to iterator
    void on_pb_inter_decrease_clicked();
    void on_pb_iter_increase_clicked();
    void on_pb_iter_begin_clicked();
    void on_pb_iter_end_clicked();
//algorithms
    void on_pb_min_element_clicked();
    void on_pb_max_element_clicked();
    void on_pb_sort_clicked();
    void on_pb_sort_r_clicked();
    void on_pb_unique_clicked();
    void on_pb_reverse_clicked();
    void on_pb_shuffle_clicked();
    void on_pb_lower_bound_clicked();
    void on_pb_upper_bourd_clicked();
//methods
    void on_pb_pop_front_clicked();
    void on_pb_push_front_clicked();
    void on_pb_pop_back_clicked();
    void on_pb_push_back_clicked();
    void on_pb_erase_clicked();
    void on_pb_insert_clicked();
    void on_pb_clear_clicked();
//find, count, edit, resize
    void on_pb_find_clicked();
    void on_pb_count_clicked();
    void on_pb_edit_clicked();
    void on_pb_resize_clicked();

private:
    void ApplyModel();
    void ApplyIterator();
    void IteratorToBegin();

private:
    Model deque_model_;
    Ui::MainWindow *ui;
    std::mt19937 generator_;
};

static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};
