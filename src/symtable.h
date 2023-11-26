/**
 * @file symtable.h
 * @author Samuel Lenčéš (xlogin00@vutbr.cz)	//TODO zmen si login Samo
 * @brief Header file for symtable.c
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SYMTABLE
#define SYMTABLE
#include "errors.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "types.h"
#include "stack.h"


typedef enum {
	GLOBAL_FRAME,
	TEMP_FRAME,
	LOCAL_FRAME
} frame_type;

typedef enum {
	CREATE_IF_MISSING, // create, insert and return an empty SymbolData
	IGNORE_IF_MISSING, // return NULL if not found
	ERROR_IF_MISSING, // run error.h
	CREATE,
	FIND,
	FIND_UNINITIALIZED
} symbol_missing;

/**
 * @brief Struct representing a variable
 * 
 */
typedef struct {
	int recursion_depth;
	int block_id;
	data_type type;
	int is_defined;
	int was_used;
	int is_initialized;			// avoid use before initialization
} VariableData;

/**
 * @brief Struct representing a parameter of a function.
 * 		  jméno_parametru  identifikátor_parametru:typ
 * 
 */
typedef struct
{
    char* name;
	char *identifier;
    data_type type;
} parameter;

/**
 * @brief Struct representing a function
 * 
 */
typedef struct {
	int is_declared;
	int is_defined;

	int num_of_params;
	parameter *parameters;
	
	data_type return_type;
} FunctionData;

/**
 * @brief Enum for symbol type
 * 
 */
typedef enum {
	VAR_DATA,
	FUNC_DATA
} symbol_type;

/**
 * @brief Union of VariableData and FunctionData
 * 
 */
typedef struct {
	symbol_type type;
	union { VariableData varData; FunctionData funcData; } data;
} SymbolData;

/**
 * @brief Node of binary search tree
 * 
 */
typedef struct bst_node {
  char* key;               // key of the node -> name of variable/function
  SymbolData* value;       // value of the node -> data about variable/function
  struct bst_node *parent;
  struct bst_node *left;  
  struct bst_node *right; 
} bst_node_t;

void symtable_init();

/**
 * @brief Get the block id of a variable marking its scope during definition
 * 
 * @param key 
 * @return char 
 */
void get_block_id(char* key, char* identifier);

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