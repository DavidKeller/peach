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

struct _stack_t
{
    void *** chunks;

    uint32_t chunks_count;
    uint64_t chunk_size;

    uint64_t datas_count;
};


peach_stack_t *
peach_stack_init
            (uint32_t initial_size,
            uint32_t chunk_size)
{
    uint32_t i;
    peach_stack_t * stack;

    assert(chunk_size != 0);

    stack = malloc(sizeof(*stack));
    assert(stack != 0);

    stack->chunks_count = initial_size / chunk_size;
    if (initial_size % chunk_size != 0 || initial_size == 0)
        stack->chunks_count ++;

    stack->chunks = malloc(stack->chunks_count
                * sizeof(*stack->chunks));
    assert(stack->chunks != 0);

    for (i = 0; i < stack->chunks_count; i++) {
        stack->chunks[i] = calloc(chunk_size, sizeof(**stack->chunks));
        assert(stack->chunks[i] != 0);
    }

    stack->chunk_size = chunk_size;
    stack->datas_count = 0;

    return stack;
}

void
peach_stack_destroy
            (peach_stack_t * stack,
            peach_stack_clean_t clean)
{
    uint64_t i;
    
    assert(stack != 0);

    if (clean != 0);
        for (i = stack->datas_count; i != 0; ) {
            i--;
            (*clean)(stack->chunks[i / stack->chunk_size]
                                    [i % stack->chunk_size]);
        }

    for (i = 0; i <stack->chunks_count; i++)
        free(stack->chunks[i]);

    free(stack->chunks);
    free(stack);
}

uint64_t
peach_stack_get_length
            (const peach_stack_t * stack)
{
    return stack->datas_count;
}

void
peach_stack_push
            (peach_stack_t * stack,
            void * data)
{
    assert(stack != 0);

    if (stack->datas_count == stack->chunks_count * stack->chunk_size) {
        stack->chunks = realloc(stack->chunks, (stack->chunks_count + 1) 
                                                * sizeof(*stack->chunks));
        assert(stack->chunks != 0);

        stack->chunks[stack->chunks_count] = calloc(stack->chunk_size, 
                                                    sizeof(**stack->chunks));

        assert(stack->chunks[stack->chunks_count] != 0);

        stack->chunks_count ++;
    }

    stack->chunks[stack->datas_count / stack->chunk_size]
                [stack->datas_count % stack->chunk_size] = data;

    stack->datas_count ++;
}

void *
peach_stack_pop
            (peach_stack_t * stack)
{
    void * data;

    assert(stack != 0);

    if (stack->datas_count == 0)
        data = 0;
    else {
        if (stack->datas_count < (stack->chunks_count - 1) 
                    * stack->chunk_size) {
            stack->chunks_count --;

            free(stack->chunks[stack->chunks_count]);
            stack->chunks = realloc(stack->chunks, stack->chunks_count
                        * sizeof(*stack->chunks));
            assert(stack->chunks != 0);
        }

        stack->datas_count --;

        data = stack->chunks[stack->datas_count / stack->chunk_size]
                    [stack->datas_count % stack->chunk_size];
    }

    return data;
}

void *
peach_stack_top
            (const peach_stack_t * stack)
{
    void * data;
    assert(stack != 0);

    if (stack->datas_count == 0)
        data = 0;
    else
        data = stack->chunks[(stack->datas_count - 1) / stack->chunk_size]
                [(stack->datas_count - 1) % stack->chunk_size];

    return data;
}

int
peach_stack_foreach
            (const peach_stack_t * stack,
            peach_stack_predicate_t routine, 
            ...)
{
    va_list arguments;
    int result;
    uint64_t i;

    assert(stack != 0);
    assert(routine != 0);

    for (i = stack->datas_count, result = 0; i != 0 && result == 0; ) {

        va_start(arguments, routine);

        i--;
        result = (*routine)(stack->chunks[i / stack->chunk_size]
                [i % stack->chunk_size], arguments);

        va_end(arguments);
    }

    return result;
}

