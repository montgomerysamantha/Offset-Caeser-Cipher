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
    char convert = source; // the char we are encrypting

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
        convert += key; //offset the char
        if ((int)convert > Z_VALUE)
        {
            int overflow = (int)convert - Z_VALUE;
            convert = A_VALUE - 1 + overflow;
        }
        return convert;
    }
    else if (source >= 'a' && source <= 'z') //lowercase letter
    {
        convert += key; //offset the char
        if ((int)convert > LOWER_Z_VALUE)
        {
            int overflow = (int)convert - 122;
            convert = 96 + overflow;
        }
        return convert;
    }
    else //symbol or punctuation
    {
        //do not encrypt
        return source;
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
      //TODO: FIX
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
}

void print_usage()
{
    printf("Usage:\n");
    printf("\t./main encrypt message key key_offset\n");
    printf("\t./main decrypt message key key_offset\n");
}

int core_main(int argc, const char * argv[])
{
    print_usage();
    return 0;
}
