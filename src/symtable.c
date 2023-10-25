#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>

// Frame stack
bst_node_t* global_frame = NULL;

bst_node_t* temp_frame = NULL;
int exists_temp_frame = 0;

bst_node_t** local_frames;
int frame_stack_size = 0;
// TODO: Keep track of sizeof(local_frames) to avoid segfault

void symtable_init() {
    bst_init(&global_frame);    
	local_frames = malloc(sizeof(bst_node_t*) * 8);
}

void set_frame_root(frame_type frame_type, bst_node_t* new_root) {
    if (frame_type == LOCAL_FRAME) {
        if (local_frames[frame_stack_size - 1])
            //printf("Set frame root for LOCAL -> %s (was %s)\n", new_root->key, local_frames[frame_stack_size - 1]->key);
        local_frames[frame_stack_size - 1] = new_root;
    }
    else if (frame_type == TEMP_FRAME) {
        if (temp_frame)
            //printf("Set frame root for TEMP -> %s (was %s)\n", new_root->key, temp_frame->key);
        temp_frame = new_root;
    }
    else if (frame_type == GLOBAL_FRAME) {
        if (global_frame)
            //printf("Set frame root for GLOBAL -> %s (was %s)\n", new_root->key, global_frame->key);
        global_frame = new_root;
    }
    else {
        //printf("INTERNAL ERR: set_frame_root: unknown frame type %d\n", frame_type);
        exit(-1);
    }
}

SymbolData* get_symbol_from_frame(frame_type frame_type, char* symbol, symbol_missing follow_up) {
    bst_node_t* frame;
    if (frame_type == LOCAL_FRAME) {
        frame = local_frames[frame_stack_size - 1];
    }
    else if (frame_type == TEMP_FRAME) {
        frame = temp_frame;
    }
    else if (frame_type == GLOBAL_FRAME) {
        frame = global_frame;
    }
    else {
        //printf("INTERNAL ERR: get_symbol_from_frame: unknown frame type %d\n", frame_type);
        exit(-1);
    }


	SymbolData* data = bst_search(frame, symbol);
	if (data) {
		//printf("Symbol in %d symbol table.\n", frame_type);
		return data;
	}
	else {
        if (follow_up == CREATE_IF_MISSING) {
            //printf("Symbol not in symbol table, inserting...\n");
            data = calloc(1, sizeof(SymbolData));
            
            frame = bst_insert(&frame, symbol, data, NULL);
            set_frame_root(frame_type, frame);
            //printf("Get symbol %s from:\n", symbol);
            return data;
        }
        else if (follow_up == IGNORE_IF_MISSING) {
            //printf("Symbol not in symbol table, ignoring...\n");
            return 56;
        }
        else if (follow_up == ERROR_IF_MISSING) {
            //printf("Symbol not inf symbol table, raising error...\n");
            //TODO: my_exit(56);
        }
        else {
            //printf("INTERNAL ERR: get_symbol_from_frame: unknown follow_up resolution %d\n", follow_up);
            exit(-1);
        }
	}
}

SymbolData* get_symbol(char* symbol, symbol_missing follow_up, frame_type* found_frame_type) {
    //printf("Get symbol %s, followup %d\n", symbol, follow_up);
    SymbolData* result;
    // try find om temp frame if exists
    if (exists_temp_frame) {
        //printf(".. search in TEMP FRAME\n");
        result = get_symbol_from_frame(TEMP_FRAME, symbol, IGNORE_IF_MISSING);
        if (result){
            *found_frame_type = TEMP_FRAME;
            return result;
        }
    }

    // try find in local frame if exists
    if (frame_stack_size > 0) {
        //printf(".. search in LOCAL FRAME\n");
        if (frame_stack_size > 0 && local_frames[frame_stack_size - 1])
            //bst_print(local_frames[frame_stack_size - 1], 0);
        result = get_symbol_from_frame(LOCAL_FRAME, symbol, IGNORE_IF_MISSING);
        if (result){
            *found_frame_type = LOCAL_FRAME;
            return result;
        }
    }

    // try find in global frame if exists
        //printf(".. search in GLOBAL FRAME\n");
    result = get_symbol_from_frame(GLOBAL_FRAME, symbol, IGNORE_IF_MISSING);
    if (result){
        *found_frame_type = GLOBAL_FRAME;
        return result;
    }

    if (follow_up == IGNORE_IF_MISSING) {
        *found_frame_type = -1;
        return NULL;
    }

    if (follow_up == ERROR_IF_MISSING) {
        *found_frame_type = -1;
        //TODO: my_exit(56);
    }

    if (follow_up == CREATE_IF_MISSING) {
        if (exists_temp_frame) {
            //printf(".. create in TEMP FRAME\n");
            result = get_symbol_from_frame(TEMP_FRAME, symbol, CREATE_IF_MISSING);
            *found_frame_type = TEMP_FRAME;
            return result;
        }

        // try find in local frame if exists
        if (frame_stack_size > 0) {
            //printf(".. create in LOCAL FRAME\n");
            result = get_symbol_from_frame(LOCAL_FRAME, symbol, CREATE_IF_MISSING);
            *found_frame_type = LOCAL_FRAME;
            return result;
        }

        // try find in global frame if exists
            //printf(".. create in GLOBAL FRAME\n");
        result = get_symbol_from_frame(GLOBAL_FRAME, symbol, CREATE_IF_MISSING);
        *found_frame_type = GLOBAL_FRAME;
        return result;
    }

    //printf("INTERNAL ERR: get_symbol: unknown follow_up resolution %d\n", follow_up);
    exit(-1);
}

int create_frame() {
    // TODO: Free temp if exists
    exists_temp_frame = 1;
    bst_init(&temp_frame);
}

int push_frame() {
    if (!exists_temp_frame) {
        //printf("push_frame: no temp frame available\n");
        //TODO: my_exit(55);
    }

    local_frames[frame_stack_size] = temp_frame;
    exists_temp_frame = 0;
    bst_init(&temp_frame);
    frame_stack_size++;
}

int pop_frame() {
    // TODO: Free temp if exists
    if (frame_stack_size < 1) {
        //printf("pop_frame: no local frame available\n");
        //TODO: my_exit(55);
    }

    temp_frame = local_frames[frame_stack_size - 1];
    frame_stack_size--;
    exists_temp_frame = 1;
}

void bst_init(bst_node_t **tree) {
  *tree = NULL;
}

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
    exit(-1);
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
    exit(-1);
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