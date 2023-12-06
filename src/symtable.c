/**
 * @file symtable.c
 * @author Samuel Lenčéš (xlogin00@vutbr.cz)	//TODO zmen si login Samo
 * @brief Implementation of symtable for storing variables and functions
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "symtable.h"


extern error_code ERROR;
extern int block_counter;
extern int recursion_counter;
extern Stack *block_stack;
extern Stack *recursion_stack;

// Frame stack
bst_node_t* global_frame = NULL;

bst_node_t* temp_frame = NULL;
int exists_temp_frame = 0;

bst_node_t** local_frames;
int frame_stack_size = 0;
// TODO: Keep track of sizeof(local_frames) to avoid segfault

/**
 * @brief Initialize the symbol table
 * 
 */
void symtable_init() {
  bst_init(&global_frame);    
	local_frames = malloc(sizeof(bst_node_t*) * 8);
  // TODO: Keep track of sizeof(local_frames) to avoid segfault

}

/**
 * @brief Iterates through the symbol table and checks if all functions were defined
 * 
 */
void symtable_check_functions(){
  bst_node_t* node = global_frame;
  //iterate dfs through the tree
  while (node != NULL)
  {
    if (node->value->type == FUNC_DATA && node->value->data.funcData.is_declared == 0 )
    {
      set_error(UNDEFINED_FUNCTION_ERR);
      return;
    }
    if (node->left != NULL)
    {
      node = node->left;
    }
    else if (node->right != NULL)
    {
      node = node->right;
    }
    else
    {
      while (node->parent != NULL && (node->parent->right == NULL || node->parent->right == node))
      {
        node = node->parent;
      }
      if (node->parent == NULL)
      {
        break;
      }
      node = node->parent->right;
    }
  }
}

/**
 * @brief Get the highest block id of a variable marking its scope during definition, that IS NOT
 *        higher than the current block id.
 * 
 * @param key 
 */
void get_block_id(char* key, char *identifier) {
  SymbolData *symbol =  get_symbol_from_frame(LOCAL_FRAME, key, FIND);
  if (symbol) {
    if (symbol->type == FUNC_DATA)
    {
      set_error(UNDEFINED_VAR_ERR);
      return ;
    }
    memset(identifier, 0, 1024);
    sprintf(identifier, "%d_%d", symbol->data.varData.recursion_depth ,symbol->data.varData.block_id);
    return;
  }
  else {
    set_error(UNDEFINED_VAR_ERR);
    return;
  }
}

/**
 * @brief Set the frame root node
 * 
 * @param frame_type Which frame to set
 * @param new_root The new root node
 */
void set_frame_root(frame_type frame_type, bst_node_t* new_root) {
    if (frame_type == LOCAL_FRAME) {
        //if (local_frames[frame_stack_size - 1])
            //printf("Set frame root for LOCAL -> %s (was %s)\n", new_root->key, local_frames[frame_stack_size - 1]->key);
        local_frames[frame_stack_size - 1] = new_root;
    }
    else if (frame_type == TEMP_FRAME) {

            //printf("Set frame root for TEMP -> %s (was %s)\n", new_root->key, temp_frame->key);
      temp_frame = new_root;
    }
    else if (frame_type == GLOBAL_FRAME) {

    global_frame = new_root;
        
    //printf("Set frame root for GLOBAL -> %s (was %s)\n", new_root->key, global_frame->key);
    }
    else {
        set_error(INTERNAL_ERR); //FIXME: //TODO: treba pekne sa vratit, nie exit koli freeom v maine
        return;
    }
}

/**
 * @brief Get the symbol from frame object
 * 
 * @param frame_type 
 * @param symbol 
 * @param follow_up 
 * @return SymbolData* 
 */
SymbolData* get_symbol_from_frame(frame_type frame_type, char* symbol, symbol_missing follow_up) {
    bst_node_t* frame;
    int searched_local_frame = frame_stack_size -1;

    while (frame_type == LOCAL_FRAME && searched_local_frame >= 0 && (follow_up == FIND|| follow_up == FIND_UNINITIALIZED)) 
    {
      frame = local_frames[searched_local_frame];
      SymbolData* data = bst_search(frame, symbol);
      if (data)
      {
        if (data->data.varData.recursion_depth > peek(recursion_stack))
        {
          searched_local_frame--;
          continue;
        }
        else if(data->data.varData.block_id != peek(block_stack) && data->data.varData.recursion_depth == peek(recursion_stack)) {
          searched_local_frame--;
          continue;
        }
        else if(data->data.varData.is_initialized == 0 && follow_up == FIND) {
          searched_local_frame--;
          continue;
        }

        return data;
      }
      else {
        if(searched_local_frame == 0) {   // means we searched all frames and did not find so we return
          return NULL;
        }
        searched_local_frame--;
      }
    }
    if (frame_type == LOCAL_FRAME  && (follow_up == FIND||follow_up == FIND_UNINITIALIZED))
    {
      return NULL; // we did not find the symbol in any frame in previous while loop
    }
    

    if (frame_type == LOCAL_FRAME) {
      frame = local_frames[frame_stack_size - 1];
    }
    // else if (frame_type == TEMP_FRAME) {
    //     frame = temp_frame;
    // }
    else if (frame_type == GLOBAL_FRAME) {
        frame = global_frame;
    }
    else {
        set_error(INTERNAL_ERR); //FIXME: //TODO: treba pekne sa vratit, nie exit koli freeom v maine
        return NULL;
    }


  SymbolData* data = bst_search(frame, symbol);


  if (data)
  { 
    if(data && frame_type == GLOBAL_FRAME && follow_up == CREATE && data->data.funcData.is_declared) {    // Function redefinition
      set_error(UNDEFINED_FUNCTION_ERR);
      return NULL;
    }
    return data;
  }
  else {
    if ((follow_up == CREATE_IF_MISSING || follow_up == CREATE)&& frame_type == LOCAL_FRAME) {
      data = calloc(1, sizeof(SymbolData));
      data->data.varData.block_id = peek(block_stack);
      data->data.varData.recursion_depth = peek(recursion_stack);
      data->data.varData.is_initialized = 0;
      data->type = VAR_DATA;
      frame = bst_insert(&frame, symbol, data, NULL);
      set_frame_root(frame_type, frame);
      return data;
    }
    else if(frame_type == GLOBAL_FRAME && (follow_up == CREATE)){   // Function definition
      data = calloc(1, sizeof(SymbolData));
      data->type = FUNC_DATA;
      frame = bst_insert(&frame, symbol, data, NULL);
      data->data.funcData.is_declared = 1;
      data->data.funcData.is_called = 0;
      set_frame_root(frame_type, frame);
      return data;
    }
    else if(frame_type == GLOBAL_FRAME && (follow_up == CREATE_IF_MISSING )){ // Function was called, add to symtable but do not define
      data = calloc(1, sizeof(SymbolData));
      data->type = FUNC_DATA;
      frame = bst_insert(&frame, symbol, data, NULL);
      data->data.funcData.is_called = 0;
      data->data.funcData.is_declared = 0;
      set_frame_root(frame_type, frame);
      return data;
    }
    else if ((follow_up == FIND ) && frame_type == GLOBAL_FRAME){    // Function not defined
      set_error(UNDEFINED_FUNCTION_ERR);
      return NULL;
    }
    else if ((follow_up == FIND ) && frame_type == LOCAL_FRAME){   // Variable not defined
      set_error(UNDEFINED_VAR_ERR);
      return NULL;
    }
    else if (follow_up == IGNORE_IF_MISSING) {                     //FIXME: //TODO: warning: returning ‘int’ from a function with return type ‘SymbolData *’ makes pointer from integer without a cast [-Wint-conversion]
        //printf("Symbol not in symbol table, ignoring...\n");
        return NULL;
    }
    else {
        //printf("INTERNAL ERR: get_symbol_from_frame: unknown follow_up resolution %d\n", follow_up);
        set_error(INTERNAL_ERR);

        return NULL;
    }
	}
  return NULL;  //FIXME: //TODO: warning: control reaches end of non-void function [-Wreturn-type]
}

/**
 * @brief Get the the symbol from frames, in order of priority: TEMP, LOCAL, GLOBAL
 * 
 * @param symbol 
 * @param follow_up 
 * @param found_frame_type 
 * @return SymbolData* 
 */
SymbolData* get_symbol(char* symbol, symbol_missing follow_up, frame_type* found_frame_type) {
    //printf("Get symbol %s, followup %d\n", symbol, follow_up);
    SymbolData* result;
    // try find om temp frame if exists
    if (follow_up != CREATE)
    {
      // if (exists_temp_frame) {
      //     //printf(".. search in TEMP FRAME\n");
      //     result = get_symbol_from_frame(TEMP_FRAME, symbol, IGNORE_IF_MISSING);
      //     if (result){
      //         *found_frame_type = TEMP_FRAME;
      //         return result;
      //     }
      // }

      // try find in local frame if exists
      if (frame_stack_size > 0) {
          //printf(".. search in LOCAL FRAME\n");
          if (frame_stack_size > 0/* && local_frames[frame_stack_size - 1]*/){
            result = get_symbol_from_frame(LOCAL_FRAME, symbol, IGNORE_IF_MISSING);
          }
          if (result){
              *found_frame_type = LOCAL_FRAME;
              return result;
          }
      }

      // // try find in global frame if exists
      //     //printf(".. search in GLOBAL FRAME\n");
      // result = get_symbol_from_frame(GLOBAL_FRAME, symbol, IGNORE_IF_MISSING);
      // if (result){
      //     *found_frame_type = GLOBAL_FRAME;
      //     return result;
      // }
    }

    if (follow_up == FIND || follow_up == FIND_UNINITIALIZED){
      if (frame_stack_size > 0) {
          //printf(".. search in LOCAL FRAME\n");
          if (frame_stack_size > 0/* && local_frames[frame_stack_size - 1]*/){
            result = get_symbol_from_frame(LOCAL_FRAME, symbol, follow_up);
          }
          if (result){
              *found_frame_type = LOCAL_FRAME;
              return result;
          }
      }

    }
    

    if (follow_up == IGNORE_IF_MISSING) {
        *found_frame_type = -1;
        return NULL;
    }

    if (follow_up == ERROR_IF_MISSING) {
        *found_frame_type = -1;
        set_error(INTERNAL_ERR);
        return NULL;
    }

    if (follow_up == CREATE_IF_MISSING || follow_up == CREATE) {
        // if (exists_temp_frame) {
        //     //printf(".. create in TEMP FRAME\n");
        //     result = get_symbol_from_frame(TEMP_FRAME, symbol, follow_up);
        //     *found_frame_type = TEMP_FRAME;
        //     return result;
        // }

        // try find in local frame if exists
        if (frame_stack_size > 0) {
            //printf(".. create in LOCAL FRAME\n");
            result = get_symbol_from_frame(LOCAL_FRAME, symbol, follow_up);
            *found_frame_type = LOCAL_FRAME;
            return result;
        }

        // // try find in global frame if exists
        //     //printf(".. create in GLOBAL FRAME\n");
        // result = get_symbol_from_frame(GLOBAL_FRAME, symbol, follow_up);
        // *found_frame_type = GLOBAL_FRAME;
        // return result;
    }

    //printf("INTERNAL ERR: get_symbol: unknown follow_up resolution %d\n", follow_up);
    set_error(INTERNAL_ERR);
    return NULL;
}

/**
 * @brief Allocate a new frame
 * 
 * @return int 
 */
int create_frame() {
    // TODO: Free temp if exists
    exists_temp_frame = 1;
    bst_init(&temp_frame);
    //generatePrint("CREATEFRAME\n");
    return 0;  //FIXME: //TODO: warning: control reaches end of non-void function [-Wreturn-type]
}

/**
 * @brief Push the temp frame to the local frame stack
 * 
 * @return int 
 */
int push_frame() {
    if (!exists_temp_frame) {
        //printf("push_frame: no temp frame available\n");
        set_error(INTERNAL_ERR);
        //TODO: my_exit(55);
        return -1;
    }
    push(block_stack, block_counter);
    block_counter++;

    push(recursion_stack, recursion_counter);
    recursion_counter++;
    //generatePrint("PUSHFRAME\n");

    local_frames[frame_stack_size] = temp_frame;


    exists_temp_frame = 0;
    bst_init(&temp_frame);

    frame_stack_size++;
    //set_frame_root(LOCAL_FRAME, local_frames[frame_stack_size - 1]);
    return 0; // FIXME: //TODO: warning: control reaches end of non-void function [-Wreturn-type]
}

/**
 * @brief Pop the local frame stack to the temp frame
 * 
 * @return int 
 */
int pop_frame() {
    // TODO: Free temp if exists
    if (frame_stack_size < 1) {
        //printf("pop_frame: no local frame available\n");
        set_error(INTERNAL_ERR);
        return -1;
        //TODO: my_exit(55);
    }
    pop(block_stack);
    pop(recursion_stack);
    recursion_counter--;
    //generatePrint("POPFRAME\n");

    temp_frame = local_frames[frame_stack_size - 1];
    frame_stack_size--;
    exists_temp_frame = 1;
    return 0;  //FIXME: //TODO: warning: control reaches end of non-void function [-Wreturn-type]

}

/**
 * @brief Initialize a binary search tree
 * 
 * @param tree 
 */
void bst_init(bst_node_t **tree) {
  *tree = NULL;
}

/**
 * @brief Search for a key in a binary search tree
 * 
 * @param tree 
 * @param key 
 * @return SymbolData* 
 */
SymbolData* bst_search(bst_node_t *tree, char* key) {
  if (tree == NULL) {
    return NULL;
  }

  if (strcmp(tree->key, key) == 0){
    return tree->value;
  }


  if (strcmp(key, tree->key) < 0){
    return bst_search(tree->left, key);
  } else {
    return bst_search(tree->right, key);
  }
}

/**
 * @brief Insert a new node into a binary search tree
 * 
 * @param tree The tree to insert into
 * @param key Name of the variable/function 
 * @param value Data about the variable/function
 * @param parent Parent of the new node, may be NULL
 * @return bst_node_t* 
 */
bst_node_t* bst_insert(bst_node_t **tree, char* key, SymbolData* value, bst_node_t* parent) {
  if ((*tree) == NULL){

    bst_node_t *new_node = malloc(sizeof(bst_node_t));
    if (new_node == NULL) {
      return NULL;
    }
    new_node->key = key;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = parent;
    //DEBUG
    if(new_node->parent) {
      if (strcmp(key, parent->key) < 0) {
        parent->left = new_node;
      }
      else {
        parent->right = new_node;
      }
    }
    splay(new_node);
    //*tree = new_node;
    return new_node;
  }
  if (strcmp(key, (*tree)->key) < 0){
    return bst_insert(&(*tree)->left, key, value, *tree);
  } else if (strcmp(key, (*tree)->key) > 0) {
    return bst_insert(&(*tree)->right, key, value, *tree);
  } else {
    //printf("bst_insert: Replacing existing node %s\n", key);
    set_error(INTERNAL_ERR);
    return NULL;
  }
}


void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
  if ((*tree)->right != NULL){
    bst_replace_by_rightmost(target, &(*tree)->right);
  } else {
    target->value = (*tree)->value;
    target->key = (*tree)->key;
    bst_node_t *rightmost = (*tree);
    (*tree) = (*tree)->left;
    free(rightmost);
  }
}


void bst_delete(bst_node_t **tree, char* key) {
  if ((*tree) == NULL) return;

  if (strcmp(key, (*tree)->key) < 0) {
    bst_delete(&(*tree)->left, key);
  } else if (strcmp(key, (*tree)->key) > 0) {
    bst_delete(&(*tree)->right, key);
  } else if ((*tree)->left == NULL && (*tree)->right == NULL) {   //nema podstro //TODO: my
    free((*tree));
    (*tree) = NULL;
  } else if ((*tree)->left != NULL && (*tree)->right == NULL) {   //ma lavy podstrom
    bst_node_t *tbd = (*tree);    //to be deleted
    *tree = (*tree)->left;
    free(tbd);
  } else if ((*tree)->left == NULL && (*tree)->right != NULL) {   //ma pravy podstrom
    bst_node_t *tbd = (*tree);
    *tree = (*tree)->right;
    free(tbd);
  } else {    //ma oba podstro//TODO:  my
    bst_replace_by_rightmost((*tree), &((*tree)->left));
  }
}

void bst_dispose(bst_node_t **tree) {
  if((*tree) != NULL) {
    bst_dispose(&(*tree)->left);
    bst_dispose(&(*tree)->right);
    free(*tree);
    *tree = NULL;
  }
}



void left_rotate(bst_node_t* node) {
  /*   P              X   
  //  / \            / \  
  // A   X    ->    P   C 
  //    / \        / \    
  //   B   C      A   B   */
  
  if (!node->parent) return; // Error

  bst_node_t* parent = node->parent;
  bst_node_t* b = node->left;
  bst_node_t* pp = parent->parent;
  
  node->left = parent;
  parent->parent = node;

  node->parent = pp;
  if (pp) {
    if (pp->left == parent)
      pp->left = node;
    else
      pp->right = node;
  }

  parent->right = b;
  if(b)
    b->parent = parent;
}


void right_rotate(bst_node_t* node) {
  /*      P             X
  //     / \           / \
  //    X   C   ->    A   P
  //   / \               / \
  //  A   B             B   C*/

  if (!node->parent) return; // Error

  bst_node_t* parent = node->parent;
  bst_node_t* b = node->right;
  bst_node_t* pp = parent->parent;
  
  node->right = parent;
  parent->parent = node;
  
  node->parent = pp;
  if (pp) {
    if (pp->left == parent)
      pp->left = node;
    else
      pp->right = node;
  }

  parent->left = b;
  if(b)
    b->parent = parent;
}

void rotate_up(bst_node_t* node) {
  if (node->parent->left == node) {
    right_rotate(node);
  }
  else if (node->parent->right == node) {
    left_rotate(node);
  }
  else {
    //printf("Invalid tree structure, parent %s has no child %s\n", node->parent->key, node->key);
    set_error(INTERNAL_ERR);
    return;
  }
}


void splay(bst_node_t *node) {
  while (node && node->parent) {
    // ZIG
    if (!node->parent->parent) {
      rotate_up(node);
      return;
    }
    int is_node_left = node->parent->left == node;
    int is_parent_left = node->parent->parent->left == node->parent;

    // ZIG-ZIG
    if (is_node_left && is_parent_left) {
      rotate_up(node->parent);
      rotate_up(node);
      continue;
    }

    // ZIG-ZAG
    else {
      rotate_up(node);
      rotate_up(node);
      continue;
    }
  }
}