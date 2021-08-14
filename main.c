#include <stdio.h>
#include "statem.h"

int main(){
    char buffer[32*5];
    machine stack[5] = {
        {"", CLOSED},
        {"", CLOSED},
        {"", CLOSED},
        {"", CLOSED},
        {"", CANARY}
    };

    while(1){
        fgets(buffer, 32*5, stdin);
        answer sas = read_query(buffer, stack);
        char* waw;
        switch(sas){
            case STRANGE_QUERY:
                waw = "strange query"; break;
            case LIST:
                waw = _List_impl(buffer, stack); break;
            case GET:
                waw = _Get_impl(buffer, stack); break;
            case NO_ENTRY:
                waw = "there is no that machine"; break;
            case ALREADY_CREATED:
                waw = "machine with that name already created"; break;
            case COUNT_OVERFLOV:
                waw = "all machines busy"; break;
            case LONG_NAME:
                waw = "to long name for machine (max 15)"; break;
            case WRONG_STATE:
                waw = "not valid for current state"; break;
            case OK:
                waw = "ok"; break;
            case EXIT:
                return 0;
        }
        puts(waw);
    }
}