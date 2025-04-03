#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>

#define max 100
int n;
char prod[max][max][max];
char rhs[max][max][max];
char first[max][max];
char follow[max][max];
char nonterminal[max];

void addset(char *set, char c){
    if(strchr(set,c)) return;
    int len  = strlen(set);
    set[len] = c;
    set[len+1] = '\0';
}


void first_compute(int index){
    if(first[index][0] !='\0'){
        for(int i = 0;rhs[index][i][0];i++){
            char *prod = rhs[index][i];
            if(!isupper(prod[0]) || prod[0]=='#'){
                addset(first[index],prod[0]);
            }
            for(int j = 0; j<n;j++){
                if(prod[0]==nonterminal[j]){
                    first_compute(j);
                    for(int k =0 ;first[j][k];k++){
                        if(first[j][k] !='#'){
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
    while(change){
        change = 0;
        for(int i=0;i<n;i++){
            for(int j =0 ;rhs[i][j];j++){
                for(int k = 0 ;rhs[i][j][k];k++){
                   if(!isupper(rhs[i][j][k])){
                    addset(follow[i],rhs[i][j][k]);
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
        fgets(input,200,stdin);
        input[strchr(input,"|")] = 0;
        nonterminal[i] = input[0];
        token = strtok(input,"|");
        int j =0;
        while(token){
            strcpy(rhs[i][j++],token);
            token = strtok(NULL,"|");
        }
    }
    for(int i =0 ;i<n ;i++){
        first_compute(i);
    }
    // follow();
}
