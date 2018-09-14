//
//  core.c
//  Project 1
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdbool.h>

#include "core.h"

#define CHARACTER_COUNT (LAST_CHARACTER - FIRST_CHARACTER + 1)
#define FIRST_CHARACTER 'A'
#define LAST_CHARACTER 'Z'

#define TRUE 1;
#define FALSE 0;

//Samantha's macros
#define ALPHABET_LENGTH 26
#define A_VALUE 65
#define Z_VALUE 90

#define LOWER_A_VALUE 97
#define LOWER_Z_VALUE 122

int is_number_convertable(const char * string) {
    int len = strlen(string);
    const char * s = string;

    for (int i = 0; i < len; i++) {
        if (!isdigit(*s)) {
            return FALSE;
        }
        s++;
    }

    return TRUE;
}

char encrypt_character(char source, int key)
{
    int convert = source; // the char we are encrypting

    if (key > ALPHABET_LENGTH) // if the key is large
    {
        key = key % ALPHABET_LENGTH;
    }
    else if (key <= 0) // if the key is negative or zero
    {
        return (char)source; //do not offset
    }

    if (source >= 'A' && source <= 'Z') //uppercase letter
    {
        convert += key; //offset the char
        if ((int)convert > Z_VALUE)
        {
            int overflow = (int)convert - Z_VALUE;
            convert = A_VALUE - 1 + overflow;
        }
        return (char)convert;
    }
    else if (source >= 'a' && source <= 'z') //lowercase letter
    {
        convert += key; //offset the char
        if ((int)convert > LOWER_Z_VALUE)
        {
            int overflow = (int)convert - LOWER_Z_VALUE;
            convert = LOWER_A_VALUE - 1 + overflow;
        }
        return (char)convert;
    }
    else //symbol or punctuation
    {
        //do not encrypt
        return (char)source;
    }
}

void encrypt_string(char * message, int key, int step)
{
    //step is the amount we are incrementing each time
    char curmsg[100]; //the current encryption message we have so far

    //for each char in the message
    for (int i = 0; i <= strlen(message); i++)
    {
        //encryption section
        char source = message[i]; //the original unencrypted char
        curmsg[i] = encrypt_character(source, key); //add encrypted char to the current message

        //key section
        key += step; //add step to key to update
    }

    strncpy(message, curmsg, strlen(message)); //copy encrypted message (curmsg) to message
}

char decrypt_character(char source, int key)
{
    char convert = source; // the char we are decrypting

    if (key > ALPHABET_LENGTH) // if the key is large
    {
        key = key % ALPHABET_LENGTH;
    }
    else if (key <= 0) // if the key is negative or zero
    {
        return source; //do not offset
    }

    if (source >= 'A' && source <= 'Z') //uppercase letter
    {
        convert -= key; //offset the char
        if ((int)convert < A_VALUE)
        {
            int underflow = A_VALUE - (int)convert;
            convert = Z_VALUE + 1 - underflow;
        }
        return convert;
    }
    else if (source >= 'a' && source <= 'z') //lowercase letter
    {
        convert -= key; //offset the char
        if ((int)convert < LOWER_A_VALUE)
        {
            int underflow = LOWER_A_VALUE - (int)convert;
            convert = LOWER_Z_VALUE + 1 - underflow;
        }
        return convert;
    }
    else //symbol or punctuation
    {
        //do not encrypt
        return source;
    }
}

void decrypt_string(char * message, int key, int step)
{
    //step is the amount we are incrementing each time
    char curmsg[100]; //the current decrypted message we have so far

    //for each char in the message
    for (int i = 0; i <= strlen(message); i++)
    {
        //decryption section
        char source = message[i]; //the encrypted char
        curmsg[i] = decrypt_character(source, key); //add decrypted char to the current message

        //key section
        key += step; //add step to key to update
    }

    strncpy(message, curmsg, strlen(message)); //copy decrypted message (curmsg) to message
}

//function to convert const char * to lowercase
void lowercase(const char *cstr)
{
    char *str = (char*)cstr;

    while (*str) {
        *str = tolower(*str);
        ++str;
    }
}

void print_usage()
{
    printf("Usage:\n");
    printf("\t./main encrypt message key key_offset\n");
    printf("\t./main decrypt message key key_offset\n");
}

int core_main(int argc, const char * argv[])
{
    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
    {
      printf("Missing arguments\n");
      print_usage();
    }
    else
    {
      char type[10]; //the command line argument (encrypt or decrypt)
      strcpy(type, argv[1]);
      lowercase(type); //convert it to lowercase if user typed caps accidentally

      char message[200]; //the message
      strcpy(message, argv[2]); //copying argv[2] to message

      char key[10];
      strcpy(key, argv[3]); //copying argv[3] to key

      char key_offset[10];
      strcpy(key_offset, argv[4]); //the step

      //start checking for other user errors now that we know arguments are not null
      if (strcmp(type, "encrypt") != 0 && strcmp(type, "decrypt") != 0)
      {
        printf("Unknown command %s\n", argv[1]);
        print_usage();
      }
      else if (strlen(message) > 100)
      {
        printf("Max message length is 100 characters\n");
        print_usage();
      }
      else if (!is_number_convertable(key))
      {
        printf("Key must be an integer\n");
        print_usage();
      }
      else if (!is_number_convertable(key_offset))
      {
        printf("Key offset must be an integer\n");
        print_usage();
      }
      else
      {
        //no errors so call functions
        if (strcmp(type, "encrypt") == 0)
        {
          encrypt_string(message, atoi(argv[3]), atoi(argv[4]));
          printf("%s\n", message);
        }
        else //decrypt case
        {
          decrypt_string(message, atoi(argv[3]), atoi(argv[4]));
          printf("%s\n", message);
        }
      }
    }

    return 0;
}
