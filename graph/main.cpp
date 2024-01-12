#include <iostream>
#include "graph.h"

void example_metods(){
    graph graph;
    graph.add_vertex("a", "white");
    graph.add_vertex("b", "white");
    graph.add_vertex("c", "white");
    graph.add_vertex("d", "white");

    graph.add_edge("a", "b", 1);
    graph.add_edge("a", "c", 1);
    graph.add_edge("a", "d", 1);
    
    graph.display_matrix();
    std::cout <<std::endl;
    
    std::cout << graph.first("a") << std::endl;
    std::cout << graph.next_v("a", 1) << std::endl;
    std::cout << graph.get_adjacent_vertex("a", 2) << std::endl;
    graph.del_v("d");
    graph.del_e("a", "c");
    
    graph.display_matrix();
    std::cout <<std::endl;

    graph.print_costs();
    graph.edit_e("a", "b", 14);
    graph.print_costs();
    
    std::cout <<std::endl;

    graph.print_marks();
    graph.edit_v("b", "black");
    graph.print_marks();
    std::cout <<std::endl;

}
void example_chains(){
    graph graph;
    graph.add_vertex("a", "white");
    graph.add_vertex("b", "white");
    graph.add_vertex("c", "white");
    graph.add_vertex("d", "white");
    graph.add_vertex("e", "white");
    graph.add_vertex("f", "white");
    graph.add_vertex("g", "white");
    graph.add_vertex("h", "white");
    graph.add_vertex("i", "white");
    graph.add_vertex("k", "white");
    graph.add_vertex("x", "white");
    graph.add_vertex("y", "white");
    graph.add_vertex("m", "white");
    graph.add_vertex("n", "white");
    graph.add_vertex("v", "white");
    graph.add_vertex("r", "white");

    graph.add_edge("a", "b", 1);
    graph.add_edge("a", "c", 1);
    graph.add_edge("a", "d", 1);
    graph.add_edge("b", "e", 1);
    graph.add_edge("b", "f", 1);
    graph.add_edge("e", "g", 1);
    graph.add_edge("e", "h", 1);
    graph.add_edge("h", "i", 1);
    graph.add_edge("f", "h", 1);
    graph.add_edge("f", "k", 1);
    graph.add_edge("i", "x", 1);
    graph.add_edge("c", "v", 1);
    graph.add_edge("v", "m", 1);
    graph.add_edge("v", "n", 1);
    graph.add_edge("m", "x", 1);
    graph.add_edge("n", "y", 1);
    graph.add_edge("y", "x", 1);
    graph.add_edge("d", "n", 1);
    graph.add_edge("d", "r", 1);
    graph.add_edge("r", "c", 1);
    
    graph.display_matrix();
    std::cout << std::endl;
    graph.search_chains("a", "x");
    graph.print_chains();
}
int main() {
    
    //example_metods();
   example_chains();
    
}
