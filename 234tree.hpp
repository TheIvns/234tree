#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

using T = float;

class ttf_tree
{
    private:
        class hnizdo;
        class prvek;
        
    


    public:
        ttf_tree();
        ~ttf_tree();
        
        

        

        bool empty();

        void TREE_INSERT(const T& data);
        
        void TREEPRINT();

        void clear();
            
        prvek* find_prvek (const T& data, hnizdo* hnizdo_);

        void get_it_down_n_del(const T& data);

        void get_depth();
        


    private:
        hnizdo* pom_hnizdo;
        hnizdo* pom_grandparent;
        hnizdo* main_root;
        hnizdo* bottom_for_switch;
        //po switchi dostanu bottom kde mazu a parent tohoto bottomu
        hnizdo* parent_of_wanted_hnizdo;
        prvek* switched_prvek;

        void insert_into_subtree(const T& data, hnizdo* hnizdo_, hnizdo* parent, bool been_split);

        void insert_into_hnizdo(const T& data, hnizdo* hnizdo_);

        void printhnizdo(hnizdo* hnizdo_);

        void split(hnizdo* hnizdo_, hnizdo* &parent);

        void printlv(hnizdo* hnizdo_, hnizdo* grandparent, int counter_for_grandparent, int n, int pom);

        void remove_all(hnizdo* hnizdo_, int count);

        hnizdo* find_hnizdo_with_prvek_for_del (const T& data, hnizdo* hnizdo_, hnizdo* parent);

        hnizdo* find_hnizdo_with_prvek_after_switch (prvek* prvek_, hnizdo* hnizdo_, hnizdo* parent, bool first_turn_right);

        void delete_prvek(const T&data, prvek* prvek_, hnizdo* hnizdo_, hnizdo* parent);

        void rotation_for_one_node_parent (hnizdo* hnizdo_, hnizdo* parent);

        void rotation_for_two_node_parent (hnizdo* hnizdo_, hnizdo* parent, int what_type);

        void merge_for_two_node_parent (hnizdo* hnizdo_, hnizdo* parent, int what_type);
        
        void merge_for_three_node_parent (hnizdo* hnizdo_, hnizdo* parent, int what_type);

        void rotation_for_three_node_parent (hnizdo* hnizdo_, hnizdo* parent, int what_type);

        void merge_with_with_one_node_parent (hnizdo* hnizdo_, hnizdo* parent);

        int reorganize_the_tree(hnizdo* hnizdo_, hnizdo* parent);

        prvek* find_successor_n_insert_prvek (hnizdo* hnizdo_, prvek* prvek_, bool first_turn_right);



        unsigned int number_of_elements;
        unsigned int depth;

    


        


};

class ttf_tree::hnizdo
{
    private:
        //class prvek;

        
    public:
        hnizdo();

    
    private:
        hnizdo* left_left;
        hnizdo* middle_left;
        hnizdo* middle_right;
        hnizdo* right_right;
        hnizdo* middle;

        unsigned int number_of_nodes;
        std::vector<prvek*> hnizdo_arr;

    friend class ttf_tree;
    
};


class ttf_tree::prvek
{
    public:
        prvek(T data);
    
    private:
        T data;

        T get_data() const;

    friend ttf_tree;
};

