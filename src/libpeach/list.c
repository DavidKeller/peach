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

struct _list_cell_t
{
    void * data;

    peach_list_cell_t * next;
    peach_list_cell_t * prev;
};

struct _list_t
{
    peach_list_cell_t * top;
    peach_list_cell_t * bottom;

    uint64_t datas_count;
};

static void
_push_first_cell
            (peach_list_t * list,
            void * data);

peach_list_t *
peach_list_init(void)
{
    peach_list_t * list;

    list = calloc(1, sizeof(*list));
    assert(list != 0);

    return list;
}

void
peach_list_destroy
            (peach_list_t * list,
            peach_list_clean_t clean)
{
    assert(list != 0);

    while (list->top != 0) {
        peach_list_cell_t * to_del;

        to_del = list->top;
        list->top = to_del->next;

        if (clean != 0)
            (*clean)(to_del->data);
        free(to_del);
    }

    free(list);
}

void
peach_list_push_top
            (peach_list_t * list,
            void * data)
{
    assert(list != 0);
    assert(data != 0);

    if (list->datas_count == 0)
        _push_first_cell(list, data);
    else {
        peach_list_cell_t * cell;

        cell = malloc(sizeof(*cell));
        assert(cell != 0);

        list->top->prev = cell;
        cell->next = list->top;
        cell->prev = 0;
        list->top = cell;

        cell->data = data;
        list->datas_count ++;
    }
}

void
peach_list_push_bottom
            (peach_list_t * list,
            void * data)
{
    assert(list != 0);
    assert(data != 0);

    if (list->datas_count == 0)
        _push_first_cell(list, data);
    else {
        peach_list_cell_t * cell;

        cell = malloc(sizeof(*cell));
        assert(cell != 0);

        list->bottom->next = cell;
        cell->prev = list->bottom;
        cell->next = 0;
        list->bottom = cell;

        cell->data = data;
        list->datas_count ++;
    }
}

void *
peach_list_pop_top
            (peach_list_t * list)
{
    void * data;

    assert(list != 0);

    if (list->datas_count == 0)
        data = 0;
    else if (list->datas_count == 1) {
        data = list->top->data;

        free(list->top);

        list->top = list->bottom = 0;

        list->datas_count = 0;
    } else {
        peach_list_cell_t * to_del;

        to_del = list->top;
        list->top = to_del->next;
        list->top->prev = 0;

        data = to_del->data;

        list->datas_count --;

        free(to_del);
    }

    return data;
}

void *
peach_list_pop_bottom
            (peach_list_t * list)
{
    void * data;

    assert(list != 0);

    if (list->datas_count == 0)
        data = 0;
    else if (list->datas_count == 1) {
        data = list->top->data;

        free(list->top);

        list->top = list->bottom = 0;

        list->datas_count = 0;
    } else {
        peach_list_cell_t * to_del;

        to_del = list->bottom;
        list->bottom = to_del->prev;
        list->bottom->next = 0;

        data = to_del->data;

        list->datas_count --;

        free(to_del);
    }

    return 0;
}

int
peach_list_foreach
            (const peach_list_t * list,
            peach_list_predicate_t routine, 
            ...)
{
    va_list arguments;
    peach_list_cell_t * cell;
    int result;

    assert(list != 0);
    assert(routine != 0);

    for (result = 0, cell = list->top; result == 0 && cell != 0; 
                cell = cell->next) {
        va_start(arguments, routine);
        result = (*routine)(cell->data, arguments);
        va_end(arguments);
    }

    return result;
}

uint64_t
peach_list_get_length
            (const peach_list_t * list)
{
    assert(list != 0);

    return list->datas_count;
}

void
peach_list_iterator_init
            (const peach_list_t * list,
            peach_list_iterator_t * iterator)
{
    assert(list != 0);
    assert(iterator != 0);

    iterator->list = list;
    iterator->current_cell = list->top;
}

void *
peach_list_iterator_get_next
            (peach_list_iterator_t * iterator)
{
    void * data;

    if (iterator->current_cell == 0)
        data = 0;
    else {
        data = iterator->current_cell->data;
        iterator->current_cell = iterator->current_cell->next;
    }

    return data;
}

static void
_push_first_cell
            (peach_list_t * list,
            void * data)
{
    list->top = list->bottom = malloc(sizeof(*list->top));
    assert(list->top != 0);

    list->top->data = data;
    list->top->next = list->top->prev = 0;

    list->datas_count = 1;
}
