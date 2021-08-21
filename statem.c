#include "statem.h"

call_stack queryes[] = {
    {"init", _Init},
    {"run", _Run},
    {"pause", _Pause},
    {"stop", _Stop},
    {"enough", _Enough},
    {"exterminantus", _Exterminantus},
    {"get", _Get},
    {"exit", _Exit_server},
    {"list", _List},
    {NULL, NULL}
};

answer read_query(char* query, machine* stack){
    query = strtok(query, ":");
    call_stack* query_ptr;
    for(query_ptr = queryes; query_ptr->ptr; query_ptr++)
        if(!strcmp(query, query_ptr->str))
            return query_ptr->ptr(strtok(NULL, "\n"), stack);

    return STRANGE_QUERY;
}

machine* seek_machine(char* name, machine* stack){
    for(; stack->_state != CANARY; stack++)
        if(!strcmp(stack->_name, name))
            return stack;

    return NULL;
}

answer _Init(char* name, machine* stack){
    if(!name) return STRANGE_QUERY;
    if(strlen(name) > 15) return LONG_NAME;
    if(seek_machine(name, stack)) return ALREADY_CREATED;
    for(; ; stack++)
        switch(stack->_state){
            case CANARY: 
                return COUNT_OVERFLOV;
            case CLOSED: 
                strcpy(stack->_name, name);
                stack->_state = INITIAL;
                return OK;
        }
}

answer _Run(char* name, machine* stack){
    stack = seek_machine(name, stack);
    if(!name) return STRANGE_QUERY;
    if(!stack) return NO_ENTRY;
    if(stack->_state == CLOSED) return WRONG_STATE;

    stack->_state = RUN;
    return OK;
}

answer _Pause(char* name, machine* stack){
    stack = seek_machine(name, stack);
    if(!name) return STRANGE_QUERY;
    if(!stack) NO_ENTRY;
    if(stack->_state != RUN) return WRONG_STATE;

    stack->_state = PAUSE;
    return OK;
}

answer _Stop(char* name, machine* stack){
    for(; stack->_state != CANARY; stack++)
        if(stack->_state == RUN) stack->_state = PAUSE;

    return OK;
}

answer _Enough(char* name, machine* stack){
    stack = seek_machine(name, stack);
    if(!name) return STRANGE_QUERY;
    if(!stack) return NO_ENTRY;

    machine* swaper = stack + 1;
    while(swaper->_name[0]) swaper++;
    swaper--;

    strcpy(stack->_name, swaper->_name);
    stack->_state = swaper->_state;
    swaper->_name[0] = '\0';
    swaper->_state = CLOSED;
    return OK;
}

answer _Exterminantus(char* name, machine* stack){
    for(; stack->_state != CANARY; stack++){
        stack->_name[0] = '\0';
        stack->_state = CLOSED;
    }

    return OK;
}

answer _Get(char* name, machine* stack){ return (name ? GET : STRANGE_QUERY); }
answer _List(char* name, machine* stack){ return LIST; }
answer _Exit_server(char* name, machine* stack){ return EXIT; }

char* _List_impl(char* buffer, machine* stack){
    strcpy(buffer, "\n");
    for(; stack->_state != CANARY; stack++){
        strcat(buffer, stack->_name);
        char* m_state;
        switch(stack->_state){
            case INITIAL: m_state = " -> initial\n"; break;
            case RUN: m_state = " -> running\n"; break;
            case PAUSE: m_state = " -> paused\n"; break;
            case CLOSED: m_state = " -> closed\n"; break;
        }
        strcat(buffer, m_state);
    }
    return buffer;
}

char* _Get_impl(char* buffer, machine* stack){
    char* name = strchr(buffer, '\0') + 1;
    if(!(stack = seek_machine(name, stack))) strcpy(buffer, "there is no that machne");
    else{
        strcpy(buffer, stack->_name);
        char* m_state;
        switch(stack->_state){
            case INITIAL: m_state = " -> initial\n"; break;
            case RUN: m_state = " -> running\n"; break;
            case PAUSE: m_state = " -> paused\n"; break;
            case CLOSED: m_state = " -> closed\n"; break;
        }
        strcat(buffer, m_state);
    }
    return buffer;
}
