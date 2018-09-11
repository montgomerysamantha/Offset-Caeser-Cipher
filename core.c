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

    if (key > 26) // if the key is large
    {
        key = key % 26;
    }
    else if (key <= 0) // if the key is negative or zero
    {
        return source; //do not offset
    }

    if (source >= 'A' && source <= 'Z') //uppercase letter
    {
        convert += key; //offset the char
        if ((int)convert > 90)
        {
            int overflow = (int)convert - 90;
            convert = 64 + overflow;
        }
        return convert;
    }
    else if (source >= 'a' && source <= 'z') //lowercase letter
    {
        convert += key; //offset the char
        if ((int)convert > 122)
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
    return source;
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
