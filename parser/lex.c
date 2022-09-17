#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "keyword_table.c"
#include "symbolTable.c"
#include "lexical.h"
#define STATES 24

int acc_states[STATES];
int dfa[STATES][128];
node *tok;
FILE* fp;
int line_no = 0;
int char_no = 0;
char buffer[500];
int buf_ln = 0;
int buf_ind = 0;
void init();
void lex(){
	if(buf_ind>=buf_ln){
		if(fscanf(fp, "%[^\n]%*c", buffer)==-1){
			tok->sym = '$';
			return;
		}
		buf_ln = strlen(buffer);
		buffer[buf_ln++] = '\n';
		buffer[buf_ln] = '\0';
		buf_ind = 0;
		line_no++;
	}
	//printf("buffer: %s, buf_ln: %d, buf_ind: %d\n",buffer,buf_ln,buf_ind);

	char token[50];
	int l = 0;
	int state = 0;
	while(buf_ind<buf_ln){
		char c = buffer[buf_ind++];
		char_no++;
		
		int x = dfa[state][c];
		//printf("newstate: %d, curstate: %d, c: %c, buf_ind: %d\n", x, state, c, buf_ind);
		if(x==0){
			if(state!=0){
				token[l] = '\0';
				printf("token found: %s, size: %d\n",token,l);

				int num = get_code(token);//search in keyword table
				if(num==-1){
					symbolinfo* y = look_up(token);//search in symbol table
					if(y==NULL){
						num = acc_states[state];
						if(isdigit(token[0]))
							tok->info.intlit_node.value = atoi(token);
						else if(isalpha(token[0]))
							strcpy(tok->info.id_node.name, token);
					}
					else{
						num = __type__;
						tok->info.type_node.basetype = y->basetype;
						tok->info.type_node.dim = y->dim;
					}
				}
				tok->sym = num;
				buf_ind--;
				char_no--;
				return;
			}
		}
		else if(x==-1){
			token[l] = '\0';
			/*if(strcmp(token,"main")==0 && c=='('){
				printf("token found: %s, size: %d\n",token,l);
				tok->sym = get_code(token);
				buf_ind--;
				char_no--;
				return;
			}else{*/
				printf("Invalid Token in line %d, char %d\n",line_no, char_no);
				exit(1);
			//}
		}

		state = x;
		if((c!=' ' && c!='\t') || (l>0 && (token[0]=='\'' || token[0]=='"')))
			token[l++] = c;
	}
	tok->sym = -1;
}

void init(){
	store_keywords();
	init_symbol_table();

	for(int i=0;i<STATES;i++){
		for(int j=0;j<128;j++)
			if(i==0){
				if(isalpha(j))
					dfa[i][j] = 1;
				else if(isdigit(j))
					dfa[i][j] = 2;
				else if(j=='"')
					dfa[i][j] = 3;
				else if(j=='\'')
					dfa[i][j] = 5;
				else if(j=='=')
					dfa[i][j] = 8;
				else if(j=='+')
					dfa[i][j] = 10;
				else if(j=='-')
					dfa[i][j] = 11;
				else if(j=='*')
					dfa[i][j] = 12;
				else if(j=='^')
					dfa[i][j] = 13;
				else if(j=='[')
					dfa[i][j] = 14;
				else if(j==']')
					dfa[i][j] = 15;
				else if(j=='(')
					dfa[i][j] = 16;
				else if(j==')')
					dfa[i][j] = 17;
				else if(j=='{')
					dfa[i][j] = 18;
				else if(j=='}')
					dfa[i][j] = 19;
				else if(j=='>')
					dfa[i][j] = 20;
				else if(j=='<')
					dfa[i][j] = 21;
				else if(j==';')
					dfa[i][j] = 22;
				else if(j==',')
					dfa[i][j] = 23;
				else if(j==' ' || j=='\t' || j=='\n')
					dfa[i][j] = 0;
				else
					dfa[i][j] = -1;
			}
			else if(i==1){
				if(isalnum(j))
					dfa[i][j] = 1;
				else if(j==' ' || j=='\t' || j==',' || j==';' || j=='+' || j=='-' || j=='^' || j=='=' || j=='>' || j=='<' || j=='(' || j==')' || j=='[' || j==']')
					dfa[i][j] = 0;
				else
					dfa[i][j] = -1;
			}
			else if(i==2){
				if(isdigit(j))
					dfa[i][j] = 2;
				else if(j==' ' || j=='\t' || j==',' || j==';' || j=='+' || j=='-' || j=='^' || j=='>' || j=='<' || j==']')
					dfa[i][j] = 0;
				else
					dfa[i][j] = -1;
			}
			else if(i==3){
				if(j=='"')
					dfa[i][j] = 4;
				else
					dfa[i][j] = 3;
			}
			else if(i==5){
				if(j=='\'')
					dfa[i][j] = -1;
				else
					dfa[i][j] = 6;
			}
			else if(i==6){
				if(j=='\'')
					dfa[i][j] = 7;
				else
					dfa[i][j] = -1;
			}
			else if(i==8){
				if(j=='=')
					dfa[i][j] = 9;
				else
					dfa[i][j] = 0;
			}
			else{
				dfa[i][j] = 0;
			}
	}

	acc_states[1] = __id__;
	acc_states[2] = __intlit__;
	acc_states[4] = __stringlit__;
	acc_states[7] = __charlit__;
	acc_states[9] = __eq__;
	acc_states[8] = '=';
	acc_states[10] = '+';
	acc_states[11] = '-';
	acc_states[12] = '*';
	acc_states[13] = '^';
	acc_states[14] = '[';
	acc_states[15] = ']';
	acc_states[16] = '(';
	acc_states[17] = ')';
	acc_states[18] = '{';
	acc_states[19] = '}';
	acc_states[20] = '>';
	acc_states[21] = '<';
	acc_states[22] = ';';
	acc_states[23] = ',';
	
	//char fn[50];
	tok = (node*)malloc(sizeof(node));
	tok->sym = -1;
	//printf("Enter c program file name: ");
	//scanf("%s",fn);
	fp = fopen("x.c", "r");
}

int main(){
	init();
	lex();
	while(tok->sym!='$'){
		if(tok->sym!=-1)
			printf("%d\n",tok->sym);
		lex();
	}
}
