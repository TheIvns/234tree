# 234tree
school project

Dokumentace k 234 stromu + popis B-stromu

Struktura
Je zde class 234 strom

Ta má subbclassy hnizda
Ty mají jako atributy 5 ptrs dolů, left left, middle left, middle, middle right, right right. 
Jsou obsazené podle počtu prvků v hnizde.
Dále má atribut hnizdo_arr, což je vektor.

Dále je zde subbclass prvek.
To jsou prvky, které vkládám do vektoru. Mají atribut data.


Public funkce 
**Empty** - bool typ, je strom prázdný?

**Tree insert** - vkládání dat typu T, vkládání do stromu, volá si funkce insert into subtree

**Clear** - vyčistí celý strom aniž by dával bacha na vyváženost

**Find prvek** - bere data typu T, a ptr na hnizdo, kde chci začínat, obecně mainroot, vrátí ukazatel na prvek, který hledám pomocí dat

**get_it_down_n_del** - bere za argument data typu T, funkce, která maže prvek a zároveň balancuje strom pomocí reorganize_the_tree a delete_prvek

**Get_depth** - vrátí hloubku stromu

**Treeprint** - vykreslí strom, doporučuju v konzoli toggle size to content width. Každé hnízdo má pod sebou 5 ptrs a podle obsazenosti jsou obsazené ptrs. K značí konec hnizda a X nullptrs. X^n značí kolik nullptrs vykreslí jeden nullptr v patře výš. 6x/ značí konec pětice ptrs.

Private 

**Insert into subtree** - normální vkládání až na to, že pokud narazí při vkládání na node s 3 prvky, tak zavolá split funkci, po split funkci se volá insert into subtree ale s hnizdo = Parent a Parent = grandparent, protože by se špatně rozlišovalo, kde po splitu jsem. Tedy je to krok zpátky a insert. Pokud má po splitu Parent, tedy hnizdo, tři nody tak to nechávám být, ať to nesplituju zbytečně.

**Split** - splituje hnizdo podle vlastností 234 stromu, je lepší interpretovat graficky, ve zkratce prostřední prvek nahoru a podle toho kde jsem se přepojí pointery

**Insert into hnizdo** - vytvoří nový prvek v hnizdu a automaticky ho korektně zařadí, automaticky zvětšuje Number of nodes daného hnizda. Proto je potřeba při přemísťování ve splitu delete

**Printlv** - vyprintí daný level stromu

**Remove_all** - používá se při clear, všechno smaže

**Find hnizdo with prvek for del** - používat jen při delete, protože volá reorganize_tree. Vrací ukazatel na hnizdo s hledaným prvkem. Pokud najde prvek, už nevolá reorganize the tree, volá si to až find hnízdo with prvek aster switch. Pokud prvek co chceme mazat neexistuje, vyhodí prvek není v databázi, strom je sice přeorganizovaný, ale ničemu by to nemělo vadit, protože při merges and rotations se udržuje pořadí.

**Find hnizdo with prvek after switch** - najde hnizdo s hledaným prvkem po find_successor_n_insert_prvek, protože jakmile najdu hnizdo s prvek s Find hnizdo with prvek for del, tak ho musím switchnout s jeho successorem. Poté je zde jiný typ hledání než podle seřazení.

**Merges and rotations** - rotace a merge pro specifický typ prvků v hnizdu

**Reorganize the tree** - při průchodu stromem pro delete prvku je potřeba předělávat hnizda s jedním prvkem, abychom nezpůsobili underflow, o to se stará reorganize the tree. Vrací int podle typu změny, protože pak je potřeba jinak hledat s funkcemi find hnizdo.

**Find successor n insert prvek** - najde successora hledaného prvku a nahradí ho hledaným prvkem, v get don n delete se nahradí prvek succeessorem



