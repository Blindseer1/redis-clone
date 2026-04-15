#include <cstring>
#include <string>

enum OP{
    ECHO, SET
};


//TODO: Implement a match for different data types and operations
//TODO: ????
//TODO: ????
//TODO: Return the final string?



void c_append(char *s, char c){
  int len = strlen(s);
  s[len] = c;
  s[len+1] = '\0';
}


const char* parser(char buf[1024]){
  char ans[1024]="";
  char len = buf[1];
  c_append(ans,len);


  const char* r = ans;
  return r;
}
