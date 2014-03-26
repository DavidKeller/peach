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
#include <string.h>
#include <stdlib.h>

#include <peach.h>

struct _set_t
{
    uint64_t allocated_size;
    uint64_t grow_size;
    uint64_t datas_count;

    uint64_t far_free_entry;

    void ** datas;
};

peach_set_t *
peach_set_init
            (uint64_t initial_size,
            uint64_t grow_size)
{
    peach_set_t * set;

    set = malloc(sizeof(*set));
    assert(set != 0);

    set->datas = calloc(1, initial_size * sizeof(*set->datas));
    assert(set->datas != 0);

    set->allocated_size = initial_size;
    set->datas_count = 0;
    set->far_free_entry = 0;
    set->grow_size = grow_size;

    return set;
}

void
peach_set_destroy
            (peach_set_t * set, 
            peach_set_clean_t clean)
{
    uint64_t i;

    if (clean != 0)
        for (i = 0; i < set->allocated_size; i++)
            if (set->datas[i]!= 0)
                (*clean)(set->datas[i]);

    free(set->datas);
    free(set);
}

uint64_t
peach_set_get_length
            (const peach_set_t * set)
{
    return set->datas_count;
}

void
peach_set_iterator_init
            (const peach_set_t * set,
            peach_set_iterator_t * iterator)
{
    iterator->set = set;
    iterator->current_position = 0;
}

void *
peach_set_iterator_get_next
            (peach_set_iterator_t * iterator)
{
    void * data;

    data = 0;
    while (iterator->current_position < iterator->set->allocated_size 
            && (data = iterator->set->datas[iterator->current_position++]) 
            == 0);

    return data;
}


void
peach_set_add
            (peach_set_t * set,
            void * data)
{
    assert(data != 0);
    
    if (set->datas_count >= set->allocated_size) {
        void ** new_datas_array;

        new_datas_array = malloc(sizeof(*new_datas_array) 
                    * (set->allocated_size + set->grow_size));
        assert(new_datas_array != 0);

        memcpy(new_datas_array, set->datas, sizeof(*new_datas_array) 
                    * set->allocated_size);
        memset(new_datas_array + set->allocated_size, 0, 
                    sizeof(*new_datas_array) * set->grow_size); 

        free(set->datas);
        set->datas = new_datas_array;

        set->datas[set->allocated_size] = data;
        set->datas_count ++;
        set->allocated_size += set->grow_size;
    } else {
        uint64_t i;
        int found;
        
        for (i = set->far_free_entry, found = 0; i < set->allocated_size 
                    && found == 0; i++)
            if (set->datas[i] == 0) {
                set->datas[i] = data;
                set->datas_count ++;
                set->far_free_entry = i;
                found = 1;
            }
    }
}

void
peach_set_remove(peach_set_t * set,
            void * data)
{
    uint64_t i;

    assert(data != 0);

    for (i = 0; i < set->allocated_size; i++)
        if (set->datas[i] == data) {
            set->datas[i] = 0;
            set->datas_count --;

            if (set->far_free_entry > i)
                set->far_free_entry = i;
        }
}

void
peach_set_remove_multiples
            (peach_set_t * set,
            peach_set_predicate_t predicate, 
            ...)
{
    va_list arguments;
    uint64_t i;

    assert(predicate != 0);

    for (i = 0; i < set->allocated_size; i++) {
        if (set->datas[i] != 0) {
            va_start(arguments, predicate);
            if ((*predicate)(set->datas[i], arguments) != 0) {
                set->datas[i] = 0;
                set->datas_count --;

                if (set->far_free_entry > i)
                    set->far_free_entry = i;
            }
            va_end(arguments);
        }
    }

    /* Resize the array if there is set->grow_size unused entries */
    if (set->allocated_size > (set->datas_count + set->grow_size)) {
        void ** new_datas_array;
        uint64_t j;

        new_datas_array = malloc(sizeof(*new_datas_array) *
                        (set->allocated_size - set->grow_size));
        assert(new_datas_array != 0);

        for (i = 0, j = 0; i < set->allocated_size; i++)
            if (set->datas[i] != 0)
            {
                new_datas_array[j] = set->datas[i];
                j++;
            }

        free(set->datas);
        set->datas = new_datas_array;
        set->allocated_size -= set->grow_size;
    }
}

int
peach_set_foreach
            (const peach_set_t * set,
            peach_set_predicate_t routine, 
            ...)
{
    va_list arguments;
    uint64_t i;
    int result;

    assert(routine != 0);

    for (i = 0, result = 0; i < set->allocated_size && result == 0; i++)
        if (set->datas[i] != 0) {
            va_start(arguments, routine);

            result = (*routine)(set->datas[i], arguments);

            va_end(arguments);
        }

    return result;
}

