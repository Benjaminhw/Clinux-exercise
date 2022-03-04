#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
int main(){ 
    pid_t pid = fork(); 
    if( pid == 0 ) { 
        exit(10); 
    }
    else{ 
        sleep(10);
    } 
}