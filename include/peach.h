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

#ifndef _PEACH_H_
#define _PEACH_H_

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct _config_reader_t peach_config_reader_t;

typedef int 
(*peach_config_reader_param_process_t)
            (const char * parameter, 
            const char * key, 
            const char ** values, 
            uint16_t values_count, 
            void * on_call_argument);


extern peach_config_reader_t *
peach_config_reader_init
            (uint32_t table_size);

extern void
peach_config_reader_destroy
            (peach_config_reader_t * config_reader);

extern int
peach_config_reader_exec
            (peach_config_reader_t * config_reader, 
            int config_file);

extern int
peach_config_reader_param_register
            (peach_config_reader_t * config_reader, 
            const char * parameter, 
            peach_config_reader_param_process_t process, 
            void * on_call_argument);

extern int
peach_config_reader_param_unregister
            (peach_config_reader_t * config_reader,
            const char * parameter);

#ifndef NDEBUG
extern int
peach_debug_get_level(void);

extern void
peach_debug_set_level
            (int level);
#endif

typedef struct _hash_t peach_hash_t;

typedef void 
(*peach_hash_clean_t)
            (void * data);

typedef int 
(*peach_hash_predicate_t)
            (void * data, 
            va_list arguments);

extern peach_hash_t *
peach_hash_init
            (uint64_t table_size);

extern void
peach_hash_destroy
            (peach_hash_t * hash, 
            peach_hash_clean_t clean);

extern int
peach_hash_add
            (peach_hash_t * hash, 
            const char * key, 
            uint32_t key_length, 
            void * data);

extern void *
peach_hash_get
            (const peach_hash_t * hash, 
            const char * key, 
            uint32_t key_length);

extern void *
peach_hash_remove
            (peach_hash_t * hash, 
            const char * key, 
            uint32_t key_length);

extern void
peach_hash_clean
            (peach_hash_t * hash, 
            peach_hash_clean_t clean);

extern int
peach_hash_foreach
            (peach_hash_t * hash, 
            peach_hash_predicate_t routine, 
            ...);

typedef struct _list_t peach_list_t;

typedef struct _list_cell_t peach_list_cell_t;

typedef void 
(*peach_list_clean_t)
            (void * data);

typedef int 
(*peach_list_predicate_t)
            (void * data,
            va_list arguments);

typedef struct
{
    const peach_list_t * list;
    peach_list_cell_t * current_cell;
}
peach_list_iterator_t;


extern peach_list_t *
peach_list_init(void);

extern void
peach_list_destroy
            (peach_list_t * list,
            peach_list_clean_t clean);

extern void
peach_list_push_top
            (peach_list_t * list,
            void * data);

extern void
peach_list_push_bottom
            (peach_list_t * list,
            void * data);

extern void *
peach_list_pop_top
            (peach_list_t * list);

extern void *
peach_list_pop_bottom
            (peach_list_t * list);
            
extern int
peach_list_foreach
            (const peach_list_t * list,
            peach_list_predicate_t routine, 
            ...);

extern uint64_t
peach_list_get_length
            (const peach_list_t * list);

extern void
peach_list_iterator_init
            (const peach_list_t * list,
            peach_list_iterator_t * iterator);

extern void *
peach_list_iterator_get_next
            (peach_list_iterator_t * iterator);

#define peach_log_err(...)                      \
    do {                                        \
        peach_log_print(stderr, __VA_ARGS__);   \
        fflush(stderr);                         \
    }                                           \
    while(0)

#define peach_log_info(...)                     \
    do {                                        \
        peach_log_print(stdout, __VA_ARGS__);   \
        fflush(stdout);                         \
    }                                           \
    while(0)

#ifndef NDEBUG
    #define peach_log_debug(_level, ...)        \
        do {                                    \
            if (peach_debug_get_level() >= _level) {\
                peach_log_print(stderr, "[debug] " __VA_ARGS__);\
                fflush(stderr);                 \
            }                                   \
        }                                       \
        while (0)
#else
    #define peach_log_debug(...)                \
        do {                                    \
                                                \
        }                                       \
    while (0)
#endif

/**
 * \brief Print the current date on a \a stream.
 * \param stream The output stream.
 */
extern void
peach_log_print
            (FILE * stream, 
            ...);

#define PEACH_MODULE_API_VERSION 6

typedef int 
(*peach_module_init_t)(void);

typedef int 
(*peach_module_exit_t)(void);

typedef struct
{
    peach_module_init_t init;
    peach_module_exit_t exit;
}
peach_module_functions_t;

typedef struct
{
    const char * name;
    const uint64_t version;
}
peach_module_id_t;


#define PEACH_MODULE_REGISTER(__name, __version, __module_init, __module_exit)\
    uint32_t __peach_module_api_version = PEACH_MODULE_API_VERSION;\
                                        \
    const peach_module_functions_t __peach_module_functions =\
    {                                   \
        .init = __module_init,          \
        .exit = __module_exit           \
    };                                  \
                                        \
    const peach_module_id_t __peach_module_id =\
    {                                   \
        .name = __name,                 \
        .version = __version            \
    }; 

#define PEACH_MODULE_DEPENDENCIES(...)      \
    const peach_module_id_t __peach_module_dependencies [] =\
    {                                   \
        __VA_ARGS__                     \
        {.name = 0, .version = 0}       \
    }; 

#define PEACH_MODULE_NEED(__name, __version)\
    {.name = __name, .version = __version},

typedef struct _module_loader_t peach_module_loader_t;

extern peach_module_loader_t *
peach_module_loader_init(void);

extern void
peach_module_loader_destroy
            (peach_module_loader_t * module_loader);

extern const char *
peach_module_load
            (peach_module_loader_t * module_loader,
            const char * path); 

typedef struct _set_t peach_set_t;

typedef void 
(*peach_set_clean_t)
            (void * data);

typedef int 
(*peach_set_predicate_t)
            (void * data,
            va_list arguments);

typedef struct
{
    const peach_set_t * set;
    uint64_t current_position;
}
peach_set_iterator_t;

extern peach_set_t *
peach_set_init
            (uint64_t initial_size,
            uint64_t grow_size);

extern void
peach_set_destroy
            (peach_set_t * set,
            peach_set_clean_t clean);

extern uint64_t
peach_set_get_length
            (const peach_set_t * set);

extern void
peach_set_iterator_init
            (const peach_set_t * set,
            peach_set_iterator_t * iterator);

extern void *
peach_set_iterator_get_next
            (peach_set_iterator_t * iterator);

extern void
peach_set_add
            (peach_set_t * set,
            void * data);

extern void
peach_set_remove(peach_set_t * set,
            void * data);

extern void
peach_set_remove_multiples
            (peach_set_t * set,
            peach_set_predicate_t predicate, ...);

extern int
peach_set_foreach
            (const peach_set_t * set,
            peach_set_predicate_t routine, ...);

typedef struct _stack_t peach_stack_t;

typedef void 
(*peach_stack_clean_t)
            (void * data);

typedef int 
(*peach_stack_predicate_t)
            (void * data,
            va_list arguments);

extern peach_stack_t *
peach_stack_init
            (uint32_t chunck_count,
            uint32_t chunk_size);

extern void
peach_stack_destroy
            (peach_stack_t * stack,
            peach_stack_clean_t clean);

extern uint64_t
peach_stack_get_length
            (const peach_stack_t * stack);

extern void
peach_stack_push
            (peach_stack_t * stack,
            void * data);

extern void *
peach_stack_pop
            (peach_stack_t * stack);

extern void *
peach_stack_top
            (const peach_stack_t * stack);

extern int
peach_stack_foreach
            (const peach_stack_t * stack,
            peach_stack_predicate_t routine, 
            ...);

typedef struct _string_list_t peach_string_list_t;

extern peach_string_list_t *
peach_string_list_create(void);

extern peach_string_list_t *
peach_string_list_push
            (peach_string_list_t * string_list,
            char * peach_string);

extern char *
peach_string_list_pop
            (peach_string_list_t * string_list);

extern void
peach_string_list_destroy
            (peach_string_list_t * string_list);

extern char *
peach_string_list_merge
            (peach_string_list_t * string_list,
            int);

extern char *
peach_string_list_merge_on_the_fly
            (uint16_t string_count,
            ...);

#endif
