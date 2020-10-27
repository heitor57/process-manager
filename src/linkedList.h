struct process{
    int pid;
};
typedef struct descriptor List;

List* create_list();
void free_list(List* li);
int insert_end(List* li, struct process p);
int insert_start(List* li, struct process p);
int remove_start(List* li);
int remove_end(List* li);
int size_list(List* li);
int full_list(List* li);
int empty_list(List* li);
int get_by_pid(List* li, int pid, struct process *p);
int get_by_index(List* li, int pos, struct process *p);
void print_list(List* li);
