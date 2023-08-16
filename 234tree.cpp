#include "234tree.hpp"
using T = float;

using namespace::std;

ttf_tree::ttf_tree()
{
    main_root = nullptr;
    number_of_elements = 0;
    pom_hnizdo = nullptr;
    parent_of_wanted_hnizdo = nullptr;
    switched_prvek = nullptr;
    pom_grandparent = nullptr;
}

ttf_tree::hnizdo::hnizdo()
    : hnizdo_arr(), left_left(nullptr),
    middle_left(nullptr), middle_right(nullptr),
    right_right(nullptr), middle(nullptr), number_of_nodes(0)
{
    vector<T> hnizdo_arr;
}


void ttf_tree::TREE_INSERT(const T& data)
{

    if (empty())
    {
        main_root = new hnizdo();
        
        main_root -> hnizdo_arr.push_back(new prvek(data));
        main_root -> number_of_nodes += 1;
        this -> depth +=1;
        number_of_elements += 1;
        return;

    }
    else
    {  
        insert_into_subtree(data, main_root, nullptr, false);
        return;
    }   
}

bool ttf_tree::empty()
{
    if (this -> main_root == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}






void ttf_tree:: insert_into_hnizdo(const T& data, hnizdo* hnizdo_)
 {
    if (hnizdo_->hnizdo_arr.size() == 0)
    {

        hnizdo_ -> hnizdo_arr.push_back(new prvek(data));
        hnizdo_->number_of_nodes +=1;
        this->number_of_elements +=1;
        return;
    }

    for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
    {
        
        if( data < hnizdo_->hnizdo_arr[i]->get_data())
        {
            hnizdo_ -> hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin()+ i, new prvek(data));
            hnizdo_->number_of_nodes +=1;
            this->number_of_elements +=1;
            return;
        }

        if(i == hnizdo_->hnizdo_arr.size()-1)
        {
            hnizdo_ -> hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin()+ i + 1, new prvek(data));
            hnizdo_->number_of_nodes +=1;
            this->number_of_elements +=1;
            return;
        }
    }
    
    
 }

void ttf_tree::split(hnizdo* hnizdo_, hnizdo* &parent)
{
    T middle_one = hnizdo_ -> hnizdo_arr[1]->get_data();
    

    //total split with nullptr parent
    if (parent == nullptr)
    {
        
        main_root = new hnizdo;
        insert_into_hnizdo(middle_one, main_root);
        delete hnizdo_->hnizdo_arr[1];
        hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);

        main_root -> right_right = new hnizdo;
        insert_into_hnizdo(hnizdo_->hnizdo_arr[1]->get_data(), main_root->right_right);
        delete hnizdo_->hnizdo_arr[1];
        hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
        
        main_root->left_left = hnizdo_;
        
        if (hnizdo_->left_left != nullptr)
        {
            main_root -> right_right -> right_right = hnizdo_->right_right;
            main_root -> right_right -> left_left = hnizdo_->middle_right;
            hnizdo_ -> right_right = hnizdo_ -> middle_left;
        }
        
        hnizdo_ -> middle_left = nullptr;
        hnizdo_ -> middle_right = nullptr;
        
        this -> depth += 1;
        main_root->number_of_nodes = 1;
        hnizdo_->number_of_nodes = 1;
        main_root->right_right->number_of_nodes = 1;
        //premistěni a vynulovani
        this->pom_hnizdo = main_root;
        this->pom_grandparent = nullptr;
        return;

    }

    
    
    //levej a pravej split s i bez children and middle empty
    if (parent -> middle == nullptr)
    {
        insert_into_hnizdo(middle_one, parent);
        delete hnizdo_->hnizdo_arr[1];
        hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);  
        hnizdo_->number_of_nodes -= 1;

    //pravej split
        if (middle_one > parent->hnizdo_arr[0]->get_data())
        {
            parent -> middle = new hnizdo;
            insert_into_hnizdo(hnizdo_->hnizdo_arr[0]->get_data(), parent->middle);
            delete hnizdo_->hnizdo_arr[0];
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
            hnizdo_->number_of_nodes -= 1;

            if(hnizdo_->left_left != nullptr)
            {
                parent -> middle -> left_left = hnizdo_ -> left_left;
                parent -> middle -> right_right = hnizdo_ -> middle_left;

                hnizdo_ -> left_left = hnizdo_ -> middle_right;
                hnizdo_ -> middle_right = nullptr;
                hnizdo_ -> middle_left = nullptr;
            }
        }
    //levej split
        else if (middle_one < parent->hnizdo_arr[1]->get_data())
        {
            parent -> middle = new hnizdo;
            insert_into_hnizdo(hnizdo_->hnizdo_arr[1]->get_data(), parent->middle);
            //když je to vlevo tak chci hodit do middle to vpravo
            delete hnizdo_->hnizdo_arr[1];
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
            hnizdo_ -> number_of_nodes -= 1;

            if(hnizdo_->left_left != nullptr)
            {
                parent -> middle -> left_left = hnizdo_ -> middle_right;
                parent -> middle -> right_right = hnizdo_ -> right_right;

                hnizdo_ -> right_right = hnizdo_ -> middle_left;
                hnizdo_ -> middle_right = nullptr;
                hnizdo_ -> middle_left = nullptr;
            }
        }
        this->pom_hnizdo = parent;
        return;
    }

        

    insert_into_hnizdo(middle_one, parent);
    delete hnizdo_->hnizdo_arr[1];
    hnizdo_ -> hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
    hnizdo_ -> number_of_nodes -= 1;
//pravej split
    if (middle_one > parent->hnizdo_arr[1]->get_data()) //pokud je plnej middle prvek a nahoru jde prvek zprava
    {
        parent -> middle_left = parent -> middle;
        parent -> middle = nullptr;
        
        parent -> middle_right = new hnizdo;
        insert_into_hnizdo(hnizdo_->hnizdo_arr[0]->get_data(), parent-> middle_right);
        delete hnizdo_->hnizdo_arr[0];
        hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
        hnizdo_ -> number_of_nodes -= 1;

        if (hnizdo_->left_left != nullptr)
        {
            parent -> middle_right -> left_left = hnizdo_ -> left_left;
            parent -> middle_right -> right_right = hnizdo_ -> middle_left;

            hnizdo_ -> left_left = hnizdo_ -> middle_right;
            hnizdo_ -> middle_left = nullptr;
            hnizdo_ -> middle_right = nullptr;
        }
        this->pom_hnizdo = parent;
        return;
    }
//levej split
    if (middle_one < parent->hnizdo_arr[1]->get_data()) 
    {
        
        parent -> middle_right = parent -> middle;
        parent -> middle = nullptr;
        
        parent -> middle_left = new hnizdo;
        insert_into_hnizdo(hnizdo_->hnizdo_arr[1]->get_data(), parent-> middle_left);
        delete hnizdo_->hnizdo_arr[1];
        hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
        hnizdo_ -> number_of_nodes -= 1;

        if (hnizdo_->left_left != nullptr)
        {
            parent -> middle_left -> right_right = hnizdo_ -> right_right;
            parent -> middle_left -> left_left = hnizdo_ -> middle_right;

            hnizdo_ -> right_right = hnizdo_ -> middle_left;
            hnizdo_ -> middle_left = nullptr;
            hnizdo_ -> middle_right = nullptr;
        }
        this->pom_hnizdo = parent;
        return;

    }
//middle split
    if (middle_one > parent->hnizdo_arr[0]->get_data() && middle_one < parent->hnizdo_arr[2]->get_data()) 
    {
        parent -> middle_left = new hnizdo;
        insert_into_hnizdo(parent -> middle->hnizdo_arr[0] ->get_data(), parent->middle_left);
        delete hnizdo_->hnizdo_arr[0];
        hnizdo_ -> hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
        hnizdo_->number_of_nodes -= 1;
        //prvne levej pak pravej
        parent -> middle_right = new hnizdo;
        insert_into_hnizdo(parent -> middle->hnizdo_arr[0]->get_data(), parent->middle_right);
        delete hnizdo_->hnizdo_arr[0];
        hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
        hnizdo_->number_of_nodes -=1;
        
        


        if (hnizdo_->left_left != nullptr)
        {
            parent -> middle_left -> left_left = hnizdo_ -> left_left;
            parent -> middle_left -> right_right = hnizdo_ -> middle_left;


            parent -> middle_right -> left_left = hnizdo_ -> middle_right;
            parent -> middle_right -> right_right = hnizdo_ -> right_right;

            hnizdo_ -> left_left = nullptr;
            hnizdo_ -> middle_left = nullptr;
            hnizdo_ -> middle_right = nullptr;
            hnizdo_ -> right_right = nullptr;

        }
        delete parent -> middle;
        parent -> middle = nullptr;

        this->pom_hnizdo = parent;


        return;
    }
    

    

    

}

void ttf_tree::insert_into_subtree(const T& data, hnizdo* hnizdo_, hnizdo* parent, bool been_split)
{

    for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
    {
        if (hnizdo_->hnizdo_arr[i]->get_data() == data)
        {
            std::cout << "data are already in the tree" << endl;
            return;
        }
    }
    
    if (hnizdo_->number_of_nodes == 3 && been_split == false)
    {
        this->pom_hnizdo = hnizdo_;
        
        split(hnizdo_, parent);
        
        hnizdo_ = this->pom_hnizdo;
        
        insert_into_subtree(data, hnizdo_, this->pom_grandparent, true);
        return;

    }
    

    if (hnizdo_->left_left == nullptr)
    {
        insert_into_hnizdo(data, hnizdo_);
        //mělo by stačit, protože vzhledem k vyvatenosti stromu
        //by měl nullptr na levo == nullptr všude
        return;
    }

    this->pom_grandparent = parent;
    for (int a = 0; a < hnizdo_->hnizdo_arr.size(); a++)
    {
        
        if (hnizdo_->number_of_nodes == 3)
        {
            if (data < hnizdo_->hnizdo_arr[a]->get_data())
            {
                if (a == 0)
                {
                    return insert_into_subtree(data, hnizdo_->left_left, hnizdo_, false);
                }
                else if (a==1)
                {
                    return insert_into_subtree(data, hnizdo_->middle_left, hnizdo_, false);
                }
                else if (a==2)
                {
                    return insert_into_subtree(data, hnizdo_->middle_right, hnizdo_, false);
                }
            }
        }
        if (hnizdo_->number_of_nodes == 2)
        {
            if (data < hnizdo_->hnizdo_arr[a]->get_data())
            {
                if (a==0)
                {
                    return insert_into_subtree(data, hnizdo_->left_left, hnizdo_, false);
                }
                else if (a==1)
                {
                    return insert_into_subtree(data, hnizdo_->middle, hnizdo_, false);
                }

            }
            
        }
        if (hnizdo_->number_of_nodes == 1)
        {
            if (data < hnizdo_->hnizdo_arr[a]->get_data())
            {
                if (a==0)
                {
                    return insert_into_subtree(data, hnizdo_->left_left, hnizdo_, false);
                }
            }
            
        }
    }
    if (hnizdo_->number_of_nodes == 3)
    {
        return insert_into_subtree(data, hnizdo_->right_right, hnizdo_, false);
    }
    if (hnizdo_->number_of_nodes == 2)
    {
        return insert_into_subtree(data, hnizdo_->right_right, hnizdo_, false);
    }
    if (hnizdo_->number_of_nodes == 1)
    {
        return insert_into_subtree(data, hnizdo_->right_right, hnizdo_, false);
    }
    

}

void ttf_tree::TREEPRINT()
{
    for (int i = 0; i < this -> depth; i++)
    {
    printlv(main_root, nullptr, 4-i, i, 0);
    std::cout << endl;
    }
}

void ttf_tree::printlv(hnizdo* hnizdo_, hnizdo* grandparent, int counter_for_grandparent, int n, int pom)
{   
    if (counter_for_grandparent == 2)
    {
        grandparent = hnizdo_;
        counter_for_grandparent = 0;
    }

    counter_for_grandparent += 1;

    if (hnizdo_ == nullptr && n != pom && grandparent != nullptr)
    {
        
        std::cout << "X * 5";
        std::cout << std::setw(1) << "";
    
        std::cout << "//////";
        return;
    }

    else if (hnizdo_ == nullptr && n != pom)
    {
        
        std::cout << "X * 5^"<<(-1+n);
        std::cout << std::setw(1) << "";
    
        std::cout << "//////";
        return;
    }

    if (hnizdo_ == nullptr)
    {
        std::cout << "X";
        std::cout << std::setw(1) << "";
        return;
    }
    else if (pom == n && hnizdo_ != nullptr)
    {
        for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i ++)
        {
            T data = hnizdo_ -> hnizdo_arr[i]->get_data();
            std::cout << data << ",";
        }
        std::cout << "K";
        std::cout << std::setw(1) << "";
        return;
    }
    

    
    pom += 1;
//ten print je blbe musím vymyslet aby se to printovalo vsechno zaraz
    printlv(hnizdo_->left_left, grandparent, counter_for_grandparent, n, pom);
    printlv(hnizdo_->middle_left, grandparent, counter_for_grandparent, n, pom);
    printlv(hnizdo_->middle, grandparent, counter_for_grandparent,n, pom);
    printlv(hnizdo_->middle_right, grandparent, counter_for_grandparent, n, pom);
    printlv(hnizdo_->right_right, grandparent, counter_for_grandparent, n, pom);
    std::cout <<"///";
    return;

}

ttf_tree::~ttf_tree()
{
    clear();
}

void ttf_tree::clear()
{
    if (empty())
    {
        return;
    }
    remove_all(this->main_root, 0);
    main_root = nullptr;//po smazaní jsem tam neměl automaticky nullptr

}

void ttf_tree::get_depth()
{
    cout<<this->depth<<endl;
}

void ttf_tree::remove_all(hnizdo* hnizdo_, int count)
{
    std::cout << "lvl " << count << endl;
    if (hnizdo_ == nullptr)
    {
        return;
    }
    count +=1;

    remove_all(hnizdo_->left_left, count);
    remove_all(hnizdo_->middle_left, count);
    remove_all(hnizdo_->middle, count);
    remove_all(hnizdo_->middle_right, count);
    remove_all(hnizdo_->right_right, count);

    
    ttf_tree::number_of_elements = ttf_tree::number_of_elements - hnizdo_ -> number_of_nodes;

    
    delete hnizdo_;
    return;
}

ttf_tree::prvek* ttf_tree::find_prvek (const T& data, hnizdo* hnizdo_)
{
    if (empty())
    {
        return nullptr;
    }

    for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
    {
        if (hnizdo_->hnizdo_arr[i] ->get_data() == data)
        {
            return hnizdo_->hnizdo_arr[i];
        }
    }

    if (hnizdo_->left_left == nullptr)
    {
        cout << "Prvek neni v databazi"<< endl;
        return nullptr;
    }

    for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
    {
        if (hnizdo_->hnizdo_arr[i] ->get_data() == data)
        {
            return hnizdo_->hnizdo_arr[i];
        }

        if (data < hnizdo_->hnizdo_arr[i]->get_data() && i == 0)
        {
            return find_prvek(data, hnizdo_->left_left);
        }

        if (data < hnizdo_->hnizdo_arr[i]->get_data() && hnizdo_->middle != nullptr)
        {
            return find_prvek(data, hnizdo_->middle);
        }

        if (data < hnizdo_->hnizdo_arr[i]->get_data() && i == 1)
        {
            return find_prvek(data, hnizdo_->middle_left);
        }

        if (data < hnizdo_->hnizdo_arr[i]->get_data() && i == 2)
        {
            return find_prvek(data, hnizdo_->middle_right);
        }

        return find_prvek (data, hnizdo_->right_right);
    }
}


///////

T ttf_tree::prvek::get_data() const
{
    return this->data;
}

ttf_tree::prvek::prvek(T data)
        :data(data)
        {

        }

ttf_tree::hnizdo* ttf_tree::find_hnizdo_with_prvek_for_del(const T& data, hnizdo* hnizdo_, hnizdo* parent)
{
    if (empty())
    {
        return nullptr;
    }

    if (hnizdo_ == nullptr)
    {
        std::cout << "Prvek neni v databazi"<< endl;
        return nullptr;
    }

    for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
    {
        if (hnizdo_->hnizdo_arr[i] ->get_data() == data)
        {
            return hnizdo_;
        }
    }

    if (hnizdo_->left_left != nullptr && hnizdo_ ->number_of_nodes == 1)
    {
        
        this->pom_hnizdo = hnizdo_;
        reorganize_the_tree(hnizdo_, parent);
        hnizdo_ = this->pom_hnizdo;
        //kvůli merge, protoze si mazu hnizda pod zadkem
        
    }
    
    
    for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
    {

        if (data < hnizdo_->hnizdo_arr[i]->get_data() && i == 0)
        {
            if(hnizdo_->left_left != nullptr)
            {
                this->parent_of_wanted_hnizdo = hnizdo_;    
            }
            
            return find_hnizdo_with_prvek_for_del(data, hnizdo_->left_left, hnizdo_);
        }

        if (data < hnizdo_->hnizdo_arr[i]->get_data() && hnizdo_->middle != nullptr)
        {
            if(hnizdo_->left_left != nullptr)
            {
                this->parent_of_wanted_hnizdo = hnizdo_;    
            }
            return find_hnizdo_with_prvek_for_del(data, hnizdo_->middle,hnizdo_);
        }

        if (data < hnizdo_->hnizdo_arr[i]->get_data() && i == 1)
        {
            if(hnizdo_->left_left != nullptr)
            {
                this->parent_of_wanted_hnizdo = hnizdo_;    
            }
            return find_hnizdo_with_prvek_for_del(data, hnizdo_->middle_left, hnizdo_);
        }

        if (data < hnizdo_->hnizdo_arr[i]->get_data() && i == 2)
        {
            if(hnizdo_->left_left != nullptr)
            {
                this->parent_of_wanted_hnizdo = hnizdo_;    
            }
            return find_hnizdo_with_prvek_for_del(data, hnizdo_->middle_right, hnizdo_);
        }

        
    }
    if(hnizdo_->left_left != nullptr)
    {
        this->parent_of_wanted_hnizdo = hnizdo_;    
    }
    return find_hnizdo_with_prvek_for_del (data, hnizdo_->right_right, hnizdo_);
}

//rotace se spusti automaticky na hnizdo s jednim prvkem
//upraveno pro strom i s children
//asi už dobrá
void ttf_tree::rotation_for_one_node_parent(hnizdo* hnizdo_, hnizdo* parent)
{
    
    
    if (parent->left_left == hnizdo_)
    {
        //anticlockwise rotation
        hnizdo_->hnizdo_arr.push_back(parent->hnizdo_arr[0]);
        parent -> hnizdo_arr.push_back(parent->right_right->hnizdo_arr[0]);
        hnizdo_->number_of_nodes+=1;
        parent->right_right->number_of_nodes-=1;

        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin());

        
        parent->right_right->hnizdo_arr.erase(parent->right_right->hnizdo_arr.begin());

        if (hnizdo_ ->left_left != nullptr && parent->right_right->number_of_nodes == 1 && hnizdo_->number_of_nodes == 2)
        {
            hnizdo_->middle = hnizdo_->right_right;
            hnizdo_->right_right = parent->right_right->left_left;
           
            parent->right_right->left_left = parent->right_right->middle;
            parent->right_right->middle = nullptr;
        }

        else if (hnizdo_ ->left_left != nullptr && parent->right_right->number_of_nodes == 2 && hnizdo_->number_of_nodes == 2)
        {
            hnizdo_->middle = hnizdo_->right_right;
            hnizdo_->right_right = parent->right_right->left_left;

            parent->right_right->left_left = parent->right_right->middle_left;
            parent->right_right->middle = parent->right_right->middle_right;
            parent->right_right->middle_left = nullptr;
            parent->right_right->middle_right = nullptr;
        }


        
        return;


    }

    else if (parent -> right_right == hnizdo_)
    {
        
        //clockwise rotation
        
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[0]);
       
        parent -> hnizdo_arr.insert(parent->hnizdo_arr.begin(), parent->left_left->hnizdo_arr[parent->left_left->hnizdo_arr.size()-1]);
        hnizdo_->number_of_nodes+=1;
        parent->left_left->number_of_nodes-=1;

        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);

        
        parent->left_left->hnizdo_arr.erase(parent->left_left->hnizdo_arr.begin()+parent->left_left->hnizdo_arr.size()-1);

        if (hnizdo_ ->left_left != nullptr && parent->left_left->number_of_nodes == 1 && hnizdo_->number_of_nodes == 2)
        {
            hnizdo_->middle = hnizdo_->left_left;
            hnizdo_->left_left = parent->left_left->right_right;
           
            parent->left_left->right_right = parent->left_left->middle;
            parent->left_left->middle = nullptr;
        }

        else if (hnizdo_ ->left_left != nullptr && parent->left_left->number_of_nodes == 2 && hnizdo_->number_of_nodes == 2)
        {
            hnizdo_->middle = hnizdo_->left_left;
            hnizdo_->left_left = parent->left_left->right_right;

            parent->left_left->right_right = parent->left_left->middle_right;
            parent->left_left->middle = parent->left_left->middle_left;
            parent->left_left->middle_right = nullptr;
            parent->left_left->middle_left = nullptr;
        }

        
        return;
    }
}

//what type 0 - vlevo jeden prvek provedena rotace anticlockwise
//1 - middle podle poctu v sousednich hnizdech clockwise ci anticlockwise
//2 - vpravo jeden prvek, provedena clockwise
void ttf_tree::rotation_for_two_node_parent(hnizdo* hnizdo_, hnizdo* parent, int what_type)
{
    if (what_type == 0)
    {
        hnizdo_ -> hnizdo_arr.push_back(parent->hnizdo_arr[0]);
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin());

        parent->left_left->number_of_nodes+=1;
        parent->middle->number_of_nodes-=1;

        parent->hnizdo_arr.insert(parent->hnizdo_arr.begin(),parent->middle->hnizdo_arr[0]);
        parent->middle->hnizdo_arr.erase(parent->middle->hnizdo_arr.begin());

        if (hnizdo_ -> left_left != nullptr)
        {
            if (parent->middle->number_of_nodes == 1)
            {
                hnizdo_ -> middle = hnizdo_ -> right_right;
                hnizdo_->right_right = parent->middle->left_left;

                parent->middle->left_left = parent->middle->middle;
                parent->middle->middle = nullptr;
            }

            else if (parent->middle->number_of_nodes == 2)
            {
                hnizdo_ -> middle = hnizdo_ -> right_right;
                hnizdo_->right_right = parent->middle->left_left;

                parent->middle->left_left = parent->middle->middle_left;
                parent->middle->middle = parent->middle->middle_right;
                parent->middle-> middle_left = nullptr;
                parent->middle->middle_right = nullptr;
            }
        }
        return;
    }

    if (what_type == 1)
    {
        if (parent->left_left ->number_of_nodes >= 2)
        {
            hnizdo_ -> hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[0]);
            parent->hnizdo_arr.erase(parent->hnizdo_arr.begin());

            parent->middle->number_of_nodes+=1;
            parent->left_left->number_of_nodes-=1;

            parent->hnizdo_arr.insert(parent->hnizdo_arr.begin(),parent->left_left->hnizdo_arr[parent->left_left->hnizdo_arr.size()-1]);
            parent->left_left->hnizdo_arr.erase(parent->left_left->hnizdo_arr.begin()+parent->left_left->hnizdo_arr.size()-1);

            if (hnizdo_->left_left != nullptr)
            {
                if (parent->left_left->number_of_nodes == 1)
                {
                    hnizdo_ -> middle = hnizdo_ -> left_left;
                    hnizdo_->left_left = parent->left_left->right_right;

                    parent->left_left->right_right = parent->left_left->middle;
                    parent->left_left->middle = nullptr;
                }

                else if (parent->left_left->number_of_nodes == 2)
                {
                    hnizdo_ -> middle = hnizdo_ -> left_left;
                    hnizdo_->left_left = parent->left_left->right_right;

                    parent->left_left->right_right = parent->left_left->middle_right;
                    parent->left_left->middle = parent->left_left->middle_left;
                    parent->middle_left = nullptr;
                    parent->middle_right = nullptr;
                }
            }
            
            return;
        }

        if (parent->right_right ->number_of_nodes >= 2)
        {
            hnizdo_ -> hnizdo_arr.push_back(parent->hnizdo_arr[1]);
            parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);

            parent->middle->number_of_nodes+=1;
            parent->right_right->number_of_nodes-=1;

            parent->hnizdo_arr.push_back(parent->right_right->hnizdo_arr[0]);
            parent->right_right->hnizdo_arr.erase(parent->right_right->hnizdo_arr.begin());

            if (hnizdo_->left_left != nullptr)
            {
                if (parent->right_right->number_of_nodes == 1)
                {
                    hnizdo_ -> middle = hnizdo_ -> right_right;
                    hnizdo_->right_right = parent->right_right->left_left;

                    parent->right_right->left_left = parent->right_right->middle;
                    parent->right_right->middle = nullptr;
                }

                else if (parent->right_right->number_of_nodes == 2)
                {
                    hnizdo_ -> middle = hnizdo_ -> right_right;
                    hnizdo_->right_right = parent->right_right->left_left;

                    parent->right_right->left_left = parent->right_right->middle_left;
                    parent->right_right->middle = parent->right_right->middle_right;
                    parent->right_right->middle_left = nullptr;
                    parent->right_right->middle_right = nullptr;
                }
            }
            
            return;
        }
    }

    if (what_type == 2)
    {
        hnizdo_ -> hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[1]);
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);

        parent->right_right->number_of_nodes+=1;
        parent->middle->number_of_nodes-=1;

        parent->hnizdo_arr.insert(parent->hnizdo_arr.begin()+1,parent->middle->hnizdo_arr[parent->middle->hnizdo_arr.size()-1]);
        parent->middle->hnizdo_arr.erase(parent->middle->hnizdo_arr.begin()+parent->middle->hnizdo_arr.size()-1);

        if (hnizdo_->left_left != nullptr)
        {
            if (parent->middle->number_of_nodes == 1)
            {
                hnizdo_ -> middle = hnizdo_ -> left_left;
                hnizdo_->left_left = parent->middle->right_right;

                parent->middle->right_right = parent->middle->middle;
                parent->middle->middle = nullptr;
            }

            else if (parent->middle->number_of_nodes == 2)
            {
                hnizdo_ -> middle = hnizdo_ -> left_left;
                hnizdo_->left_left = parent->middle->right_right;

                parent->middle->right_right = parent->middle->middle_right;
                parent->middle->middle = parent->middle->middle_left;
                parent->middle->middle_left = nullptr;
                parent->middle->middle_right = nullptr;
            }
        }
        
        return;
    }
}

//what_type 0 - left left
//1 - middle 
//2 - right right
void ttf_tree::merge_for_two_node_parent (hnizdo* hnizdo_, hnizdo* parent, int what_type)
{
    if (what_type == 0)
    {
        hnizdo_->hnizdo_arr.push_back(parent->hnizdo_arr[0]);
        hnizdo_->hnizdo_arr.push_back(parent->middle->hnizdo_arr[0]);
        
        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin());
        parent->middle->hnizdo_arr.erase(parent->middle->hnizdo_arr.begin());
        
        if (hnizdo_->left_left != nullptr)
        {
            hnizdo_ -> middle_left = hnizdo_->right_right;
            hnizdo_-> middle_right = parent->middle -> left_left;
            hnizdo_ -> right_right = parent->middle->right_right;
            
        }
        delete parent -> middle;
        hnizdo_->number_of_nodes = 3;
        parent->middle = nullptr;
        return;
    }

    if (what_type == 1)
    {
               
        if (parent->left_left->number_of_nodes == 1)
        {
            
            parent->left_left->hnizdo_arr.push_back(parent->hnizdo_arr[0]);
            parent->left_left->hnizdo_arr.push_back(parent->middle->hnizdo_arr[0]);
            
            parent->hnizdo_arr.erase(parent->hnizdo_arr.begin());
            hnizdo_->hnizdo_arr.erase(parent->middle->hnizdo_arr.begin());
            
            if (hnizdo_->left_left != nullptr)
            {
                
                parent->left_left -> middle_left = parent->left_left -> right_right;
                parent->left_left -> middle_right = hnizdo_ -> left_left;
                parent->left_left -> right_right = hnizdo_->right_right;
               
            }
            parent->left_left->number_of_nodes = 3;
            this->pom_hnizdo = parent->left_left;
            delete parent->middle;
            parent->middle = nullptr;
            return;
        }

        else if (parent->right_right ->number_of_nodes == 1)
        {
            hnizdo_->hnizdo_arr.push_back(parent->hnizdo_arr[1]);
            hnizdo_->hnizdo_arr.push_back(parent->right_right->hnizdo_arr[0]);
            
            
            parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);
            parent->right_right->hnizdo_arr.erase(parent->middle->hnizdo_arr.begin());
            
            if (hnizdo_ ->left_left != nullptr)
            {
                hnizdo_ -> middle_left = hnizdo_ -> right_right;
                hnizdo_ -> middle_right = parent->right_right -> left_left;
                hnizdo_ -> right_right = parent->right_right->right_right;
                
                parent->right_right = hnizdo_;
            }
            
            hnizdo_ -> number_of_nodes = 3;
            delete parent->middle;
            parent->middle = nullptr;
            return;
        }
        
    }

    if (what_type == 2)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[1]);
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->middle->hnizdo_arr[0]);
        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);
        parent->middle->hnizdo_arr.erase(parent->middle->hnizdo_arr.begin());
        
        if (hnizdo_->left_left != nullptr)
        {
            hnizdo_ -> middle_right = hnizdo_->left_left;
            hnizdo_-> middle_left = parent->middle -> right_right;
            hnizdo_ -> left_left = parent->middle->left_left;
            
        }
        hnizdo_->number_of_nodes = 3;
        delete parent->middle;
        parent->middle = nullptr;
        return;
    }
}

//what_type 0-left left
//1 - middle left
//2 - middle right
//3 - right right
void ttf_tree::merge_for_three_node_parent(hnizdo* hnizdo_, hnizdo* parent, int what_type)
{
    if (what_type == 0)
    {
        hnizdo_->hnizdo_arr.push_back(parent->hnizdo_arr[0]);
        hnizdo_->hnizdo_arr.push_back(parent->middle_left->hnizdo_arr[0]);
        
        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin());
        

        
        parent->middle_left->hnizdo_arr.erase(parent->middle_left->hnizdo_arr.begin());
        
        parent->middle = parent->middle_right;
        parent->left_left->number_of_nodes = 3;

        if (hnizdo_->left_left != nullptr)
        {
            hnizdo_->middle_left = hnizdo_->right_right;
            hnizdo_->middle_right = parent -> middle_left->left_left;
            hnizdo_->right_right = parent->middle_left->right_right;
            
            delete parent->middle_left;
            parent->middle_left=nullptr;
            parent->middle_right = nullptr;
        }
        else
        {
            delete parent->middle_left;
            parent -> middle_left = nullptr;
            parent->middle_right= nullptr;
        }
        return ;
        
    }

    else if (what_type == 1)
    {
        hnizdo_->hnizdo_arr.push_back(parent->hnizdo_arr[1]);
        hnizdo_->hnizdo_arr.push_back(parent->middle_right->hnizdo_arr[0]);
        
        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);
        
        parent->middle_right->hnizdo_arr.erase(parent->middle_right->hnizdo_arr.begin());

        parent->middle = parent->middle_left;
        parent->middle->number_of_nodes = 3;
        hnizdo_ = parent -> middle;

        if (hnizdo_->left_left != nullptr)
        {
            
            hnizdo_->middle_left = hnizdo_->right_right;
            hnizdo_->middle_right = parent->middle_right->left_left;
            hnizdo_->right_right = parent -> middle_right->right_right;
            delete parent->middle_right;
            parent->middle_left = nullptr;
            parent->middle_right = nullptr;
        }
        else
        {
            delete parent->middle_right;
            parent -> middle_left = nullptr;
            parent->middle_right= nullptr;
        }
        return;
    }

    else if (what_type == 2)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[1]);
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->middle_left->hnizdo_arr[0]);
        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);
        parent->middle_left->hnizdo_arr.erase(parent->middle_left->hnizdo_arr.begin());

        
        parent->middle = parent->middle_right;
        parent->middle->number_of_nodes = 3;
        hnizdo_ = parent->middle;

        if (hnizdo_->left_left != nullptr)
        {
            hnizdo_->middle_right = hnizdo_->left_left;
            hnizdo_->left_left = parent->middle_left->left_left;
            hnizdo_->middle_left = parent -> middle_left->right_right;
            
            
            delete parent->middle_left;
            parent->middle_left=nullptr;
            parent->middle_right = nullptr;
        }
        else
        {
            delete parent->middle_left;
            parent -> middle_left = nullptr;
            parent->middle_right= nullptr;
        }
        return;

        
    }

    else if (what_type == 3)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[2]);
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->middle_right->hnizdo_arr[0]);
        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+2);
        

        parent->middle_right->hnizdo_arr.erase(parent->middle_right->hnizdo_arr.begin());

        parent->middle = parent->middle_left;

        parent->right_right->number_of_nodes=3;

        if (hnizdo_->left_left != nullptr)
        {
            hnizdo_->middle_left = parent -> middle_right->right_right;
            hnizdo_->middle_right = hnizdo_->left_left;
            hnizdo_->left_left = parent->middle_right->left_left;
            delete parent->middle_right;
            parent->middle_left=nullptr;
            parent->middle_right = nullptr;
        }
        else
        {
            delete parent->middle_right;
            parent -> middle_left = nullptr;
            parent->middle_right= nullptr;
        }
        return;

        
    }

}

//5 - chci mazat right right and middle right >= 2
//4 - chci mazat middle right and right right >= 2
//3 - chci mazat middle right and middle left >=2
//2 - chci mazat middle left and middle right >= 2
//1 - chci mazat middle left and left left >= 2
//0 - chci mazat left left and middle left >= 2
void ttf_tree::rotation_for_three_node_parent(hnizdo* hnizdo_, hnizdo* parent, int what_type)
{
    if (what_type == 5)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[2]);
        
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+2);

        parent->hnizdo_arr.insert(parent->hnizdo_arr.begin()+2, parent->middle_right->hnizdo_arr[parent->middle_right->hnizdo_arr.size()-1]);
        
        parent->middle_right->hnizdo_arr.erase(parent->middle_right->hnizdo_arr.begin() + parent->middle_right->hnizdo_arr.size()-1);

        hnizdo_->number_of_nodes+=1;
        parent->middle_right->number_of_nodes-=1;

        if (hnizdo_ -> left_left != nullptr)
        {
            if (parent->middle_right->number_of_nodes == 1)
            {
                hnizdo_-> middle = hnizdo_->left_left;
                hnizdo_->left_left = parent->middle_right->right_right;
                parent->middle_right->right_right = parent->middle_right->middle;
                parent->middle_right->middle = nullptr;
            }
            else if (parent->middle_right->number_of_nodes == 2)
            {
                hnizdo_->middle = hnizdo_->left_left;
                hnizdo_->left_left = parent -> middle_right -> right_right;
                parent->middle_right->right_right = parent->middle_right->middle_right;
                parent->middle_right->middle = parent -> middle_right->middle_left;
                parent->middle_right->middle_left = nullptr;
                parent -> middle_right -> middle_right = nullptr;
            }
        }
        return;
    }

    else if (what_type == 4)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin()+1, parent->hnizdo_arr[2]);
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+2);

        parent->hnizdo_arr.insert(parent->hnizdo_arr.begin()+2, parent->right_right->hnizdo_arr[0]);
        parent->right_right->hnizdo_arr.erase(parent->right_right->hnizdo_arr.begin());

        hnizdo_->number_of_nodes+=1;
        parent->right_right->number_of_nodes-=1;

        if (hnizdo_ -> left_left != nullptr)
        {
            if (parent->right_right->number_of_nodes == 1)
            {
                hnizdo_-> middle = hnizdo_->right_right;
                hnizdo_->right_right = parent->right_right->left_left;
                parent->right_right->left_left = parent->right_right->middle;
                parent->right_right->middle = nullptr;
            }
            else if (parent->right_right->number_of_nodes == 2)
            {
                hnizdo_->middle = hnizdo_->right_right;
                hnizdo_->right_right = parent -> right_right -> left_left;
                parent->right_right->left_left = parent->right_right->middle_left;
                parent->right_right->middle = parent -> right_right->middle_right;
                parent->right_right->middle_left = nullptr;
                parent -> right_right -> middle_right = nullptr;
            }
        }
        return;
    }

    else if (what_type == 3)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[1]);
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);

        parent->hnizdo_arr.insert(parent->hnizdo_arr.begin()+1, parent->middle_left->hnizdo_arr[parent->middle_left->hnizdo_arr.size()-1]);
        parent->middle_left->hnizdo_arr.erase(parent->middle_left->hnizdo_arr.begin()+parent->middle_left->hnizdo_arr.size()-1);

        hnizdo_->number_of_nodes+=1;
        parent->middle_left->number_of_nodes-=1;

        if (hnizdo_ -> left_left != nullptr)
        {
            if (parent->middle_left->number_of_nodes == 1)
            {
                hnizdo_-> middle = hnizdo_->left_left;
                hnizdo_->left_left = parent->middle_left->right_right;
                parent->middle_left->right_right = parent->middle_left->middle;
                parent->middle_left->middle = nullptr;
            }
            else if (parent->middle_left->number_of_nodes == 2)
            {
                hnizdo_->middle = hnizdo_->left_left;
                hnizdo_->left_left = parent -> middle_left -> right_right;
                parent->middle_left->right_right = parent->middle_left->middle_right;
                parent->middle_left->middle = parent -> middle_left->middle_left;
                parent->middle_left->middle_left = nullptr;
                parent -> middle_left -> middle_right = nullptr;
            }
        }
        return;
    }

    else if (what_type == 2)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin()+1, parent->hnizdo_arr[1]);
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);

        parent->hnizdo_arr.insert(parent->hnizdo_arr.begin()+1, parent->middle_right->hnizdo_arr[0]);
        parent->middle_right->hnizdo_arr.erase(parent->middle_right->hnizdo_arr.begin());

        hnizdo_->number_of_nodes+=1;
        parent->middle_right->number_of_nodes-=1;

        if (hnizdo_ -> left_left != nullptr)
        {
            if (parent->middle_right->number_of_nodes == 1)
            {
                hnizdo_-> middle = hnizdo_->right_right;
                hnizdo_->right_right = parent->middle_right->left_left;
                parent->middle_right->left_left = parent->middle_right->middle;
                parent->middle_right->middle = nullptr;
            }
            else if (parent->middle_right->number_of_nodes == 2)
            {
                hnizdo_->middle = hnizdo_->right_right;
                hnizdo_->right_right = parent -> middle_right -> left_left;
                parent->middle_right->left_left = parent->middle_right->middle_left;
                parent->middle_right->middle = parent -> middle_right->middle_right;
                parent->middle_left->middle_left = nullptr;
                parent -> middle_left -> middle_right = nullptr;
            }
        }
        return;
    }

    else if (what_type == 1)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin(), parent->hnizdo_arr[0]);
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin());

        parent->hnizdo_arr.insert(parent->hnizdo_arr.begin(), parent->left_left->hnizdo_arr[parent->left_left->hnizdo_arr.size()-1]);
        parent->left_left->hnizdo_arr.erase(parent->left_left->hnizdo_arr.begin()+parent->left_left->hnizdo_arr.size()-1);

        hnizdo_->number_of_nodes+=1;
        parent->left_left->number_of_nodes-=1;

        if (hnizdo_ -> left_left != nullptr)
        {
            if (parent->left_left->number_of_nodes == 1)
            {
                hnizdo_-> middle = hnizdo_->left_left;
                hnizdo_->left_left = parent->left_left->right_right;
                parent->left_left->right_right = parent->left_left->middle;
                parent->left_left->middle = nullptr;
            }
            else if (parent->left_left->number_of_nodes == 2)
            {
                hnizdo_->middle = hnizdo_->left_left;
                hnizdo_->left_left = parent -> left_left -> right_right;
                parent->left_left->right_right = parent->left_left->middle_right;
                parent->left_left->middle = parent -> left_left->middle_left;
                parent->left_left->middle_left = nullptr;
                parent -> left_left -> middle_right = nullptr;
            }
        }
        return;
    }

    else if (what_type == 0)
    {
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin()+1, parent->hnizdo_arr[0]);
        parent->hnizdo_arr.erase(parent->hnizdo_arr.begin());

        parent->hnizdo_arr.insert(parent->hnizdo_arr.begin(), parent->middle_left->hnizdo_arr[0]);
        parent->middle_left->hnizdo_arr.erase(parent->middle_left->hnizdo_arr.begin());

        hnizdo_->number_of_nodes+=1;
        parent->middle_left->number_of_nodes-=1;

        if (hnizdo_ -> left_left != nullptr)
        {
            if (parent->middle_left->number_of_nodes == 1)
            {
                hnizdo_-> middle = hnizdo_->right_right;
                hnizdo_->right_right = parent->middle_left->left_left;
                parent->middle_left->left_left = parent->middle_left->middle;
                parent->middle_left->middle = nullptr;
            }
            else if (parent->middle_left->number_of_nodes == 2)
            {
                hnizdo_->middle = hnizdo_->right_right;
                hnizdo_->right_right = parent -> middle_left -> left_left;
                parent->middle_left->left_left = parent->middle_left->middle_left;
                parent->middle_left->middle = parent -> middle_left->middle_right;
                parent->middle_left->middle_left = nullptr;
                parent -> middle_left -> middle_right = nullptr;
            }
        }
        return;
    }
    
}

void ttf_tree::merge_with_with_one_node_parent (hnizdo* hnizdo_, hnizdo* parent)
{
    parent->hnizdo_arr.insert(parent->hnizdo_arr.begin(), parent->left_left->hnizdo_arr[0]);
    parent->hnizdo_arr.push_back(parent->right_right->hnizdo_arr[0]);
    
    parent->left_left->hnizdo_arr.erase(parent->left_left->hnizdo_arr.begin());
    parent->right_right->hnizdo_arr.erase(parent->right_right->hnizdo_arr.begin());

    if (hnizdo_ -> left_left != nullptr)
    {
        parent->middle_left = parent->left_left->right_right;
        hnizdo* pom = parent -> left_left;
        parent->left_left = parent->left_left->left_left;
        parent->middle_right = parent->right_right->left_left;
        delete pom;

        pom = parent ->right_right;
        parent->right_right = parent->right_right->right_right;
        delete pom;
        
        
    }
    else
    {
        delete parent->left_left;
        delete parent->right_right;
        parent->left_left = nullptr;
        parent->right_right = nullptr;
    }
    this->pom_hnizdo = parent;
    
    this->depth -= 1;
    parent->number_of_nodes = 3;
    return; //nahazu do parenta a zkratim

}

ttf_tree::hnizdo* ttf_tree::find_hnizdo_with_prvek_after_switch (prvek* prvek_, hnizdo* hnizdo_, hnizdo* parent, bool first_turn_right)
{

    if (hnizdo_ -> left_left == nullptr)
    {
        this->parent_of_wanted_hnizdo = parent;
        
        return hnizdo_;
    }

    
    int type_of_change = 0;
    this->pom_hnizdo = hnizdo_;
    if (hnizdo_->number_of_nodes == 1)
    {
        type_of_change = reorganize_the_tree(hnizdo_, parent);
    }
    
    hnizdo_ = this->pom_hnizdo;

    bool was_merged = false;
    bool was_switched = false;

    if (type_of_change == 1 || type_of_change == 2 || type_of_change == 3)
    {
        was_merged = true;
    }
    else if (type_of_change == 2)
    {
        was_switched = true;
    }
    
    if (first_turn_right == true)
    {
        if (was_switched)
        {
            return find_hnizdo_with_prvek_after_switch (prvek_, hnizdo_-> middle, hnizdo_, true);
        }
        else if (was_merged)
        {

            return find_hnizdo_with_prvek_after_switch(prvek_, hnizdo_->middle_right, hnizdo_, true);
        }


        else
        {
            return find_hnizdo_with_prvek_after_switch (prvek_, hnizdo_->left_left, hnizdo_, true);

        }
    }

    else
    {
        if (hnizdo_->number_of_nodes == 1)
        {
            if (prvek_ == hnizdo_->hnizdo_arr[0])
            {   
                first_turn_right = true;
                
                return find_hnizdo_with_prvek_after_switch(prvek_, hnizdo_->right_right, hnizdo_, first_turn_right);
            }
            

        }
        else if (hnizdo_->number_of_nodes == 2)
        {
            first_turn_right = true;

            if (prvek_ == hnizdo_->hnizdo_arr[0])
            {
                return find_hnizdo_with_prvek_after_switch(prvek_, hnizdo_->middle, hnizdo_, first_turn_right);
            }
            else if (prvek_ == hnizdo_->hnizdo_arr[1])
            {
                return find_hnizdo_with_prvek_after_switch(prvek_, hnizdo_->right_right, hnizdo_, first_turn_right);
            }
            

        }
        else if (hnizdo_->number_of_nodes == 3)
        {
            first_turn_right = true;

            if (prvek_ == hnizdo_->hnizdo_arr[0])
            {
                return find_hnizdo_with_prvek_after_switch(prvek_, hnizdo_->middle_left, hnizdo_, first_turn_right);
            }
            else if (prvek_ == hnizdo_->hnizdo_arr[1])
            {
                return find_hnizdo_with_prvek_after_switch(prvek_, hnizdo_->middle_right, hnizdo_, first_turn_right);
            }
            else if (prvek_ == hnizdo_->hnizdo_arr[2])
            {
                return find_hnizdo_with_prvek_after_switch(prvek_, hnizdo_->right_right, hnizdo_, first_turn_right);
            }
            
        }
    }
}

ttf_tree::prvek* ttf_tree::find_successor_n_insert_prvek (hnizdo* hnizdo_, prvek* prvek_, bool first_turn_right)
{
    if (hnizdo_ -> left_left == nullptr)
    {

        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin()+1, prvek_);
        prvek* pom = hnizdo_->hnizdo_arr[0];
        
        hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
        //nevolam delete, protože ptr mam uloženej a nechci prvek deletnout ale dat ho jinam
        return pom;
    }

    if (first_turn_right == true)
    {
        return find_successor_n_insert_prvek (hnizdo_->left_left, prvek_, true);
    }

    else
    {
        if (hnizdo_->number_of_nodes == 1)
        {
            if (prvek_ == hnizdo_->hnizdo_arr[0])
            {   
                first_turn_right = true;

                return find_successor_n_insert_prvek(hnizdo_->right_right, prvek_, first_turn_right);
            }
            

        }
        else if (hnizdo_->number_of_nodes == 2)
        {
            first_turn_right = true;

            if (prvek_ == hnizdo_->hnizdo_arr[0])
            {
                return find_successor_n_insert_prvek(hnizdo_->middle, prvek_, first_turn_right);
            }
            else if (prvek_ == hnizdo_->hnizdo_arr[1])
            {
                return find_successor_n_insert_prvek(hnizdo_->right_right, prvek_, first_turn_right);
            }
            

        }
        else if (hnizdo_->number_of_nodes == 3)
        {
            first_turn_right = true;

            if (prvek_ == hnizdo_->hnizdo_arr[0])
            {
                return find_successor_n_insert_prvek(hnizdo_->middle_left, prvek_, first_turn_right);
            }
            else if (prvek_ == hnizdo_->hnizdo_arr[1])
            {
                return find_successor_n_insert_prvek(hnizdo_->middle_right, prvek_, first_turn_right);
            }
            else if (prvek_ == hnizdo_->hnizdo_arr[2])
            {
                return find_successor_n_insert_prvek(hnizdo_->right_right, prvek_, first_turn_right);
            }
            
        }
    } 
    
}

void ttf_tree::get_it_down_n_del(const T& data)
{
    hnizdo* hnizdo_ = find_hnizdo_with_prvek_for_del(data, this->main_root, nullptr);
    
    if (hnizdo_ == nullptr)
    {
        return;
    }
   
    prvek* prvek_ = find_prvek(data, hnizdo_);
    
    int pos;
    for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
    {
        if (hnizdo_->hnizdo_arr[i]->get_data()==data)
        {
            pos = i;
        }
    }
    prvek* succ = find_successor_n_insert_prvek(hnizdo_, prvek_, false);
    

    
    if (succ != prvek_)
    {
        hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+pos);
        hnizdo_->hnizdo_arr.insert(hnizdo_->hnizdo_arr.begin()+pos, succ);
    }
    
    //TOHLE JE WEIRD PROTOŽE POS JE JEDNA NULA ATD, TAKŽE BY MĚLA BÝT MINUS 1, ALE FUNGUJE TO
    this->switched_prvek = hnizdo_->hnizdo_arr[pos];


    hnizdo_ = find_hnizdo_with_prvek_after_switch(this->switched_prvek, hnizdo_, this->parent_of_wanted_hnizdo, false);
    
    
    delete_prvek(data, prvek_, hnizdo_, this->parent_of_wanted_hnizdo);
    return;
}

void ttf_tree::delete_prvek(const T&data, prvek* prvek_, hnizdo* hnizdo_, hnizdo* parent)
{

   
    this->pom_hnizdo = hnizdo_;
    
    
    if (hnizdo_->number_of_nodes >= 2)
    {
        for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
        {
            if (hnizdo_->hnizdo_arr[i]==prvek_)
            {
                delete prvek_;
                hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+i);
                
                hnizdo_->number_of_nodes -= 1;
                this->number_of_elements -=1;
                
                return;
            }
        }
        
    }
    else if (parent->number_of_nodes ==1 && parent->left_left->number_of_nodes == 1 && parent->right_right->number_of_nodes == 1 )
    {
        merge_with_with_one_node_parent(hnizdo_, parent);
        hnizdo_ = this->pom_hnizdo;
        
        for (int i = 0; i < hnizdo_->hnizdo_arr.size(); i++)
        {
            if (hnizdo_->hnizdo_arr[i]==prvek_)
            {
                delete prvek_;
                parent->hnizdo_arr.erase(parent->hnizdo_arr.begin()+i);
                
                this->number_of_elements -=1;
                
                return;
            }
        }
    }
    else if (hnizdo_ == parent->left_left)
    {

        if (parent->number_of_nodes==1 && parent->right_right->number_of_nodes >= 2)
        {
            rotation_for_one_node_parent(hnizdo_, parent);
            
            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
            
            hnizdo_->number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent->number_of_nodes == 2 && parent->middle->number_of_nodes>=2)
        {
            rotation_for_two_node_parent(hnizdo_, parent, 0);

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
            
            hnizdo_->number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent->number_of_nodes == 3 && parent->middle_left->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 0);

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
            hnizdo_ -> number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent -> number_of_nodes == 2 && parent->middle->number_of_nodes == 1)
        {
            merge_for_two_node_parent(hnizdo_, parent, 0);
            hnizdo_ = this->pom_hnizdo;

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());

            hnizdo_->number_of_nodes -= 1;
            this->number_of_elements -= 1;
            
            return;
        }

        

        if (parent->number_of_nodes == 3 && parent->middle_left->number_of_nodes == 1)
        {
            merge_for_three_node_parent(hnizdo_, parent, 0);
            
            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
            hnizdo_->number_of_nodes -=1;
            this->number_of_elements -=1;
            
            return;
        }

        


    }
    else if (hnizdo_ == parent->middle_left)
    {

        if (parent->number_of_nodes == 3 && parent->left_left->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 1);

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
            hnizdo_ -> number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent->number_of_nodes == 3 && parent->middle_right->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 2);

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
            hnizdo_ -> number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent->number_of_nodes == 3 && parent->middle_right->number_of_nodes == 1)
        {
            merge_for_three_node_parent(hnizdo_, parent, 1);

            delete hnizdo_->hnizdo_arr[0];
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
            hnizdo_->number_of_nodes -=1;
            this->number_of_elements -=1;
            
            return;
        }

        
        
    }
    else if (hnizdo_ == parent->middle)
    {
        if (parent->number_of_nodes == 2 && (parent->left_left->number_of_nodes>=2 || parent->right_right->number_of_nodes>=2))
        {
            if (parent->left_left -> number_of_nodes >= 2)
            {
                rotation_for_two_node_parent(hnizdo_, parent, 1);

                delete prvek_;
                hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
                
                hnizdo_->number_of_nodes -= 1;
                this->number_of_elements -=1;
                
                return;
            }
            else if (parent->right_right -> number_of_nodes >= 2)
            {
                rotation_for_two_node_parent(hnizdo_, parent, 1);

                delete prvek_;
                hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
                
                hnizdo_->number_of_nodes -= 1;
                this->number_of_elements -=1;
                
                return;
            }
        }

        if (parent -> number_of_nodes == 2 && (parent->left_left->number_of_nodes == 1 || parent->right_right->number_of_nodes == 1))
        {
            
            merge_for_two_node_parent(hnizdo_, parent, 1);
            hnizdo_ = this->pom_hnizdo;

            delete prvek_;
            hnizdo_ = this->pom_hnizdo;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+2);
            
            hnizdo_->number_of_nodes -= 1;
            this->number_of_elements -= 1;
            
            return;
        }
    }
    else if (hnizdo_ == parent->middle_right)
    {
        if (parent->number_of_nodes == 3 && parent->middle_left->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 3);

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
            hnizdo_ -> number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent->number_of_nodes == 3 && parent->right_right->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 4);

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin());
            hnizdo_ -> number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent->number_of_nodes == 3 && parent->middle_left->number_of_nodes == 1)
        {
            
            merge_for_three_node_parent(hnizdo_, parent, 2);

            delete hnizdo_->hnizdo_arr[2];
            
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+2);
            
            hnizdo_->number_of_nodes -=1;
            this->number_of_elements -=1;
            
            return;
        }

        

        
    }
    else if (hnizdo_ == parent->right_right)
    {
        
        if (parent->number_of_nodes==1 && parent->left_left->number_of_nodes >= 2)
        {
            rotation_for_one_node_parent(hnizdo_, parent);
            
            delete prvek_;
            hnizdo_->hnizdo_arr.erase(parent->hnizdo_arr.begin()+1);
            
            hnizdo_->number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent->number_of_nodes == 2 && parent->middle->number_of_nodes>=2)
        {
            rotation_for_two_node_parent(hnizdo_, parent, 2);

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
            
            hnizdo_->number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            
            return;
        }

        if (parent->number_of_nodes == 3 && parent->middle_right->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 5);

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+1);
            hnizdo_ -> number_of_nodes -= 1;
            this->number_of_elements -=1;
            
            return;
        }

        if (parent -> number_of_nodes == 2 && parent->middle->number_of_nodes == 1)
        {
            merge_for_two_node_parent(hnizdo_, parent, 2);
            hnizdo_ = this->pom_hnizdo;

            delete prvek_;
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+2);

            hnizdo_->number_of_nodes -= 1;
            this->number_of_elements -= 1;
            return;
        }

        

        if (parent->number_of_nodes == 3 && parent->middle_right->number_of_nodes == 1)
        {
            merge_for_three_node_parent(hnizdo_, parent, 3);

            delete hnizdo_->hnizdo_arr[2];
            hnizdo_->hnizdo_arr.erase(hnizdo_->hnizdo_arr.begin()+2);
            hnizdo_->number_of_nodes -=1;
            this->number_of_elements -=1;
            
            return;
        }

        

        
    }
    

}

//0 - nothing
//1 - merge w one node parent
//2 - merge w two node parent middle
//3 - merge w three node parent - menit se nemusí
//4 - rotation
int ttf_tree::reorganize_the_tree(hnizdo* hnizdo_, hnizdo* parent)
{
    
    
    if (parent == nullptr)
    {
        return 0;     
    }


    if (parent->number_of_nodes ==1 && parent->left_left->number_of_nodes == 1 && parent->right_right->number_of_nodes == 1 )
    {
        merge_with_with_one_node_parent(hnizdo_, parent);
        
        return 1;
    }

    else if (hnizdo_ == parent->left_left)
    {
        //case with one node parent and prvek to del v left left
        if (parent->number_of_nodes==1 && parent->right_right->number_of_nodes >= 2 )
        {
            
            rotation_for_one_node_parent(hnizdo_, parent);
            
            return 4;
        }

        if (parent->number_of_nodes == 2 && parent->middle->number_of_nodes>=2)
        {
            rotation_for_two_node_parent(hnizdo_, parent, 0);

            return 4;
        }

        if (parent->number_of_nodes == 3 && parent->middle_left->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 0);

            return 4;
        }

        if (parent -> number_of_nodes == 2 && parent->middle->number_of_nodes == 1)
        {
            merge_for_two_node_parent(hnizdo_, parent, 0);

            return 2;
        }

        

        if (parent->number_of_nodes == 3 && parent->middle_left->number_of_nodes == 1)
        {
            merge_for_three_node_parent(hnizdo_, parent, 0);
            return 3;
        }

        


    }
    else if (hnizdo_ == parent->middle_left)
    {
        if (parent->number_of_nodes == 3 && parent->left_left->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 1);

            return 3;
        }

        if (parent->number_of_nodes == 3 && parent->middle_right->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 2);

            return 3;
        }

        if (parent->number_of_nodes == 3 && parent->middle_right->number_of_nodes == 1)
        {
            merge_for_three_node_parent(hnizdo_, parent, 1);
            
            return 3;
        }

        
        
    }
    else if (hnizdo_ == parent->middle)
    {
        if (parent->number_of_nodes == 2 && (parent->left_left->number_of_nodes>=2 || parent->right_right->number_of_nodes>=2))
        {
            if (parent->left_left -> number_of_nodes >= 2)
            {
                rotation_for_two_node_parent(hnizdo_, parent, 1);

                return 4;
            }
            else if (parent->right_right -> number_of_nodes >= 2)
            {
                rotation_for_two_node_parent(hnizdo_, parent, 1);

                return 4;
            }
        }

        if (parent -> number_of_nodes == 2 && (parent->left_left->number_of_nodes == 1 || parent->right_right->number_of_nodes == 1))
        {
            merge_for_two_node_parent(hnizdo_, parent, 1);

            return 2;
        }
    }
    else if (hnizdo_ == parent->middle_right)
    {
        
        if (parent->number_of_nodes == 3 && parent->middle_left->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 3);

            return 4;
        }

        if (parent->number_of_nodes == 3 && parent->right_right->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 4);

            return 4;
        }

        if (parent->number_of_nodes == 3 && parent->middle_left->number_of_nodes == 1)
        {
            merge_for_three_node_parent(hnizdo_, parent, 2);
            
            return 3;
        }

        

        

        
    }
    else if (hnizdo_ == parent->right_right)
    {
        //case with one node parent and prvek to del v right right
        if (parent->number_of_nodes==1 && parent->left_left->number_of_nodes >= 2)
        {
            
            rotation_for_one_node_parent(hnizdo_, parent);
            
            return 4;
        }

        if (parent->number_of_nodes == 2 && parent->middle->number_of_nodes>=2)
        {
            rotation_for_two_node_parent(hnizdo_, parent, 2);

            return 4;
        }
        
        if (parent->number_of_nodes == 3 && parent->middle_right->number_of_nodes >= 2)
        {
            rotation_for_three_node_parent(hnizdo_, parent, 5);

            return 4;
        }

        if (parent -> number_of_nodes == 2 && parent->middle->number_of_nodes == 1)
        {
            merge_for_two_node_parent(hnizdo_, parent, 2);

            return 2;
        }

        

        if (parent->number_of_nodes == 3 && parent->middle_right->number_of_nodes == 1)
        {
            merge_for_three_node_parent (hnizdo_, parent, 3);

            return 3;
        }

        

        
    }
    return 0;
}