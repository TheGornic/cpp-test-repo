#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <model.h>
#include <string>
#include <algorithm>
#include <algo.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    std::random_device rd;
    std::mt19937 gen(rd());
    SetRandomGen(gen);

    ApplyModel();
    ApplyIterator();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::IteratorToBegin(){
    deque_model_.iterator = deque_model_.items.begin();
}

//update ui
void MainWindow::ApplyModel() {
    int i = 0;
    auto presever_iter = deque_model_.iterator;
    ui->list_widget->clear();
    for (const std::string& vect : deque_model_.items){
        ui->list_widget->addItem(QString("%1: %2").arg(QString::number(i), QString::fromStdString(vect)));
        i++;
    }
    ui->list_widget->addItem("end");
    deque_model_.iterator = presever_iter;

    ui->pb_pop_back->setDisabled(deque_model_.items.empty());
    ui->pb_pop_front->setDisabled(deque_model_.items.empty());
    ui->pb_erase->setDisabled(deque_model_.items.empty());
    ui->txt_size->setText(QString::number(deque_model_.items.size()));
}

//changed iterator
void MainWindow::ApplyIterator(){
    int index_iterator = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    index_iterator = std::clamp(index_iterator, 0, (int)deque_model_.items.size());
    ui->list_widget->setCurrentRow(index_iterator);

    bool disabled_if_end = deque_model_.iterator == deque_model_.items.end();
    ui->pb_edit->setDisabled(disabled_if_end);
    ui->pb_erase->setDisabled(disabled_if_end);
    ui->pb_iter_increase->setDisabled(disabled_if_end);

    bool disabled_if_begin = deque_model_.iterator == deque_model_.items.begin();
    ui->pb_inter_decrease->setDisabled(disabled_if_begin);

    if (disabled_if_end){
        ui->txt_elem_content->setText("");
    } else {
        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
    }
}

//random generator for shuffle
void MainWindow::SetRandomGen(const std::mt19937& random_gen){
    generator_ = random_gen;
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow){
    currentRow = std::clamp(currentRow, 0, static_cast<int>(deque_model_.items.size()+1));
    deque_model_.iterator = deque_model_.items.begin() + currentRow;
    ApplyIterator();
}

//Workpieces
void MainWindow::on_pb_tea_clicked(){
    deque_model_.items = tea;
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_cakes_clicked(){
    deque_model_.items = cakes;
    IteratorToBegin();;
    ApplyModel();
    ApplyIterator();
}

//Applied_to_iterator
void MainWindow::on_pb_inter_decrease_clicked(){
    --deque_model_.iterator;
    ApplyIterator();
}

void MainWindow::on_pb_iter_increase_clicked(){
    ++deque_model_.iterator;
    ApplyIterator();
}

void MainWindow::on_pb_iter_begin_clicked(){
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_pb_iter_end_clicked(){
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}

//algorithms
void MainWindow::on_pb_min_element_clicked(){
    deque_model_.iterator = std::min_element(deque_model_.items.begin(),deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::on_pb_max_element_clicked(){
    deque_model_.iterator = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::on_pb_sort_clicked(){
    auto comparator = [](const std::string& str_left, const std::string& str_right){
        return str_left < str_right;
    };
    IteratorToBegin();
    deque_model_.items = MergeSort(deque_model_.items, comparator);
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_sort_r_clicked(){
    auto comparator = [](const std::string& str_left, const std::string& str_right){
        return QString::compare(QString::fromStdString(str_left),QString::fromStdString(str_right),Qt::CaseInsensitive)< 0;
    };
    IteratorToBegin();
    deque_model_.items = MergeSort(deque_model_.items, comparator);
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_unique_clicked(){
    if (!std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())){
        return;
    }
    auto erase_elements = std::unique(deque_model_.items.begin(),deque_model_.items.end());
    deque_model_.items.erase(erase_elements,deque_model_.items.end());
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_reverse_clicked(){
    std::reverse(deque_model_.items.begin(),deque_model_.items.end());
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_shuffle_clicked(){
    std::shuffle(deque_model_.items.begin(),deque_model_.items.end(), generator_);
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_lower_bound_clicked(){
    if (!std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())){
        return;
    }
    std::string text = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::lower_bound(deque_model_.items.begin(),deque_model_.items.end(), text);
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_upper_bourd_clicked(){
    if (!std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())){
        return;
    }
    std::string text = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::upper_bound(deque_model_.items.begin(),deque_model_.items.end(), text);
    ApplyModel();
    ApplyIterator();
}

//methods
void MainWindow::on_pb_pop_front_clicked(){
    deque_model_.items.pop_front();
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_push_front_clicked(){
    std::string text = ui->txt_elem_content->text().toStdString();
    deque_model_.items.push_front(text);
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_pop_back_clicked(){
    deque_model_.items.pop_back();
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_push_back_clicked(){
    std::string text = ui->txt_elem_content->text().toStdString();
    deque_model_.items.push_back(text);
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_erase_clicked(){
    deque_model_.items.erase(deque_model_.iterator);
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_insert_clicked(){
    std::string text = ui->txt_elem_content->text().toStdString();
    deque_model_.items.insert(deque_model_.iterator, text);
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_clear_clicked(){
    deque_model_.items.clear();
    IteratorToBegin();
    ApplyModel();
    ApplyIterator();
}

//find, count, edit, resize
void MainWindow::on_pb_find_clicked(){
    std::string text_find = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::find(deque_model_.items.begin(),deque_model_.items.end(), text_find);
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_count_clicked(){
    std::string text_find = ui->le_count->text().toStdString();
    int count = std::count(deque_model_.items.begin(),deque_model_.items.end(), text_find);
    ui->lbl_count->setText(QString::number(count));
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_edit_clicked(){
    *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_pb_resize_clicked(){
    int size_deque = ui->txt_size->text().toInt();
    deque_model_.items.resize(size_deque);
    ApplyModel();
    ApplyIterator();
}








































