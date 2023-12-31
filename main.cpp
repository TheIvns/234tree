#include "234tree.hpp"
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;


int compare(const void* a, const void* b)
{
	const int* x = (int*) a;
	const int* y = (int*) b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;

	return 0;
}

void Fisch_schuffle(int* array, unsigned int number_of_data)
{
    cout<<endl;
    cout<<"fischer"<<endl;
    for (int i = 0; i < number_of_data; i++)
    {
        int pom = array[i];
        int random = rand() % number_of_data;
        array[i] = array[random];
        array[random] = pom;
    }
    for(int i = 0; i < number_of_data; i ++)
    {
        cout<<array[i]<<", ";
    }
    cout<<endl;
}

bool TRY_fisher(int number_of_data)
{
    mt19937 mt(time(nullptr));
    
    int data[50] = {};
    for(int i = 0; i < number_of_data; i++)
    {
        data[i] = mt();
        sleep_for(nanoseconds(10));
    }
    for (int i = 0; i < number_of_data; i++)
    {
        cout<<data[i]<<", ";
    }

    Fisch_schuffle(data, number_of_data);
    cout<<endl;

    TTFT<int> tree;

    for (int i = 0; i < number_of_data; i++)
    {
        tree.insert(data[i]);
        //cout<<data[i]<<", ";
    }
    //bud copy implementovat nebo proste ptr
    tree.TREEPRINT();
    if(!tree.is_TTFT())return false;
    while (!tree.empty())
    {
        tree.TREEPRINT();
        int random = rand()%50;
        std::cout<<"deleting "<< data[random] << std::endl;
        tree.delete_element(data[random]);
        
        if(!tree.empty())
        {
            if(!tree.is_TTFT())
            {
                std::cout<<"not ttft"<<std::endl;
                sleep(10);
            }
            tree.TREEPRINT();
        }
        std::cout<<"/////"<<std::endl;
    }
    return true;
}

bool sorted(int number_of_data)
{
    mt19937 mt(time(nullptr));

      
    
    int data[50] = {};
    for(int i = 0; i < number_of_data; i++)
    {
        data[i] = mt();
        sleep_for(nanoseconds(10));
    }
    for (int i = 0; i < number_of_data; i++)
    {
        cout<<data[i]<<", ";
    }
    
	qsort(data, number_of_data, sizeof(int),compare);

    TTFT<int> tree;

    for (int i = 0; i < number_of_data; i++)
    {
        tree.insert(data[i]);
        //cout<<data[i]<<", ";
    }

    tree.TREEPRINT();
    if(!tree.is_TTFT())return false;
    return true;
}

bool sorted_back(int number_of_data)
{
    mt19937 mt(time(nullptr));

      
    
    int data[50] = {};
    for(int i = 0; i < number_of_data; i++)
    {
        data[i] = mt();
        sleep_for(nanoseconds(10));
    }
    for (int i = 0; i < number_of_data; i++)
    {
        cout<<data[i]<<", ";
    }
    
	qsort(data, number_of_data, sizeof(int),compare);
    TTFT<int> tree;

    tree = TTFT<int>();
    for (int i = 0; i < number_of_data; i++)
    {
        tree.insert(data[number_of_data-1-i]);
        //cout<<data[number_]<<", ";
    }
    if(!tree.is_TTFT())return false;
    return true;
}


int main(){
/*
    sorted(50);
    if(!TRY_fisher(50))
        {
            cout<<"ERRROROROROROROR"<<endl;
            return 1;
        }
    if(!TRY_fisher(50))
        {
            cout<<"ERRROROROROROROR"<<endl;
            return 1;
        }
    sorted_back(50);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    */
    for (int i = 0; i < 30; i++)
    {
        if(!TRY_fisher(50))
        {
            cout<<"ERRROROROROROROR"<<endl;
            return 1;
        }
    }

    /*TTFT<int> tree;
    for(int i = 0; i < 20; i++)
    {
        tree.insert(i);
    }
    tree.insert(20);
    tree.insert(21);
    tree.TREEPRINT();
    tree.TREEPRINT();
    //tree.TREEPRINT();
    srand((unsigned) time(NULL));
    

   while (!tree.empty())
    {
        tree.TREEPRINT();
        int random = rand()%20;
        std::cout<<"deleting "<< random << std::endl;
        tree.delete_element(random);
        
        if(!tree.empty())
        {
            if(!tree.is_TTFT())
            {
                sleep(10);

            }
            tree.TREEPRINT();
        }
        std::cout<<"/////"<<std::endl;
    }*/
    
    
    //tree.delete_element(2);//nesmazalo to dvojku, weird
}
