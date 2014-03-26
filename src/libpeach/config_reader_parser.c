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
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include <peach.h>
#include "config_reader_parser.h"

static peach_config_reader_parser_node_t *
_node_sibbling_create
            (char * path, 
            peach_config_reader_parser_node_t * child);

static peach_config_reader_parser_node_t *
_node_inner_create
            (peach_config_reader_parser_node_t * sibbling);

static peach_config_reader_parser_node_t *
_node_values_pairs_create
            (peach_config_reader_parser_node_values_pair_t * values);

static void
_node_destroy_values_pair
            (peach_config_reader_parser_node_values_pair_t * values_pair);

static void
_node_destroy
            (peach_config_reader_parser_node_t * root);


/**
 *
 *
 */
void
peach_config_reader_parser_node_destroy
            (peach_config_reader_parser_node_t * root)
{
    assert(root != 0);
    assert(root->type == CONFIG_READER_PARSER_NODE_INNER 
                || root->type == CONFIG_READER_PARSER_NODE_VALUES_PAIRS);

    /* Call a recursive function which delete all the nodes */
    _node_destroy(root);
}

/**
 *
 *
 */
peach_config_reader_parser_node_t *
peach_config_reader_parser_node_add_child
            (peach_config_reader_parser_node_t * inner,
            char * path, 
            peach_config_reader_parser_node_t * child)
{
    peach_config_reader_parser_node_t * new_sibbling;

    assert(path != 0);
    assert(child != 0);

    new_sibbling = _node_sibbling_create(path, child);

    /* Check if there is an existing subbling list */
    if (inner == 0)
        /* Create an inner node with a first sibbling */
        inner = _node_inner_create(new_sibbling);
    else {
        /* Add the new node content to the existing node list */
        inner->data.inner.bottom_sibbling->data.sibbling.next_sibbling 
                    = new_sibbling;
        inner->data.inner.bottom_sibbling = new_sibbling;
    }

    return inner;
}

/**
 *
 *
 */
peach_config_reader_parser_node_t *
peach_config_reader_parser_node_values_pairs_add
            (peach_config_reader_parser_node_t * values_pairs,
            char * key, peach_list_t * values)
{
    peach_config_reader_parser_node_values_pair_t * values_pair;

    assert(values != 0);

    /* Create a new value handler */
    values_pair = malloc(sizeof(*values_pair));
    assert(values_pair != 0);

    /* Save the current value into */
    values_pair->values = values;
    values_pair->key = key;

    /* Check if there is an existing values list */
    if (values_pairs == 0)
        /* Create a new values list */
        values_pairs = _node_values_pairs_create(values_pair);
    else
        peach_list_push_bottom(values_pairs->data.values.pairs, values_pair);

    return values_pairs;
}


static peach_config_reader_parser_node_t *
_node_sibbling_create
            (char * path, 
            peach_config_reader_parser_node_t * child)
{
    peach_config_reader_parser_node_t * new_sibbling;

    assert(path != 0);

    /* Create a new node content */
    new_sibbling = malloc(sizeof(*new_sibbling));
    assert(new_sibbling != 0);

    new_sibbling->type = CONFIG_READER_PARSER_NODE_SIBBLING;
    new_sibbling->data.sibbling.path = path;
    new_sibbling->data.sibbling.next_sibbling = 0;
    new_sibbling->data.sibbling.child = child;

    return new_sibbling;
}

static peach_config_reader_parser_node_t *
_node_inner_create
            (peach_config_reader_parser_node_t * sibbling)
{
    peach_config_reader_parser_node_t * inner;

    assert(sibbling != 0);

    /* Create a new inner node */
    inner = malloc(sizeof(*inner));
    assert(inner != 0);

    inner->type = CONFIG_READER_PARSER_NODE_INNER;

    /* Add the new node content to the top 
     * of the node node sibblings list */
    inner->data.inner.top_sibbling 
                = inner->data.inner.bottom_sibbling
                = sibbling;

    return inner;
}

static peach_config_reader_parser_node_t *
_node_values_pairs_create
            (peach_config_reader_parser_node_values_pair_t * values)
{
    peach_config_reader_parser_node_t * node;

    assert(values);

    node = malloc(sizeof(*node));
    assert(node != 0);

    node->type = CONFIG_READER_PARSER_NODE_VALUES_PAIRS;

    node->data.values.pairs = peach_list_init();
    peach_list_push_bottom(node->data.values.pairs, values);

    return node;
}

static void
_node_destroy
            (peach_config_reader_parser_node_t * root)
{
    assert(root != 0);

    if (root->type == CONFIG_READER_PARSER_NODE_VALUES_PAIRS)
        peach_list_destroy(root->data.values.pairs, 
                    (peach_list_clean_t)_node_destroy_values_pair);
    else if (root->type == CONFIG_READER_PARSER_NODE_SIBBLING) {
        /* Just delete the child, sibblings are deleted 
         * by the calling function: _node_destroy() */
        _node_destroy(root->data.sibbling.child);
        free(root->data.sibbling.path);
    } else {
        peach_config_reader_parser_node_t * to_del;

        assert(root->type == CONFIG_READER_PARSER_NODE_INNER);

        /* Delete all the subblings under this inner node */
        while(root->data.inner.top_sibbling != 0) {
            to_del = root->data.inner.top_sibbling;

            assert(to_del->type == CONFIG_READER_PARSER_NODE_SIBBLING);
            root->data.inner.top_sibbling 
                        = to_del->data.sibbling.next_sibbling;

            _node_destroy(to_del);
        }
    }

    free(root);
}

static void
_node_destroy_values_pair
            (peach_config_reader_parser_node_values_pair_t * values_pair)
{
    if (values_pair->key != 0)
        free(values_pair->key);

    peach_list_destroy(values_pair->values, (peach_list_clean_t)free);

    free(values_pair);
}

#define IN_PEACH_CONFIG_READER_PARSER_C
#include "_config_reader_parser.c"
#undef IN_PEACH_CONFIG_READER_PARSER_C
