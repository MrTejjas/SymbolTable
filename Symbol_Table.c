# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include"Symbol_Table.h"

Scope *current=NULL;

void *Initialize_Scope() {
    Scope *newScope=(Scope*)malloc(sizeof(Scope));
    for(int i=0; i<TABLE_SIZE; i++) {
        newScope->SymbolTable[i]=NULL;
    }
    newScope->parent=current;
    current=newScope;
}

Symbol_Node* create_Symbol_Node(int type, char *name, char *value) {
    Symbol_Node *newNode=(Symbol_Node*)malloc(sizeof(Symbol_Node));
    newNode->type=(char*)malloc(WORD_SIZE);
    newNode->name=(char*)malloc(WORD_SIZE);
    strcpy(newNode->name, name);
    newNode->value=(char*)malloc(WORD_SIZE);
    strcpy(newNode->value, value);
    switch (type) {
        case 1 : strcpy(newNode->type, "CHAR");
                 newNode->size=1;
                 break;
        case 2 : strcpy(newNode->type, "INT");
                 newNode->size=4;
                 break;
        case 3 : strcpy(newNode->type, "FLOAT");
                 newNode->size=4;
                 break;
        case 4 : strcpy(newNode->type, "DOUBLE");
                 newNode->size=8;
                 break;
        case 5 : strcpy(newNode->type, "STRING");
                 newNode->size=WORD_SIZE;
                 break;
        default :
                 printf("No such data type exist\n");
    }
    newNode->next=NULL;
    return newNode;
}

int hash_function(char *name) {
    int i=0;
    int index=0;
    while(name[i]!='\0') {
        index=index+name[i]*(i+1);
        i++;
    }
    return index%TABLE_SIZE;
}

void insert_node(int type, char *name,char *value) {
    Symbol_Node *newNode=create_Symbol_Node(type, name, value);
    int index=hash_function(name);
    if(current==NULL) {
        Initialize_Scope();
    }
    newNode->next=current->SymbolTable[index];
    current->SymbolTable[index]=newNode;
}

void lookup(char *name, Scope *curr) {
    int index=hash_function(name);
    if(curr==NULL) {
        printf("Error : %s is out of scope\n", name);
    }
    else {
        Symbol_Node *curr_node=curr->SymbolTable[index];
        while(curr_node!=NULL && strcmp(curr_node->name, name)!=0) {
            curr_node=curr_node->next;
        }
        if(curr_node!=NULL) {
            printf("%s = %s\n", curr_node->name, curr_node->value);
        }
        else {
            lookup(name, curr->parent);
        }
    }
}

void print_value(char *name) {
    lookup(name, current);
}

void Finalise_Scope() {
    Scope *temp=current;
    for(int i=0; i<TABLE_SIZE; i++) {
        if(current->SymbolTable[i]!=NULL) {
            while(current->SymbolTable[i]!=NULL) {
                Symbol_Node *temp=current->SymbolTable[i];
                current->SymbolTable[i]=temp->next;
                free(temp);
            }
        }
    }
    current=current->parent;
    free(temp);
}

int string_To_Integer(char *str) {
    int ans=0;
    int sign=0;
    int i=0;
    if(str[0]!='\0' && str[0]=='-') {
        sign=1;
        i=1;
    }
    while(str[i]!='\0') {
        ans=ans*10+(str[i]-48);
        i++;
    }
    if(sign==1) ans=-ans;
    return ans;
}

float string_To_Float(char *str) {
    float ans=0;
    int sign=0;
    int i=0;
    if(str[0]!='\0' && str[0]=='-') {
        sign=1;
        i=1;
    }
    while(str[i]!='\0' && str[i]!='.') {
        ans=ans*10+(str[i]-48);
        i++;
    }
    if(str[i]=='.') {
        float mul=0.1;
        i++;
        while(str[i]!='\0') {
            ans=ans+(str[i]-48)*mul;
            mul=mul*0.1;
            i++;
        }
    }
    if(sign==1) ans=-ans;
    return ans;
}

double string_To_Double(char *str) {
    double ans=0;
    int sign=0;
    int i=0;
    if(str[0]!='\0' && str[0]=='-') {
        sign=1;
        i=1;
    }
    while(str[i]!='\0' && str[i]!='.') {
        ans=ans*10+(str[i]-48);
        i++;
    }
    if(str[i]=='.') {
        double mul=0.1;
        i++;
        while(str[i]!='\0') {
            ans=ans+(str[i]-48)*mul;
            mul=mul*0.1;
            i++;
        }
    }
    if(sign==1) ans=-ans;
    return ans;
}

char string_To_Char(char *str) {
    return str[0];
}