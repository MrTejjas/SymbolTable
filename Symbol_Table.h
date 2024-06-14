# include<stdio.h>
# include<stdlib.h>
# include<string.h>

# ifndef SYMBOL_TABLE_H
# define SYMBOL_TABLE_H
# define TABLE_SIZE 101
# define WORD_SIZE 40
# define CHAR 1
# define INT 2
# define FLOAT 3
# define DOUBLE 4
# define STRING 5

typedef struct Symbol_Node{
    char *type;
    char *name;
    char *value;
    int size;
    struct Symbol_Node *next;
}Symbol_Node;

typedef struct Scope_Node{
    Symbol_Node *SymbolTable[TABLE_SIZE];
    struct Scope_Node *parent;
}Scope;

void *Initialize_Scope();

Symbol_Node* create_Symbol_Node(int type, char *name, char *value);

int hash_function(char *name);

void insert_node(int type, char *name,char *value);

void lookup(char *name, Scope *curr);

void print_value(char *name);

void Finalise_Scope();

int string_To_Integer(char *str);

float string_To_Float(char *str);

double string_To_Double(char *str);

char string_To_Char(char *str);

# define begin Initialize_Scope();
# define assign(type, name, value) insert_node(type, name, value)
# define print(name) print_value(name)
# define end Finalise_Scope();

# endif