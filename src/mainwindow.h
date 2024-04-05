#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>


//#include "AVL_Trees.cpp" //using as placeholder for red-black trees until fully implemented
#include "RedBlackTrees.cpp" //including red black trees implementation
#include "DoublyLinkedList.cpp" //including dll implementation to allow O(1) insertion/deletion to front and back nodes
#include "Graphs.cpp" //including my version of graphs to create links between genres of films, to determine other similar movies
#include "VectorImplementation.cpp" //including my own implementation of vectors, is dynamic array with pop_back and push_back functions
//and can directly access any index, if need be

#include "MergeSort.cpp" //including my merge sort algorithm to sort edges by weight, bool operators overloaded in edge class



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //declaring red black trees for storage
    RedBlackTree<Show> showsTree;
    RedBlackTree<Director> directorsTree;
    RedBlackTree<Actor> actorsTree;
    RedBlackTree<Genre> genresTree;
    RedBlackTree<Rating> ratingsTree;
    RedBlackTree<Country> countriesTree;

    //a graph of all shows, and the edges (and their weights) represent common genres between the nodes
    //functions similarly to a recommendation system, higher weight = more likely to recommend, since similar tastes
    GraphList<RBTNode<Show>*> showsLinkedByGenre; //create an undirected graph

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_AddRecToWatch_clicked();

    void on_ClearRec_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
