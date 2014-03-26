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

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <peach.h>
#include "config_reader_scanner.h"
#include "config_reader_parser.h"

struct _config_reader_t
{
    peach_hash_t * hash;
};

typedef struct
{
   peach_config_reader_param_process_t process_function;
   void * on_call_argument;
}
_config_reader_entry_t;


static int 
_parse_config_tree
            (const peach_config_reader_parser_node_t * node,
            peach_config_reader_t * config_reader, 
            peach_string_list_t * buffer);

static int 
_parse_values_pair
            (peach_config_reader_parser_node_values_pair_t * values_pair,
            va_list arguments); 


int 
peach_config_reader_exec
            (peach_config_reader_t * config_reader,
            int config_file)
{
    void * parser;
    peach_config_reader_parser_node_t * config_tree;
    peach_config_reader_scanner_t * scanner;
    int result;

    scanner = peach_config_reader_scanner_init(config_file, 256);
    parser = peach_config_reader_parserAlloc(malloc);
   
#ifndef NDEBUG
    if (peach_debug_get_level() >= 3)
        peach_config_reader_parserTrace(stdout, "");
#endif

    if ((config_tree = peach_config_reader_scanner(scanner, parser)) == 0) 
        result = -1;
    else {
        peach_string_list_t * buffer;

        buffer = peach_string_list_create();

        result = _parse_config_tree(config_tree, config_reader, buffer);

        peach_string_list_destroy(buffer);

        peach_config_reader_parser_node_destroy(config_tree);

        result = 0;
    } 

    /* Free scanner and buffer working structures */
    peach_config_reader_scanner_destroy(scanner);
    peach_config_reader_parserFree(parser, free);

    return result;
}

peach_config_reader_t *
peach_config_reader_init
            (uint32_t table_size)
{
    peach_config_reader_t * config_reader;

    config_reader = malloc(sizeof(*config_reader));
    assert(config_reader != 0);

    /* Init the hash table which will store variables */
    config_reader->hash = peach_hash_init(table_size);

    return config_reader;
}

void
peach_config_reader_destroy
            (peach_config_reader_t * config_reader)
{
    assert(config_reader != 0);

    /* Destroy the hash table which store variables
     * and free entries */
    peach_hash_destroy(config_reader->hash, free);
    free(config_reader);
}

int
peach_config_reader_param_register
            (peach_config_reader_t * config_reader, 
            const char * parameter, 
            peach_config_reader_param_process_t process_function,
            void * on_call_argument)
{
    _config_reader_entry_t * entry;

    peach_log_debug(2, "Config reader: registering '%s'.\n", parameter);

    entry = malloc(sizeof(*entry));
    assert(entry != 0);

    /* Register the callbottom funtion */
    entry->process_function = process_function;

    /* Register the argument which will be passed to the callbottom function */
    entry->on_call_argument = on_call_argument;

    /* Add entry to the hash table */
    return peach_hash_add(config_reader->hash, parameter, strlen(parameter), 
                entry);
}

int
peach_config_reader_param_unregister
            (peach_config_reader_t * config_reader,
            const char * parameter)
{
    _config_reader_entry_t * entry;
    int result;

    /* Try to remove the desired entry from the hash table */
    entry = peach_hash_remove(config_reader->hash, parameter, strlen(parameter));

    if (entry == 0)
        result = -1;
    else {
        free(entry);

        result = 0;
    }

    return result;
}

static int
_parse_config_tree
            (const peach_config_reader_parser_node_t * node, 
            peach_config_reader_t * config_reader,
            peach_string_list_t * buffer)
{
    int result;

    assert(node != 0);

    /* Check if the current node store a value */
    if (node->type == CONFIG_READER_PARSER_NODE_VALUES_PAIRS) {
        char * parameter;
        const _config_reader_entry_t * entry;

        /* Try to retrieve the entry registered at this path name */
        parameter = peach_string_list_merge(buffer, 0);

        entry = peach_hash_get(config_reader->hash, parameter, strlen(parameter));

        /* Check if the entry has been found */
        if (entry == 0) {
            peach_log_err("Configuration error: '%s' is an unknown parameter.\n",
                        parameter);

            result = -1;
        }
        else
            result = peach_list_foreach(node->data.values.pairs, 
                        (peach_list_predicate_t)_parse_values_pair, 
                        parameter, entry);

        free(parameter);
    } else {
        const peach_config_reader_parser_node_t * current_sibbling;

        assert(node->type == CONFIG_READER_PARSER_NODE_INNER);
        result = 0;

        /* For each sibbling of the node node */
        current_sibbling = node->data.inner.top_sibbling; 
        while (current_sibbling != 0 && result == 0) {

            peach_string_list_push(buffer, current_sibbling->data.sibbling.path);
            /* Save the node reassembled fragment of the 
             * associated path into the buffer */

            /* Same work again on the child(s) */
            result = _parse_config_tree(
                        current_sibbling->data.sibbling.child,
                        config_reader, buffer);

            peach_string_list_pop(buffer);

            current_sibbling = current_sibbling->data.sibbling.next_sibbling;
        }
    }

    return result;
}

static int
_parse_values_pair
            (peach_config_reader_parser_node_values_pair_t * values_pair, 
            va_list arguments)
{
    const char ** values;
    uint16_t values_count;
    uint16_t i;
    int result;
    peach_list_iterator_t iterator;
    char * parameter;
    const _config_reader_entry_t * entry;

    parameter = va_arg(arguments, char *);
    entry = va_arg(arguments, const _config_reader_entry_t *);

    peach_list_iterator_init(values_pair->values, &iterator);
    values_count = peach_list_get_length(values_pair->values);

    values = malloc(sizeof(*values) * values_count);
    assert(values != 0);

    for (i = 0; i < values_count; i++)
        values[i] = peach_list_iterator_get_next(&iterator);

    assert(entry->process_function != 0);
    result = (*entry->process_function)(parameter, values_pair->key, values, 
                values_count, entry->on_call_argument);

    free(values);

    return result;
}
