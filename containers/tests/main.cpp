#include "../ft_deque.hpp"
#include "../ft_list.hpp"
#include "../ft_map.hpp"
#include "../ft_stack.hpp"
#include "../ft_vector.hpp"
#include "../ft_queue.hpp"
#include <string>
#include <iostream>
#include <cstring>
void list_checking(void);
void deque_check(void);
void map_check(void);
void stack_check(void);
void vector_check(void);
void queue_check(void);

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "list"))
            list_checking();
        else if (!strcmp(argv[1], "deque"))
            deque_check();
        else if (!strcmp(argv[1], "map"))
            map_check();
        else if (!strcmp(argv[1], "stack"))
            stack_check();
        else if (!strcmp(argv[1], "vector"))
            vector_check();
        else if (!strcmp(argv[1], "queue"))
            queue_check();
    }
    else{
        list_checking();
        deque_check();
        map_check();
        stack_check();
        vector_check();
        queue_check(); 
		std::cout << "!!!! All tests out !!!!" << std::endl;}
    return (0);
}