//main.c
 
 #include <stdio.h> 
 #include <string.h> 
 int main() 
 { 
     execl("./add.exe" ,"add.exe" ,"3" , "4" , NULL);
     return 0; 
 }