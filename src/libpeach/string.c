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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <peach.h>

typedef struct _string_list_t _string_list_t;
struct _string_list_t
{
    peach_stack_t * stack;

    uint64_t strings_total_length;
};

static int
_merge
            (const char * data,
            va_list arguments);


/**
 *
 *
 */
extern peach_string_list_t *
peach_string_list_create(void)
{
    peach_string_list_t * string_list;

    /* Create a new peach_string list */
    string_list = malloc(sizeof(*string_list));
    assert(string_list != 0);

    string_list->stack = peach_stack_init(8, 4);
    string_list->strings_total_length = 0;

    return string_list;
}

/**
 *
 *
 */
void
peach_string_list_destroy
            (peach_string_list_t * string_list)
{
    assert(string_list  != 0);

    peach_stack_destroy(string_list->stack, (peach_stack_clean_t)free);

    free(string_list);
}

/**
 *
 *
 */
char *
peach_string_list_merge
            (peach_string_list_t * string_list, 
            int delete)
{
    char * string;
    uint64_t offset;

    assert(string_list != 0);

    string = malloc((string_list->strings_total_length + 1) * sizeof(*string));
    assert(string != 0);

    offset = string_list->strings_total_length;
    peach_stack_foreach(string_list->stack, (peach_stack_predicate_t)_merge, string, 
                &offset);

    string[string_list->strings_total_length] = '\0';
    
    if (delete)
        peach_string_list_destroy(string_list);

    return string;
}

/**
 *
 *
 */
char *
peach_string_list_merge_on_the_fly
            (uint16_t string_count,
            ...)
{
    va_list arguments;
    uint16_t i;
    uint64_t total_length;
    uint64_t offset;
    char * string;

    va_start(arguments, string_count);
    for (i = 0, total_length = 0; i < string_count; i++)
        total_length += strlen(va_arg(arguments, const char *));
    va_end(arguments);

    string = malloc(sizeof(*string) * (total_length + 1));

    va_start(arguments, string_count);
    for (i = 0, offset = 0; i < string_count; i++) {
        const char * current_string;

        current_string = va_arg(arguments, const char *);

        strcpy(string + offset, current_string);

        offset += strlen(current_string);
    }
    va_end(arguments);

    string[total_length] = '\0';
    
    return string;
}
/**
 *
 *
 */
peach_string_list_t *
peach_string_list_push
            (peach_string_list_t * string_list,
            char * string)
{
    assert(string_list != 0);
    assert(string != 0);

    peach_stack_push(string_list->stack, string);
    string_list->strings_total_length += strlen(string);

    return string_list;
}

/**
 *
 *
 */
char *
peach_string_list_pop
            (peach_string_list_t * string_list)
{
    char * string;

    assert(string_list != 0);

    string = peach_stack_pop(string_list->stack);
    string_list->strings_total_length -= strlen(string);
    
    return string;
}


static int
_merge
            (const char * data,
            va_list arguments)
{
    char * string;
    uint64_t * offset;
    uint32_t data_length;

    string = va_arg(arguments, char *);
    offset = va_arg(arguments, uint64_t *);
    data_length = strlen(data);

    *offset -= data_length;

    memcpy(string + *offset, data, data_length);

    return 0;
}

