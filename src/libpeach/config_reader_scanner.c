/* Copyright (c) 2007, David Keller
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of David Keller nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

#include <peach.h>
#include "config_reader_scanner.h"

struct _config_reader_scanner_t
{
    struct
    {
        uint32_t size;
        char * start;
        char * current_position;
        char * position_until_refill;
        char * end_of_file;
    }
    buffer;

    struct
    {
        uint32_t size;
        char * start;
        char * end;
    }
    token;

    struct
    {
        uint32_t line;
        uint32_t column;
        struct
        {
            uint32_t line;
            uint32_t column;
        }
        token_start;
    }
    position;

    struct
    {
        int status;
        int act;
    }
    scanner;

    int config_file;
};

static int
_fill_buffer
            (peach_config_reader_scanner_t * scanner);

static peach_config_reader_parser_token_data_t *
_token_data
            (const char * string, 
            uint64_t string_length, 
            uint32_t line, 
            uint32_t column);


/**
 *
 *
 */
void
peach_config_reader_scanner_destroy
            (peach_config_reader_scanner_t * config_scanner)
{
    assert(config_scanner != 0);

    free(config_scanner->buffer.start);
    free(config_scanner);
}

static int
_fill_buffer
            (peach_config_reader_scanner_t * scanner)
{
    int result;
    uint32_t space;

    assert(scanner != 0);

    if (scanner->token.start != 0) {
        scanner->token.size = scanner->buffer.position_until_refill 
                    - scanner->token.start;
        space = scanner->buffer.size - scanner->token.size;
    } else {
        scanner->token.size = 0;
        space = scanner->buffer.size;
    }

    /* Check if the current word is too large to be saved into the scanner */
    if (space == 0)
        result = -1;
    else
    {
        uint32_t readed;
        
        if (scanner->token.size > 0) {
            uint32_t to_discard;

            to_discard = scanner->token.start - scanner->buffer.start;
            memmove(scanner->buffer.start, scanner->token.start, 
                        scanner->token.size);

            /* Reset the position of the pointers */
            scanner->buffer.current_position -= to_discard;
            scanner->buffer.position_until_refill -= to_discard;
            scanner->token.start -= to_discard;
            scanner->token.end -= to_discard;
        } else {
            scanner->buffer.current_position = scanner->buffer.start;
            scanner->buffer.position_until_refill = scanner->buffer.start;
        }

        if ((readed = result = read(scanner->config_file, scanner->buffer.start
                    + scanner->token.size, space)) < space)
            /* Mark the end of the file into the scanner */
            scanner->buffer.end_of_file 
                        = scanner->buffer.start + scanner->token.size + readed;

        /* Chech if the read has been sucessfull */
        if (readed > 0)
            scanner->buffer.position_until_refill += readed;
    }

    return result;
}

static peach_config_reader_parser_token_data_t *
_token_data
            (const char * string, 
            uint64_t string_length, 
            uint32_t line, 
            uint32_t column)
{
    peach_config_reader_parser_token_data_t * token_data;

    token_data = malloc(sizeof(*token_data));
    assert(token_data != 0);

    if (string != 0) { 
        token_data->string = malloc(sizeof(*token_data->string) * string_length
                    + 1);
        assert(token_data->string != 0);

        memcpy(token_data->string, string, sizeof(*token_data->string) 
                    * string_length);
        token_data->string[string_length] = '\0';

        token_data->string_length = string_length;
    } else
        token_data->string = 0;

    token_data->line = line;
    token_data->column = column;

    return token_data;
}


#define IN_PEACH_CONFIG_READER_SCANNER_C
#include "_config_reader_scanner.c"
#undef IN_PEACH_CONFIG_READER_SCANNER_C

