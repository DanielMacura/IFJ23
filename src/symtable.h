#ifndef SYMTABLE
#define SYMTABLE
#include "error.h"
#include <stdbool.h>
#include <string.h>

typedef enum {
	GLOBAL_FRAME,
	TEMP_FRAME,
	LOCAL_FRAME
} frame_type;

typedef enum {
	CREATE_IF_MISSING, // create, insert and return an empty SymbolData
	IGNORE_IF_MISSING, // return NULL if not found
	ERROR_IF_MISSING // run error.h
} symbol_missing;
typedef struct {
	int is_declared;
	int data_type;
	int was_used;
} VariableData;

typedef struct {
	int is_declared;
	int is_defined;

	int param_length;
	int* param_list;
	
	int return_type;
} FunctionData;

typedef enum {
	VAR_DATA,
	FUNC_DATA
} symbol_type;

typedef struct {
	symbol_type type;
	union { VariableData varData; FunctionData funcData; } data;
} SymbolData;

typedef struct bst_node {
  char* key;               // kľúč
  SymbolData* value;       // hodnota TODO: nahradit
  struct bst_node *parent;
  struct bst_node *left;  // ľavý potomok
  struct bst_node *right; // pravý potomok
} bst_node_t;

void symtable_init();

SymbolData* get_symbol_from_frame(frame_type frame_type, char* symbol, symbol_missing follow_up);
SymbolData* get_symbol(char* symbol, symbol_missing follow_up, frame_type* found_frame_type);

int create_frame();
int pop_frame();
int push_frame();

void bst_init(bst_node_t **tree);
bst_node_t* bst_insert(bst_node_t **tree, char* key, SymbolData* value, bst_node_t* parent);
SymbolData* bst_search(bst_node_t *tree, char* key);
void bst_delete(bst_node_t **tree, char *key);
void bst_dispose(bst_node_t **tree);
//void bst_print(bst_node_t* node, int depth);


void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree);
void splay(bst_node_t *node);
void left_rotate(bst_node_t* node);
void right_rotate(bst_node_t* node);
void rotate_up(bst_node_t* node);
// TODO: Add bst_free(bst_node_t *node) to free key and value as well

#endif