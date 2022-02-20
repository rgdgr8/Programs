%%
^[A]+[B]+ {printf("Accepted");}
.+ {printf("Rejected");}
%%

int yywrap(){return 1;}
int main(){yylex(); return 0;}
