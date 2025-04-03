#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define max 100

int n;
char prod[max][max][max];
char first[max][max];
char follow[max][max];
char rhs[max][max][max];
char nonterminal[max];
int isnonterminal(char c){
    return (c >= 'A' && c <= 'Z');
}

void addset(char * set,char c){
    if(strchr(set,c)) return ;
    int len = strlen(set);
    set[len] = c;
    set[len +1] = '\0';
}



void first_compute(int index){
    if(first[index][0]) return ;
    for(int i =0 ;rhs[index][i][0];i++){
        char *production = rhs[index][i];
        if(!isnonterminal(production[0]) && production[0]=='#'){
            addset(first[index],production[0]);
        }
        else{
            for(int j = 0;j<n;j++){
                if(nonterminal[j]==rhs[index][i][0]){
                    first_compute(j);
                    for(int k =0 ;first[j][k];k++){
                        if(first[j][k]!='#'){
                            addset(first[index],first[j][k]);
                        }
                    }
                }
            }
        }
    }
}

void follow_compute(){
    addset(follow[0],'$');
    int change =1;
    for(int i =0;i<n;i++){
        for(int j =0;rhs[i][j];j++){
            for(int k =0 ;rhs[i][j][k];k++){
                if(!isnonterminal(rhs[i][j][k])){
                    int idx = strchr(nonterminal,rhs[i][j][k]) - nonterminal;
                    int next = k+1;
                    while(rhs[i][j][next]){
                        if(!isnonterminal(rhs[i][j][next])){
                            addset(follow[idx],rhs[i][j][next]);
                            break;
                        }
                        int next_idx = strchr(nonterminal,rhs[i][j][next]) - nonterminal;
                        for(int m =0; first[next_idx][m];m++){
                            if(first[next_idx][m]!='#'){
                                addset(follow[idx],first[next_idx][m]);
                            }
                        }
                        if (!strchr(first[next_idx], 'e')) break;
                            next++;
                        
                    }
                    if(!rhs[i][j][next]) {
                        for (int m = 0; follow[i][m]; m++) {
                            if (!strchr(follow[idx], follow[i][m])) {
                                addset(follow[idx], follow[i][m]);
                                change = 1;
                            }
                        }
                    }
                    
                }
            }
        }
    }
}


int main(){
    scanf("%d",&n);
    getchar();
    for(int i =0 ;i<n;i++){
        char input[200],*token;
        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"|")]=0;
        nonterminal[i] = input[0];
        token = strtok(input ,"|");
        int j = 0;
        while(token){
            strcpy(rhs[i][j++],token);
            token = strtok(NULL,"|");
        }
    }
    for(int i =0;i<n;i++){
        first_compute(i);
    }
    follow_compute();
    for (int i = 0; i < n; i++)
    printf("FIRST(%c) = { %s }\n", nonterminal[i], first[i]);
for (int i = 0; i < n; i++)
    printf("FOLLOW(%c) = { %s }\n", nonterminal[i], follow[i]);
return 0;
}