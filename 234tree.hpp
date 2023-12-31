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
#include <unistd.h>

template <class T>
class TTFT
{
    private:
    class element
    {
    public:
    element(T data);
    T data;
    T get_data();
    friend TTFT;
    };

    class nest
    {
    public:
    nest();

    unsigned int number_of_elements;
    std::vector<std::unique_ptr<element > > nest_arr;
    std::vector<std::unique_ptr<nest> > ptr_arr;
    };
    public:
    TTFT();
    
    void insert(const T& data); 
    bool empty();
    void TREEPRINT();
    bool is_TTFT();
    void delete_element(const T& data);
    void is_element_in_tree(const T& data);



    private:
    std::stack<T> stack;
    std::stack<std::unique_ptr<nest> > ptr_stack;
    std::unique_ptr<TTFT<T>::nest> main_root;
    unsigned int TOTAL_number_of_elements;
    unsigned int depth;
    unsigned int help_depth;
    T help_data;
    
    void insert_into_subtree(const T& data, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& parent, bool was_split);
    void insert_into_nest (const T& data, std::unique_ptr<TTFT<T>::nest>& nest_, bool new_data);
    int find_way(const T& data, std::unique_ptr<TTFT<T>::nest>& nest_);
    void split(std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& parent);
    void printlv(std::unique_ptr<TTFT<T>::nest>& nest_, int n, int pom);
    bool check_subtree(std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_, int parent_control);
    bool find_element(const T& data, int pom_depth, std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_, bool deleting, bool right, bool successor);
    bool is_case_I(int pom, std::unique_ptr<TTFT<T>::nest>& nest_);
    void rotate(int to, int from, std::unique_ptr<TTFT<T>::nest>& parent);
    void caseI(int pom, std::unique_ptr<TTFT<T>::nest>& parent);
    int find_overseer(int dataTO, int dataFROM, std::unique_ptr<TTFT<T>::nest>& parent);
    int find_in_nest(const T& data, std::unique_ptr<TTFT<T>::nest>& nest_);
    void cut_ith_el(int order, std::unique_ptr<TTFT<T>::nest>& nest_);
    void caseII(std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_);
    bool is_case_II(std::unique_ptr<TTFT<T>::nest>& parent);
    bool is_case_III(int pom, std::unique_ptr<TTFT<T>::nest>& parent);
    void caseIII(int pom, std::unique_ptr<TTFT<T>::nest>& parent, const T& data_to_del);
    void merge(int home, int neighbour, std::unique_ptr<TTFT<T>::nest>& parent, const T& data_to_del);
    void insert_ptr_to_nest(int pos, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& input);
    void del_ith_ptr(int pos, std::unique_ptr<TTFT<T>::nest>& nest_);
    std::unique_ptr<typename TTFT<T>::element> find_successor(int way, int pom_depth, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::element>& element_, bool turned);
    bool is_in_tree(const T& data, int pom_depth, std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_);
};

template <class T>
TTFT<T>::TTFT()
{
    main_root = nullptr;
    TOTAL_number_of_elements = 0;
    depth = 0;
}


template <class T>
T TTFT<T>::element::get_data()
{
    return this->data;
}

template <class T>
TTFT<T>::nest::nest()
{
    number_of_elements = 0;
    std::vector<std::unique_ptr<TTFT<T>::element > > nest_arr;
    std::vector<std::unique_ptr<TTFT<T>::nest> > ptr_arr;
}

template <class T>
TTFT<T>::element::element(T data)
    :data(data)
{

}

template <class T>
int TTFT<T>::find_way(const T& data, std::unique_ptr<TTFT<T>::nest>& nest_)
{
    for (int i = 0; i < nest_->number_of_elements; i++)
    {
        if (data < nest_->nest_arr[i]->get_data())
        {
            return i;
        }
    }
    return (nest_->number_of_elements);
}


template <class T>
bool TTFT<T>::empty()
{
    if (this->main_root != nullptr)
    {
        return false;
    }
    return true;
}

template <class T>
void TTFT<T>::insert_into_nest(const T& data, std::unique_ptr<TTFT<T>::nest>& nest_, bool new_data)
{
    if(new_data){this -> TOTAL_number_of_elements ++;}
    if (nest_->number_of_elements == 0)
    {
        nest_->nest_arr.push_back(std::make_unique<TTFT<T>::element>(data));
        nest_->number_of_elements ++;
        return;
    }
    int pom = find_way(data, nest_);
    for(int i = 0; i < nest_->number_of_elements-pom; i++)
    {
        this->stack.push(nest_->nest_arr[nest_->number_of_elements-1-i]->get_data());
        nest_ -> nest_arr.pop_back();
    }
    nest_->nest_arr.push_back(std::make_unique<TTFT<T>::element>(data));
    for(int i = 0; i < nest_->number_of_elements-pom; i++)
    {
       nest_->nest_arr.push_back(std::make_unique<TTFT<T>::element>(this->stack.top()));
       stack.pop();
    }
    nest_->number_of_elements ++;
}

template <class T>
void TTFT<T>::split(std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& parent)
{
    std::unique_ptr<TTFT<T>::element> middle = std::move(nest_->nest_arr[1]);
    std::unique_ptr<TTFT<T>::element> right = std::move(nest_->nest_arr[2]);
    nest_->nest_arr.pop_back();
    nest_->nest_arr.pop_back();
    nest_->number_of_elements --;
    nest_->number_of_elements --;
    int pom;
    if (nest_==main_root)
    {
        depth ++;
        std::unique_ptr<TTFT<T>::nest> nhelp = std::move(nest_);
        main_root = std::make_unique<TTFT<T>::nest>();
        insert_into_nest(middle->get_data(), main_root, false);
        main_root->ptr_arr.push_back(std::move(nhelp));
        main_root->ptr_arr.push_back(std::make_unique<TTFT<T>::nest>());
        insert_into_nest(right->get_data(), main_root->ptr_arr[1], false);
        if(main_root->ptr_arr[0]->ptr_arr.size()!= 0)
        {
            for(int i = 0; i < 2; i++)
            {
                ptr_stack.push(std::move(main_root->ptr_arr[0]->ptr_arr[main_root->ptr_arr[0]->ptr_arr.size()-1]));
                main_root->ptr_arr[0]->ptr_arr.pop_back();
            }
            for(int i = 0; i < 2; i++)
            {
                main_root->ptr_arr[1]->ptr_arr.push_back(std::move(ptr_stack.top()));
                ptr_stack.pop();
            }
        }
        return;
    }
    pom = find_way(middle->get_data(), parent);
    insert_into_nest(middle->get_data(), parent, false);
    for(int i = 0; i < parent->number_of_elements-1-pom; i++)
    {
        ptr_stack.push(std::move(parent->ptr_arr[parent->ptr_arr.size()-1]));
        parent->ptr_arr.pop_back();
    }
    parent->ptr_arr.push_back(std::make_unique<TTFT<T>::nest>());
    insert_into_nest(right->get_data(), parent->ptr_arr[parent->ptr_arr.size()-1], false);
    for(int i =0; i<parent->number_of_elements-1-pom; i++)
    {
        parent->ptr_arr.push_back(std::move(ptr_stack.top()));
        ptr_stack.pop();
    }
    if(parent->ptr_arr[pom]->ptr_arr.size() != 0)
    {
        for(int i = 0; i < 2; i++)
        {
            ptr_stack.push(std::move(parent->ptr_arr[pom]->ptr_arr[parent->ptr_arr[pom]->ptr_arr.size()-1]));
            parent->ptr_arr[pom]->ptr_arr.pop_back();
        }
        //nakreslit asi pom nest od parent, potom to prehodit k parent ptr arr
        for(int i = 0; i < 2; i++)
        {
            parent->ptr_arr[pom+1]->ptr_arr.push_back(std::move(ptr_stack.top()));
            ptr_stack.pop();
        }
    }
}

template <class T>
void TTFT<T>::insert(const T& data)
{
    if(empty())
    {
        this -> depth ++;
        this->main_root = std::make_unique<TTFT<T>::nest>();
        insert_into_nest(data, this->main_root, true); 
        return;
    }
//treba to pujde takhle ten grandparent
    
    insert_into_subtree(data, this->main_root, this->main_root, false);
    return;
}
template <class T>
void TTFT<T>::insert_into_subtree(const T& data, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& parent, bool was_split)
{
    bool held_three = false;
    
    for(int i = 0; i < nest_->nest_arr.size(); i++)
    {
        if (data == nest_->nest_arr[i]->get_data())
        {   
            std::cout<<"data are already in the tree"<<std::endl;
            return;
        }
    }  
    if(nest_->number_of_elements == 3 && !was_split)
    {
        held_three = true;         
        split(nest_, parent);
        was_split = true;
    }   
    if (was_split && held_three)
    {
        insert_into_subtree(data, parent, main_root, true);
        return;
    }
    if (nest_->ptr_arr.size() != 0)
    {
        int pom = find_way(data, nest_);
        insert_into_subtree(data, nest_->ptr_arr[pom], nest_, false);
        return;
    }   
    insert_into_nest(data, nest_, true);
}

template <class T>
void TTFT<T>::TREEPRINT()
{  
    
    for (int i = 1; i <= this -> depth; i++)
    {
    printlv(main_root, i, 1);
    std::cout << std::endl;
    }
}

template <class T>
void TTFT<T>::printlv(std::unique_ptr<TTFT<T>::nest>& nest_, int n, int pom)
{   
    if (pom == n)
    {
        for (int i = 0; i < nest_->number_of_elements; i ++)
        {
            T data = nest_->nest_arr[i]->get_data();
            std::cout << data << ",";
        }
        std::cout << "K";
        std::cout << std::setw(1) << "";
        return;
    }
    if (nest_->ptr_arr.size()==0)
    {
        std::cout << "X";
        std::cout << std::setw(1) << "";
        return;
    }
    pom ++;
    for(int i = 0; i<nest_->ptr_arr.size(); i++)
    {
        printlv(nest_->ptr_arr[i], n, pom);
    }
    std::cout <<"///";
    std::cout<<std::flush;
    return;

}

template <class T>
bool TTFT<T>::is_TTFT()
{
    help_depth = 0;
    return check_subtree(main_root, main_root, 0);
}

template <class T>//check jestli fakt funguje
bool TTFT<T>::check_subtree(std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_, int parent_control)
{//dodelat
    bool value = true;
    if (nest_ == main_root)
    {
        for(int i = 0; i < main_root->ptr_arr.size(); i++)
        {
            value = check_subtree(main_root, main_root->ptr_arr[i], i);
            if(value==false){return value;};
        }
        return  value;
    }
    if(parent_control == parent->number_of_elements)
    {
        for(int a = 0; a < nest_->nest_arr.size(); a++)
        {
            if (nest_->nest_arr[a]->get_data() < parent->nest_arr[parent_control-1]->get_data())
            {
                return false;
            }
        }
    }
    else
    {
        for(int a = 0; a < nest_->nest_arr.size(); a++)
        {
            if (nest_->nest_arr[a]->get_data()>parent->nest_arr[parent_control]->get_data())
            {
                return false;
            }
        }
    }
    if(nest_->ptr_arr.size()==0)
    {
        return true;
    }
    for (int i = 0; i < nest_->ptr_arr.size(); i++)
        {
            value = check_subtree(nest_, nest_->ptr_arr[i], i);
            if(value == false){return value;};
        }
    return value;
}

template <class T>
void TTFT<T>::delete_element(const T& data)
{
    if (!is_in_tree(data, 1, main_root, main_root))
    {
        return;
    }
    find_element(data, 1,  main_root, main_root, true, NULL, false, false); 
    TOTAL_number_of_elements --;  
    return;
}

template <class T>
bool TTFT<T>::is_case_I(int pom, std::unique_ptr<TTFT<T>::nest>& parent)
{
    if (pom == 0)
    {
        if (parent->ptr_arr[pom+1]->nest_arr.size() > 1){return true;}
    }
    else if (pom == parent->ptr_arr.size()-1)
    {
        if (parent->ptr_arr[pom-1]->nest_arr.size() > 1){return true;}
    }
    else
    {
        if (parent->ptr_arr[pom-1]->nest_arr.size() > 1){return true;}
        if (parent->ptr_arr[pom+1]->nest_arr.size() > 1){return true;}
    }  
    return false;
}
template <class T>
void TTFT<T>::caseI(int pom, std::unique_ptr<TTFT<T>::nest>& parent)
{
    if (pom > 0){
        if (parent->ptr_arr[pom - 1]->nest_arr.size() > 1){
            rotate(pom-1, pom, parent);
            return;
        }
    }
    if (parent->ptr_arr[pom + 1]->nest_arr.size() > 1){
        rotate(pom+1, pom, parent);
        return;
    }    
}
template <class T>
// < data2 && > data 1
int TTFT<T>::find_overseer(int data1, int data2, std::unique_ptr<TTFT<T>::nest>& parent)
{
    int pom;
    if (data1 < data2)
    {
        for (int i = 0; i < parent->ptr_arr.size(); i ++)
        {
            pom = find_in_nest(data1, parent->ptr_arr[i]);
            if (pom != -1)
            {
                return i;
            }
        }
    }
    for (int i = 0; i < parent->ptr_arr.size(); i ++)
        {
            pom = find_in_nest(data2, parent->ptr_arr[i]);
            if (pom != -1)
            {
                return i;
            }
        }
}

template <class T>
void TTFT<T>::rotate(int from, int to, std::unique_ptr<TTFT<T>::nest>& parent)
{
    if (from < to )
    {       
        std::unique_ptr<TTFT<T>::element> el_to_rot = std::move(parent->ptr_arr[from]->nest_arr[parent->ptr_arr[from]->nest_arr.size()-1]);
        parent->ptr_arr[from]->nest_arr.pop_back();
        int pom = find_overseer(parent->ptr_arr[from]->nest_arr[parent->ptr_arr[from]->nest_arr.size()-1]->get_data(), parent->ptr_arr[to]->nest_arr[0]->get_data(), parent);
        std::unique_ptr<TTFT<T>::element> el_to_rot_par = std::move(parent->nest_arr[pom]);
        parent->nest_arr.erase(parent->nest_arr.begin()+pom);
        parent->ptr_arr[from]->number_of_elements --;
        parent->number_of_elements --;
        insert_into_nest(el_to_rot_par->get_data(), parent->ptr_arr[to], false);
        insert_into_nest(el_to_rot->get_data(), parent, false);
        if (parent->ptr_arr[0]->ptr_arr.size() != 0)
        {
            insert_ptr_to_nest(0, parent->ptr_arr[to], parent->ptr_arr[from]->ptr_arr[parent->ptr_arr[from]->ptr_arr.size()-1]);
            parent->ptr_arr[from]->ptr_arr.pop_back();
        }
        return;
    }
    std::unique_ptr<TTFT<T>::element> el_to_rot = std::move(parent->ptr_arr[from]->nest_arr[0]);
    parent->ptr_arr[from]->nest_arr.erase(parent->ptr_arr[from]->nest_arr.begin());
    int pom = find_overseer(parent->ptr_arr[to]->nest_arr[0]->get_data(), parent->ptr_arr[from]->nest_arr[0]->get_data(), parent);
    std::unique_ptr<TTFT<T>::element> el_to_rot_par = std::move(parent->nest_arr[pom]);
    parent->nest_arr.erase(parent->nest_arr.begin()+pom);
    parent->ptr_arr[from]->number_of_elements --;
    parent->number_of_elements --;
    insert_into_nest(el_to_rot_par->get_data(), parent->ptr_arr[to], false);
    insert_into_nest(el_to_rot->get_data(), parent, false);
    if (parent->ptr_arr[0]->ptr_arr.size() != 0)
        {
            insert_ptr_to_nest(parent->ptr_arr[to]->ptr_arr.size(), parent->ptr_arr[to], parent->ptr_arr[from]->ptr_arr[0]);
            del_ith_ptr(0,parent->ptr_arr[from]);
        }
    return;
    
}
template <class T>
bool TTFT<T>::find_element(const T& data, int help_depth, std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_, bool deleting, bool right, bool successor)
{
    TREEPRINT();
    int pom;
    if(nest_ == main_root && depth == 1)
    {
        if(deleting)
        {
            pom = find_in_nest(data, main_root);
            if(pom>-1)
            {
                cut_ith_el(pom, main_root);
                if (TOTAL_number_of_elements == 1)
                {
                    main_root = nullptr;
                }
            }
        }
        return true;
    }
    int way_from_parent = find_way(data, parent);
    int way_from_nest = find_way(data, parent->ptr_arr[way_from_parent]);
    if(nest_ == main_root && depth > 1 && nest_->nest_arr.size()==1)
    {
        if(nest_->nest_arr[0]->get_data()==data)
        {
            std::unique_ptr<TTFT<T>::element> el = std::move(parent->nest_arr[0]);
            cut_ith_el(0, parent);
            el = find_successor(1, help_depth, parent, el, false);
            insert_into_nest(el->get_data(), parent, false);
            help_depth ++;
            pom = find_in_nest(el->get_data(), parent);
            return find_element(data, help_depth, parent, parent->ptr_arr[pom+1], deleting, true, true);
        }
        help_depth ++;
        return find_element(data, help_depth, nest_, nest_->ptr_arr[way_from_parent], deleting, false, false);
    }
    if(nest_->nest_arr.size()==1)
    {    
        if (is_case_II(parent))
        {
            caseII(parent, nest_);
            help_depth --;
        }
        else
        {
            for (int i = 0; i < parent->ptr_arr.size(); i++)
            {
                if(parent->ptr_arr[i]==nest_)
                {
                    pom = i;
                    break;
                }
            }
            if(is_case_I(pom, parent))
            {
                caseI(pom, parent);

            }
            else if(is_case_III(pom, parent))
            {
                caseIII(pom, parent, data);
            }
        }      
    }
    if (deleting)
    {
        way_from_parent = find_way(data, parent);
        if (parent->ptr_arr[0]!=nullptr)
        {
            way_from_nest = find_way(data, parent->ptr_arr[way_from_parent]);
            pom = find_in_nest(data, parent->ptr_arr[way_from_parent]);
        }
        
        if (depth == help_depth + 1 && successor)
        {
            for (int i = 0; i < parent->ptr_arr[way_from_parent]->ptr_arr.size(); i++)
            {
                pom = find_in_nest(data, parent->ptr_arr[way_from_parent]->ptr_arr[i]);
                if (pom != -1)
                {
                    pom = i;
                    break;
                }
            }
            int pom2 = find_in_nest(help_data, parent);
            //case of replaced element being two layer above or not
            if (pom2 != -1)
            {
                for (int i = 0; i < parent->ptr_arr[pom2+1]->ptr_arr.size(); i++)
                {
                    pom = find_in_nest(data, parent->ptr_arr[pom2+1]->ptr_arr[i]);
                    if (pom != -1)
                    {
                        pom = i;
                        break;
                    }
                }
                help_depth ++;
                if(depth == 2)
                {
                    return find_element(data, help_depth, parent, parent->ptr_arr[pom2+1], deleting, right, successor);
                }
                return find_element(data, help_depth, parent->ptr_arr[pom2+1], parent->ptr_arr[pom2+1]->ptr_arr[pom], deleting, right, successor);
            }
            help_depth ++;
            return find_element(data, help_depth, parent->ptr_arr[way_from_parent], parent->ptr_arr[way_from_parent]->ptr_arr[pom], deleting, right, successor);
        } 
        else if (help_depth == depth && depth != 1)
        {
            int pom2;
            for (int i = 0; i < parent->ptr_arr.size(); i++)
            {
                pom = find_in_nest(data, parent->ptr_arr[i]);
                if (pom != -1)
                {
                    pom2 = i;
                    break;
                }
            }
            cut_ith_el(pom, parent->ptr_arr[pom2]);
            return true;
        }
        else if (help_depth == depth && depth == 1)
        {
            pom = find_in_nest (data, parent);
            cut_ith_el(pom, parent);
            return true;
        }
        else
        {
            if(!successor)
            {
                if(help_depth==1)
                {
                    pom = find_in_nest(data, parent);
                    if (pom != -1)
                    {
                        std::unique_ptr<TTFT<T>::element> el = std::move(parent->nest_arr[pom]);
                        cut_ith_el(pom, parent);
                        el = find_successor(pom+1, help_depth, parent, el, false);
                        insert_into_nest(el->get_data(), parent, false);
                        help_depth ++;
                        pom = find_in_nest(el->get_data(), parent);
                        return find_element(data, help_depth, parent, parent->ptr_arr[pom+1], deleting, true, true);
                    }
                    else
                    {
                        help_depth ++;
                        return find_element(data, help_depth, parent, parent->ptr_arr[way_from_parent], deleting, false, false);
                    }
                }
                else
                {
                    if (pom != -1)
                    {
                        std::unique_ptr<TTFT<T>::element> el = std::move(parent->ptr_arr[way_from_parent]->nest_arr[pom]);
                        cut_ith_el(pom, parent->ptr_arr[way_from_parent]);
                        el = find_successor(pom+1, help_depth, parent->ptr_arr[way_from_parent], el, false);
                        insert_into_nest(el->get_data(), parent->ptr_arr[way_from_parent], false);
                        help_depth ++;
                        pom = find_in_nest(el->get_data(), parent->ptr_arr[way_from_parent]);
                        return find_element(data, help_depth, parent->ptr_arr[way_from_parent], parent->ptr_arr[way_from_parent]->ptr_arr[pom+1], deleting, true, true);
                    }
                    else
                    {
                        help_depth ++;
                        return find_element(data, help_depth, parent->ptr_arr[way_from_parent], parent->ptr_arr[way_from_parent]->ptr_arr[way_from_nest], deleting, false, false);
                    }
                }
            }
            else
            {
                pom = find_in_nest(help_data, parent);
                if (pom != -1)
                {
                    //
                    int pom3 = find_in_nest(help_data, parent->ptr_arr[pom+1]);
                    if (pom3 != -1)
                    {
                        way_from_nest = pom3+1;
                    }
                    //
                    else
                    {
                        way_from_nest = find_way(data, parent->ptr_arr[pom+1]);
                    }
                    if (help_depth == 1)
                    {
                        help_depth ++;
                        return find_element(data, help_depth, parent, parent->ptr_arr[pom+1], deleting, true, true);
                    }
                    help_depth ++;
                    return find_element(data, help_depth, parent->ptr_arr[pom+1], parent->ptr_arr[pom+1]->ptr_arr[way_from_nest], deleting, true, true);
                }
                int pom4 = find_in_nest(help_data, parent->ptr_arr[way_from_parent]);
                if (pom4 != -1)
                {
                    help_depth ++;
                    return find_element(data, help_depth, parent->ptr_arr[way_from_parent], parent->ptr_arr[way_from_parent]->ptr_arr[pom4+1], deleting, true, true);
                }
                help_depth ++;
                return find_element(data, help_depth, parent->ptr_arr[way_from_parent], parent->ptr_arr[way_from_parent]->ptr_arr[way_from_nest], deleting, true, true);
            }
        }   
    }    
}
template <class T>
int TTFT<T>::find_in_nest(const T& data, std::unique_ptr<TTFT<T>::nest>& nest_)
{
    for(int i =0; i < nest_->nest_arr.size(); i ++)
    {
        if(nest_->nest_arr[i]->get_data()==data){return i;}
    }
    return (-1);
}

template <class T>
//counted from 0
void TTFT<T>::cut_ith_el(int order, std::unique_ptr<TTFT<T>::nest>& nest_)
{
    bool second_pom_for_deletetion_of_nullptr = false;
    bool pom = false;
    for(int i = 0; i < nest_->number_of_elements; i++)
    {
        if(nest_->nest_arr[nest_->nest_arr.size()-1]==nullptr)
        {
            pom = true;
            nest_->nest_arr.pop_back();
            continue;
        }
        this->stack.push(nest_->nest_arr[nest_->nest_arr.size()-1]->get_data());
        nest_->nest_arr.pop_back();
    }
    for(int i = 0; i < nest_->number_of_elements; i++)
    {
        if(pom)
        {
            pom = false;
            second_pom_for_deletetion_of_nullptr = true;
            continue;
        }
        if(i == order && !second_pom_for_deletetion_of_nullptr)
        {
            this->stack.pop();
            continue;
        }
        nest_->nest_arr.push_back(std::make_unique<TTFT<T>::element>(this->stack.top()));
        this->stack.pop();
    }
    nest_->number_of_elements --;

}

template <class T>
void TTFT<T>::caseII(std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_)
{
    insert_into_nest(parent->ptr_arr[0]->nest_arr[0]->get_data(), parent, false);
    insert_into_nest(parent->ptr_arr[1]->nest_arr[0]->get_data(), parent, false);
    if(parent->ptr_arr[0]->ptr_arr.size() > 0)
    {
        ptr_stack.push(std::move(parent->ptr_arr[1]->ptr_arr[1]));
        ptr_stack.push(std::move(parent->ptr_arr[1]->ptr_arr[0]));
        ptr_stack.push(std::move(parent->ptr_arr[0]->ptr_arr[1]));
        ptr_stack.push(std::move(parent->ptr_arr[0]->ptr_arr[0]));
        parent->ptr_arr.pop_back();
        parent->ptr_arr.pop_back();
        for (int i = 0; i < 4; i++)
        {
            parent->ptr_arr.push_back(std::move(ptr_stack.top()));
            ptr_stack.pop();
        }
        depth --;
        return;
    }
    parent->ptr_arr.pop_back();
    parent->ptr_arr.pop_back();
    depth --;
    return;
}

template<class T>
bool TTFT<T>::is_case_II(std::unique_ptr<TTFT<T>::nest>& parent)
{
    if(parent->ptr_arr[0]->nest_arr.size()==1 && parent->ptr_arr[1]->nest_arr.size()==1 && parent->ptr_arr.size() == 2)
    {
        return true;
    }
    return false;
}

template <class T>
bool TTFT<T>::is_case_III(int pom, std::unique_ptr<TTFT<T>::nest>& parent)
{
    if (parent->ptr_arr.size()>1)
    {
        if (pom == 0)
        {
            if (parent->ptr_arr[pom+1]->nest_arr.size() == 1){return true;}
        }
        else if (pom == parent->ptr_arr.size()-1)
        {
            if (parent->ptr_arr[pom-1]->nest_arr.size() == 1){return true;}
        }
        else
        {
            if (parent->ptr_arr[pom-1]->nest_arr.size() == 1){return true;}
            if (parent->ptr_arr[pom+1]->nest_arr.size() == 1){return true;}
        }  
    }
    return false;
    

}

template <class T>
void TTFT<T>::caseIII(int pom, std::unique_ptr<TTFT<T>::nest>& parent, const T& data)
{
    if (pom > 0){
        if (parent->ptr_arr[pom - 1]->nest_arr.size() == 1){
            merge(pom, pom-1, parent, data);
            return;
        }
    }
    if (parent->ptr_arr[pom + 1]->nest_arr.size() == 1){
        merge(pom, pom+1, parent, data);
        return;
    }

}

template <class T>
void TTFT<T>::merge(int home, int neighbour, std::unique_ptr<TTFT<T>::nest>& parent, const T& data_to_del)
{
    int pom;
    if(home < neighbour)
    {
        pom = home;
    }
    else
    {
        pom = neighbour;
    }
    if (pom == -1)//case of switched el being just above el to delete, so comparison wont work
    {
        pom = find_way(data_to_del, parent);
        if (pom != 0){pom--;}
    }
    insert_into_nest(parent->nest_arr[pom]->get_data(),parent->ptr_arr[home], false);
    insert_into_nest(parent->ptr_arr[neighbour]->nest_arr[0]->get_data(), parent->ptr_arr[home], false);
    if(parent->ptr_arr[0]->ptr_arr.size() > 0 && home < neighbour)
    {
        parent->ptr_arr[home]->ptr_arr.push_back(std::move(parent->ptr_arr[neighbour]->ptr_arr[0]));
        parent->ptr_arr[home]->ptr_arr.push_back(std::move(parent->ptr_arr[neighbour]->ptr_arr[1]));
    }
    if(parent->ptr_arr[0]->ptr_arr.size() > 0 && home > neighbour)
    {
        ptr_stack.push(std::move(parent->ptr_arr[home]->ptr_arr[1]));
        ptr_stack.push(std::move(parent->ptr_arr[home]->ptr_arr[0]));
        parent->ptr_arr[home]->ptr_arr.pop_back();
        parent->ptr_arr[home]->ptr_arr.pop_back();
        parent->ptr_arr[home]->ptr_arr.push_back(std::move(parent->ptr_arr[neighbour]->ptr_arr[0]));
        parent->ptr_arr[home]->ptr_arr.push_back(std::move(parent->ptr_arr[neighbour]->ptr_arr[1]));
        parent->ptr_arr[home]->ptr_arr.push_back(std::move(ptr_stack.top()));
        ptr_stack.pop();
        parent->ptr_arr[home]->ptr_arr.push_back(std::move(ptr_stack.top()));
        ptr_stack.pop();
    }
    del_ith_ptr(neighbour, parent);
    cut_ith_el(pom, parent);
}

template <class T>
void TTFT<T>::insert_ptr_to_nest(int pos, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& input)
{
    int pom = nest_->ptr_arr.size();
    for (int i = 0; i < pom; i++)
    {
        ptr_stack.push(std::move(nest_->ptr_arr[pom-1-i]));
        nest_->ptr_arr.pop_back();
    }
    for (int i = 0; i < pom+1; i++)
    {
        if (i == pos)
        {
            nest_->ptr_arr.push_back(std::move(input));
            continue;
        }
        nest_->ptr_arr.push_back(std::move(ptr_stack.top()));
        ptr_stack.pop();
    }
    return;
}

template <class T>
void TTFT<T>::del_ith_ptr(int pos, std::unique_ptr<TTFT<T>::nest>& nest_)
{
    int pom = nest_->ptr_arr.size();
    for (int i = 0; i < pom; i++)
    {
        ptr_stack.push(std::move(nest_->ptr_arr[pom-1-i]));
        nest_->ptr_arr.pop_back();
    }
    for (int i = 0; i < pom; i++)
    {
        if (i == pos)
        {

            ptr_stack.pop();
            continue;
        }
        nest_->ptr_arr.push_back(std::move(ptr_stack.top()));
        ptr_stack.pop();
    }
    return;
}

template <class T>
std::unique_ptr<typename TTFT<T>::element> TTFT<T>::find_successor(int way, int pom_depth, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::element>& element_, bool turned)
{
    if (pom_depth == depth)
    {
        std::unique_ptr<TTFT<T>::element> pom = std::move(nest_->nest_arr[0]);
        help_data = pom->get_data();
        cut_ith_el(0, nest_);
        insert_into_nest(element_->get_data(), nest_, false);
        return pom;
    }
    pom_depth ++;
    if(turned)
    {
        return find_successor(way, pom_depth, nest_->ptr_arr[0], element_, turned);
    }
    return find_successor(way, pom_depth, nest_->ptr_arr[way], element_, true);
}

template <class T>
bool TTFT<T>::is_in_tree(const T& data, int pom_depth, std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_)
{
    if (depth != pom_depth)
    {
        int way_from_nest = find_way(data, nest_);
        int pom = find_in_nest(data, nest_);
        if (pom != -1)
        {
            std::cout<<"Data are present. "<<std::endl;
            return true;
        }
        else
        {
            pom_depth ++;
            return is_in_tree(data, pom_depth, nest_, nest_->ptr_arr[way_from_nest]);
        }
    }
    else
    {
        int pom = find_in_nest(data, nest_);
        if (pom != -1)
        {
            return true;
        }
        std::cout<<"Data are not present. "<<std::endl;
        return false;
    }
}

template <class T>
void TTFT<T>::is_element_in_tree(const T& data)
{
    is_in_tree(data, 1, main_root, main_root);
    return;
}
