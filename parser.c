#include <stdio.h>
#include "statem.h"

machine stack[5] = {
    {"", CLOSED},
    {"", CLOSED},
    {"", CLOSED},
    {"", CLOSED},
    {"", CANARY}
};

char* new_query(char* buffer){
    switch(read_query(buffer, stack)){
        case STRANGE_QUERY:
            return "strange query"; 
        case LIST:
            return _List_impl(buffer, stack); 
        case GET:
            return _Get_impl(buffer, stack); 
        case NO_ENTRY:
            return "there is no that machine"; 
        case ALREADY_CREATED:
            return "machine with that name already created"; 
        case COUNT_OVERFLOV:
            return "all machines busy"; 
        case LONG_NAME:
            return "to long name for machine (max 15)"; 
        case WRONG_STATE:
            return "not valid for current state"; 
        case OK:
            return "ok"; 
        case EXIT:
            return 0;
    }
    return "internal error: parser.c::new_query()";
}