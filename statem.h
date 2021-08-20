#include <stddef.h>
#include <string.h>

typedef enum answer{
    STRANGE_QUERY,
    LIST,
    GET,
    NO_ENTRY,
    ALREADY_CREATED,
    COUNT_OVERFLOV,
    LONG_NAME,
    NO_NAME,
    WRONG_STATE,
    EXIT,
    OK
} answer;

typedef enum state{
    INITIAL,
    RUN,
    PAUSE,
    CLOSED,
    CANARY
} state;

typedef struct machine{
    char _name[16]; 
    state _state;
} machine;

typedef struct call_stack{
    char* str; 
    answer(*ptr)(char*,machine*);
} call_stack;

char* new_query(char* buffer, machine* stack);
answer read_query(char* query, machine* stack);

answer _Init(char* name, machine* stack);
answer _Run(char* name, machine* stack);
answer _Pause(char* name, machine* stack);
answer _Stop(char* name, machine* stack);
answer _Enough(char* name, machine* stack);
answer _Exterminantus(char* name, machine* stack);

answer _Get(char* name, machine* stack);
answer _List(char* name, machine* stack);
answer _Exit_server(char* name, machine* stack);

char* _Get_impl(char* buffer, machine* stack);
char* _List_impl(char* buffer, machine* stack);
