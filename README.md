# 234tree
school project

Struktura
Je zde class 234 strom

Subclasses - nest with arguments: ptr_arr - array of pointers to another nests, nest_arr - array of pointers to elements
           - element with arguments: data of type T, get_data() - returns data saved in element



Public functions 

**Empty** - bool type {}

**insert** - void type, inserting data of type T {const T& data}

**TREEPRINT** - void type, printing tree {}

**is_TTFT** - bool type, returns bool value of right order of elements in tree, {}

**delete_element** - void type, deletes element in tree, {const T& data}

**is_element_in_tree** - bool type, returns bool value of element being in tree, {}

Private functions 

**insert_into_subtree** void type {const T& data, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& parent, bool was_split}
- inserting data into subtree, bool was_split is there for case nest_ was split while inserting data

**insert_into_nest** void type {const T& data, std::unique_ptr<TTFT<T>::nest>& nest_, bool new_data}
- inserts data into nest

**find_way** int type {const T& data, std::unique_ptr<TTFT<T>::nest>& nest_}
- returns way from nest for particular data, so ttft remains sorted, eg I want to add 3, nest has elements 2,4, I get 1 because 3 > 2 and 3 < 4

**split** void type {std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& parent}
- splits nest

**printlv** void type {std::unique_ptr<TTFT<T>::nest>& nest_, int n, int pom}

**check_subtree** {std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_, int parent_control}
-check whether subtree is sorted

**find_element** bool type, {const T& data, int pom_depth, std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_, bool deleting, bool right, bool successor}
- find_element in tree with particular operations while doing it, delete is composed within, if I want to find element in tree, I cant just give away a pointer because Im using smartptrs, so if somebody wants to change element, it is best to program function, that uses find element, deletes it and inserts new element

**is_case_I** bool type {int pom, std::unique_ptr<TTFT<T>::nest>& nest_}
-check whether our problem looks like case one, it is basic rotation

**rotate** void type {int to, int from, std::unique_ptr<TTFT<T>::nest>& parent}
-rotation from from to to

**caseI** void type {int pom, std::unique_ptr<TTFT<T>::nest>& parent}
-case for rotation, it find suitable conditions for rotation

**find_overseer** int type {int dataTO, int dataFROM, std::unique_ptr<TTFT<T>::nest>& parent}
-finds element in parent nest that is between two datas that are given

**find_in_nest** int type {const T& data, std::unique_ptr<TTFT<T>::nest>& nest_}
-finds on which pos are data in nest, otherwards returns -1

**cut_ith_el** void type {int order, std::unique_ptr<TTFT<T>::nest>& nest_}
-deletes ith element from nest_

**caseII** void type {std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_}
- perform case two

**is_case_II** bool type {std::unique_ptr<TTFT<T>::nest>& parent}
- check whether our problem looks like case two, it is merge with two node parent - this case can happen only for main_root
  
**is_case_III** bool type {int pom, std::unique_ptr<TTFT<T>::nest>& parent}
- check whether our problem looks like case three, it is merge with n node parent
  
**caseIII** void type {int pom, std::unique_ptr<TTFT<T>::nest>& parent, const T& data_to_del}
- performs case 3

**merge** void type {int home, int neighbour, std::unique_ptr<TTFT<T>::nest>& parent, const T& data_to_del}
- merges home, neighbour and data in parent into one nest
  
**insert_ptr_to_nest** void type {int pos, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::nest>& input}
- inserts ptr to nest, usually using for inserting into ptr_arr
  
**del_ith_ptr** void type {int pos, std::unique_ptr<TTFT<T>::nest>& nest_}
- deletes ith ptr, using for deleting ptrs from ptr_arr
  
**find_successor** type std::unique_ptr<typename TTFT<T>::element> {int way, int pom_depth, std::unique_ptr<TTFT<T>::nest>& nest_, std::unique_ptr<TTFT<T>::element>& element_, bool turned}
- find successror of element, it is next largest element in tree and puts elements to its place and returns successor

**is_in_tree** bool type {const T& data, int pom_depth, std::unique_ptr<TTFT<T>::nest>& parent, std::unique_ptr<TTFT<T>::nest>& nest_}
- returns bool value of element being in ttft

