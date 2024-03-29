#include <iostream>
#include <vector>
#include <string>

class graph {
private:
    std::vector<std::vector<int>> matrix;
    std::vector<int> vertexes;
    std::vector<std::string> marks;
    std::vector<std::string> v_names;
    std::vector<int> e_cost;
    std::vector<std::vector<int>> chains;
    std::vector<int> path;
    bool is_empty = true;
public:
    graph(){;}
    
    unsigned long get_size(){ // возвращает произведение размера ряда и размера столбца матрицы инцидентности
        if (!is_empty)
            return matrix.size() * matrix[0].size();
        return 0;
    }
    void add_vertex(std::string name, std::string mark){
        //is_empty = false;
        vertexes.push_back(0);
        marks.push_back(mark);
        v_names.push_back(name);
    }
    int get_index_vert(std::string name){
        for (int i=0; i<vertexes.size();i++){
            if (name == v_names[i])
                return i;
        }
        std::cout << "no vertex with name " << name << std::endl;
        return -1;
    }
    void add_edge(std::string vertex1, std::string vertex2, int cost){
        if (get_index_vert(vertex1) == -1 or get_index_vert(vertex2) == -1) {
            std::cout << "vertex is not in matrix" << std::endl;
        }
        else if (vertexes.size()!=0){
            if (is_empty){
                for (int i=0; i< vertexes.size(); i++){
                    matrix.push_back(std::vector<int>(1,0));
                }
            }
            else {
                for (int i=matrix.size(); i< vertexes.size(); i++){
                    matrix.push_back(std::vector<int>(1,0));
                }
                for (int i=0; i< vertexes.size();i++){
                    matrix[i].resize(matrix[i].size()+1);
                }
            }
            e_cost.push_back(cost);
            matrix[get_index_vert(vertex1)][matrix[0].size()-1] = 1;
            matrix[get_index_vert(vertex2)][matrix[0].size()-1] = 1;
            is_empty = false;
        }
        
        else {
            std::cout << "no vertex in matrix" << std::endl;
        }
    }
    int first(std::string vertex){ // возвращает индекс первого смежного узла
        int index = get_vertex(vertex);
        if (index != -1) {
            for (int j=0; j< matrix.size();j++){
                for (int i=0;i<matrix[0].size();i++){
                    if (matrix[j][i] == 1 and matrix[index][i] == 1 and j != index)
                        return j;
                }
            }
        }
        else{
            std::cout << "no vertex with name " << vertex<<std::endl;
        }
        return -1;
    }
    int next_v(std::string vertex, int i){// возвращает индекс первого смежного узла после индекса i
        int index = get_vertex(vertex);
        if (index != -1) {
            for (int j=i+1; j< matrix.size();j++){
                for (int a=0;a<matrix[0].size();a++){
                    if (matrix[j][a] == 1 and matrix[index][a] == 1 and j != index)
                        return j;
                }
            }
        }
        else{
            std::cout << "no vertex with name " << vertex<<std::endl;
        }
        return -1;
    }
    std::string get_adjacent_vertex(std::string v, int i){ // возврашает имя узла с заданным индексом
        int index = get_index_vert(v);
        if (index != -1) {
            for (int j =0;j<matrix[0].size();j++){
                if (matrix[i][j] == 1 and matrix[index][j] == 1 and i != index)
                    return v_names[i];
            }
            std::cout<< "vertex with index " << i << " is not adjacent to vertex " << v << std::endl;
        }
        else{
            std::cout << "no vertex with name " << v<<std::endl;
        }
        return "";
    }
    int get_vertex(std::string name){
        for (int i =0;i<v_names.size();i++){
            if (v_names[i] == name)
                return i;
        }
        return -1;
    }
    int get_edge_index(std::string vertex1, std::string vertex2){
        if (is_empty){
            std::cout << "graph is empty" << std::endl;
            return -1;
        }
        else if (get_vertex(vertex1) == -1 or get_vertex(vertex2) == -1){
            std::cout << "no vertex with name given" <<std::endl;
            return -1;
        }
        else{
            int v1_index = get_vertex(vertex1);
            int v2_index = get_vertex(vertex2);
            for (int i=0;i < matrix[0].size();i++){
                if (matrix[v1_index][i] == 1 and matrix[v2_index][i] == 1 )
                    return i;
            }
        }
        return -1;
    }
    void del_v(std::string name){ // mb delete edge along
        const int index = get_vertex(name);
        if (index != -1){
            matrix.erase(matrix.begin()+index);
            vertexes.erase(vertexes.begin()+index);
            v_names.erase(v_names.begin()+index);
            marks.erase(marks.begin()+index);
        }
        else{
            std::cout << "no vertex with name " << name << std::endl;
        }
    }
    void del_e(std::string vertex1, std::string vertex2){
        int edge_index = get_edge_index(vertex1, vertex2);
        if (edge_index == -1) {
            std::cout << "error, check if graph is empty or has no given vertexes" << std::endl;
        }
        else{
            for (int i=0;i<matrix.size();i++){
                matrix[i].erase(matrix[i].begin()+edge_index);
            }
            e_cost.erase(e_cost.begin()+edge_index);
        }
    }
    
    void edit_v(std::string name, std::string new_mark){ // изменяет метку узла по его имени
        if (vertexes.size() != 0){
            int index = get_vertex(name);
            if (index != -1){
                marks[index] = new_mark;
            }
            else{
                std::cout << "no vertex with name " << name<<std::endl;
            }
        }
    }
    void edit_v(int index, std::string new_mark){ // изменяет метку узла по его имени
        if (vertexes.size() != 0){
            if (index != -1){
                marks[index] = new_mark;
            }
            else{
                std::cout << "no vertex with name " << v_names[index]<<std::endl;
            }
        }
    }
    void edit_e(std::string vertex1, std::string vertex2, int new_cost){ //изменяет цену дуги
        if (!is_empty){
            int index = get_edge_index(vertex1, vertex2);
            if (index != -1){
                e_cost[index] = new_cost;
            }
            else{
                std::cout << "no edge with vertexes "<< vertex1 << " and "  << vertex2 << std::endl;
            }
        }
        else{
            std::cout << "graph is empty" << std::endl;
        }
    }
    void display_matrix(){ //выводит матрицу инцидентности
        if (!is_empty){
            std::cout << "___";
            for (int i=0; i<matrix[i].size();i++ ){
                std::cout <<i<< "_" ;
            }
            std::cout << std::endl;
            for (int i=0; i<matrix.size();i++){
                std::cout << v_names[i] << " |";
                for (int j =0; j< matrix[i].size();j++){
                    std::cout << matrix[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
    
    void search_chains(std::string vertex, std::string goal){
        std::vector<std::vector<int>> temp = matrix;// сохранение исходного состояния матрицы
        for (int i=first(vertex); i>-1; i = next_v(vertex, i)){ // проход по всем соседям
            marks[get_index_vert(vertex)] = "grey"; // метка посешенности
            path.push_back(get_index_vert(vertex)); // добавление узла в цепь
            DFS_chain(v_names[i], goal); // запуск рекурсивной функции
        }
        matrix = temp;
    }
    void DFS_chain(std::string start, std::string goal){
        int index = get_index_vert(start);
        edit_v(start, "grey");// маркирует узел посещенным
        path.push_back(index);// добавляет в цепь посещения
        
        if (start != goal){// проверка на достижение узла-цели
            for (int i=first(start); i>-1; i = next_v(start, i)){// проход по всем соседям
                if (get_mark(i) == "white"){ // если узел не посещен
                    DFS_chain(v_get_name(i), goal);
                }
                
            }
            edit_v(index, "black"); // если больше не осталось смежных узлов маркируется полностью пройденным
            if (path.size() > 0){
                path.pop_back(); // удаляет из цепи посещения
            }
        }
        else {
            chains.push_back(path);
            for (int x =0; x<marks.size(); x++){// маркировка всех узлов непройденным, чтобы посетить посещенные ранее но не входящие в конечную цепь узлы
                edit_v(x, "white");
            }
            edit_v(path[0], "grey"); // начальную вершину цепи обозначим пройденной воизбежание ее посещения
            std::vector<int> *temp = new std::vector<int>();
            *temp = e_cost;
            for (int l =1; l < path.size()-1; l++){ // удаляет дуги всех узлов, входящих в конечную цепь
                for (int k=first(v_get_name(path[l]) ); k>-1; k = next_v(v_get_name(path[l]), k) ) {
                    del_e(v_get_name(path[l]) , v_get_name(k) );
                }
            }
            e_cost = *temp;
            delete temp;
            path.erase(path.begin(), path.end()); // очищает цепь
        }
    }
    std::vector<std::vector<int>> get_chains(){
        return chains;
    }
    void print_chains(){
        for (int i=0; i< chains.size();i++){
            for (int j=0;j< chains[i].size();j++){
                std::cout << v_get_name(chains[i][j]) << "  ";
            }
            std::cout << std::endl;
        }
    }
    
    void erase_chains(){
        chains.erase(chains.begin(), chains.end());
    }
    int get_cost(std::string vertex){
        int index = get_index_vert(vertex);
        return e_cost[index];
    }
    std::string get_mark(std::string vertex){
        int index = get_index_vert(vertex);
        return marks[index];
    }
    std::string get_mark(int index){
        return marks[index];
    }
    
    void print_marks(){
        for (int i=0; i< marks.size();i++){
            std::cout << marks[i] << " ";
        }
        std::cout << std::endl;
    }
    void print_costs(){
        for (int i=0; i< e_cost.size();i++){
            std::cout << e_cost[i] << " ";
        }
        std::cout << std::endl;
    }
    std::string v_get_name(int index){
        return v_names[index];
    }
};
