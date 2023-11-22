/**
 * @file chararray.h
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Header file for chararray.c
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CHARARRAY_H
#define CHARARRAY_H


/**
 * @brief Creates new char array
 * 
 * @return char_array* 
 */
char* chararray_init ();

/**
 * @brief Adds a char to the char array
 * 
 * @param array 
 * @param c 
 */
void chararray_append (char** chararray, char c);

/**
 * @brief Adds a string to the char array
 * 
 * @param array 
 * @param c 
 */
void chararray_append_string(char **chararray, char* str);

/**
 * @brief Frees the char array
 * 
 * @param array 
 */
void chararray_free (char* chararray);


#endif