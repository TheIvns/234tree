#include "234tree.hpp"

using namespace std;


int main()
{ 
    srand((unsigned) time(NULL));

    cout << "good"<<endl;
    ttf_tree tree;
    int hovnajs = rand()%40;
    cout<<hovnajs<<" random"<<endl;
    tree.TREE_INSERT(hovnajs);
    for (int i = 40; i > 1; i--)
    {
        int random = rand()%100;
        cout << "input " << random << endl;
        tree.TREE_INSERT(random);
        //tree.displHnizdo(tree.main_root);     
    }


    
   
  

    
    
    tree.TREEPRINT();

    
    
    tree.get_it_down_n_del(hovnajs);
  
    
    
    tree.TREEPRINT();

    tree.clear();

    return 0;
}
