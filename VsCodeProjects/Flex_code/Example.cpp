// Example of using flex with C++
// flex file (example.l)
%{
#include <iostream>
%}
%%
[0-9]+  { std::cout << "Number: " << yytext << std::endl; }
[a-zA-Z]+ { std::cout << "Word: " << yytext << std::endl; }
.|\n    { /* Ignore other characters */ }
%%
int main() {
    yylex();
    return 0;
}