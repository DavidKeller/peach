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
#include <string.h>
#include <assert.h>

#include <peach.h>

typedef struct _hash_entry_t _hash_entry_t;
struct _hash_entry_t
{
    void * data;

    char * key;
    uint32_t key_length;

    _hash_entry_t * next;
};

struct _hash_t
{
    _hash_entry_t * table;
    uint64_t entries_count;
    uint64_t size;
};


typedef uint64_t _hash_index_t;

static _hash_index_t
_hash_getindex
            (const peach_hash_t * hash, 
            const char * key, 
            uint32_t key_length);

static int
_key_are_equal
            (_hash_entry_t * entry, 
            const char * key, 
            uint32_t key_length);

static void
_copy_key
            (_hash_entry_t * entry, 
            const char * key, 
            uint32_t key_length);

peach_hash_t *
peach_hash_init
            (uint64_t table_size)
{
    peach_hash_t * hash;

    assert(table_size != 0);

    hash = malloc(sizeof(*hash));
    assert(hash != 0);

    hash->table = calloc(1, sizeof(*hash->table) * table_size);
    assert(hash->table != 0);

    hash->size = table_size;
    hash->entries_count = 0;

    return hash;
}

void
peach_hash_destroy
            (peach_hash_t * hash, 
            peach_hash_clean_t clean)
{
    _hash_index_t index;

    assert(hash != 0);
    
    /* Parse all entries */
    for (index = 0; index < hash->size; index ++) {
        _hash_entry_t * current_entry;

        /* Free the data and key of the root node */
        if (hash->table[index].key != 0)
            free(hash->table[index].key);
        if (clean != 0)
            (*clean)(hash->table[index].data);

        /* current_entry is the first child node */
        current_entry = hash->table[index].next;
	while (current_entry != 0) {
            _hash_entry_t * todel;

	    /* Free the data and key of the child node */
            free(current_entry->key);

	    if (clean != 0)
	        (*clean)(current_entry->data);

            /* The current node will be deleted */
	    todel = current_entry;

	    /* Step to the next node */
	    current_entry = current_entry->next;

	    /* Free the old current node */
	    free(todel);
	}
    }

    free(hash->table);

    free(hash);
}

int
peach_hash_add
            (peach_hash_t * hash, 
            const char* key, 
            uint32_t key_length, 
            void * data)
{
    int result;

    assert(hash != 0);
    assert(data != 0);
    assert(key != 0);
    assert(key_length != 0);

    if (hash->entries_count >= hash->size)
        result = -1;
    else {
        _hash_index_t index;
        _hash_entry_t * current_entry;

        index = _hash_getindex(hash, key, key_length);

        current_entry = &hash->table[index];

        result = 0;
        /* Go the the first free node at this key */
        while (current_entry != 0 && result == 0) {
            /* Check if the current node is free */
            if (current_entry->key == 0) {
                /* Store the key */
                _copy_key(current_entry, key, key_length);

                /* Save the data */
                current_entry->data = data;

                hash->entries_count ++;
            } else {
                /* Checks if the key already exists */
                if (_key_are_equal(current_entry, key, key_length))
                    result = -1;
                /* Checks if the current node is followed */
                else if (current_entry->next == 0) {
                    // No it isn't
                    /* Create a new node after the current */
                    current_entry->next = calloc(1
                            , sizeof(*current_entry->next));
                    assert(current_entry->next != 0);
                }
            }

            /* Go to the following node */
            current_entry = current_entry->next;
        }
    }

    return result;
}

void *
peach_hash_get
            (const peach_hash_t * hash, 
            const char * key, 
            uint32_t key_length)
{
    /* Déclaration des variables locales */
    _hash_index_t index;
    _hash_entry_t * current_entry;
    void * found;

    /* Vérification des arguments */
    assert(hash != 0);
    assert(key != 0);
    assert(key_length != 0);

    /* Get the index of the data */
    index = _hash_getindex(hash, key, key_length);
    
    current_entry = &hash->table[index];
    found = 0;

    while (current_entry != 0 && found == 0) {
        /* Checks if the current node matchs the key */
        if (_key_are_equal(current_entry, key, key_length))
	// Yes
	    found = current_entry->data;

        /* Step to the next node */
	current_entry = current_entry->next;
    }

    /* The entry has not been found  */
    return found;
}

void *
peach_hash_remove
            (peach_hash_t * hash, 
            const char * key, 
            uint32_t key_length)
{
    _hash_index_t index;
    void * data;

    assert(hash != 0);
    assert(key != 0);
    assert(key_length != 0);

    data = 0;

    /* Go to the root node of the key */
    index = _hash_getindex(hash, key, key_length);

    /* Checks if the root node is the one to remove */
    if (_key_are_equal(&hash->table[index], key, key_length)) {
    // Yes it is
        _hash_entry_t * todel;

        /* Free the key entry */
	free(hash->table[index].key);
	hash->table[index].key = 0;

	/* Save to address of the data */
	data = hash->table[index].data;

        /* Checks if there is a child */
	if (hash->table[index].next) {
	    /* The first child node will be deleted */
	    todel = hash->table[index].next;

	    /* Data and key of the child node are copied into the root node */
	    hash->table[index].key = hash->table[index].next->key;
	    hash->table[index].data = hash->table[index].next->data;
	    /* The child of the following node become 
             * the child of the root node */
            hash->table[index].next = todel->next;

            /* Delete the root first child */
	    free(todel);
	}

        /* Update the size of the table */
	hash->entries_count --;
    } else {
    // No it isn't
        _hash_entry_t * current_entry;
        _hash_entry_t * todel;

        current_entry = &hash->table[index];
        todel = hash->table[index].next;
        while (todel != 0 && data == 0) {
            /* Checks if the current node matchs the key */
            if (_key_are_equal(todel, key, key_length)) {
    	    // Yes
	        /* Save the address of the data */
    	        data = todel->data;

		/* The next field of the previous cell aims to the next cell */
                current_entry->next = todel->next;

                /* Free the key and the node */
                free(todel->key);
		free(todel);

                /* Update the size of the table */
                hash->entries_count--;
    	    }
            else
                /* Step to the next node */
                current_entry = current_entry->next;
        }
    }
  
    /* The entry isn't in the table */
    return data;
}

void
peach_hash_clean
            (peach_hash_t * hash, 
            peach_hash_clean_t clean)
{
    _hash_index_t index;

    assert(hash != 0);
    
    for (index = 0; index < hash->size; index ++) {
        if (hash->table[index].key) {
            _hash_entry_t * current_entry;

	    free(hash->table[index].key);
	    hash->table[index].key = 0;

            if (clean != 0) {
                (*clean)(hash->table[index].data);
		hash->table[index].data = 0;
	    }

	    /* current_entry aims to the first child */
	    current_entry = hash->table[index].next;

	    /* Delete the reference to the first child */
	    hash->table[index].next = 0;

	    /* Parse all childs */
	    while (current_entry != 0) {
                _hash_entry_t * todel; 

	        /* Free the key of the current child */
                free(current_entry->key);
		/* Checks if the data must be freed */
		if (clean != 0)
		// Yes
		    (*clean)(current_entry->data);

                /* The current child will be deleted */
	        todel = current_entry;

		/* Step to the next child */
		current_entry = current_entry->next;
                
		/* Delete the old current child */
		free(todel);
	    }
	}
    }
}

int
peach_hash_foreach
            (peach_hash_t * hash, 
            peach_hash_predicate_t routine, 
            ...)
{
    va_list arguments;
    _hash_index_t index;
    int result;

    assert(hash != 0);
    assert(routine != 0);

    result = 0;
    for (index = 0; index < hash->size && result == 0; index ++) {
        _hash_entry_t * current_entry;

        current_entry = &hash->table[index];

        /* Parse all the child */
	while (current_entry != 0 && result != 0) {
            va_start(arguments, routine);

	    /* The function is called on every node */
            result = (*routine)(current_entry->data, arguments);

            va_end(arguments);

            /* Step to the next child */
	    current_entry = current_entry->next;
	}
    }

    return result;
}

/*
 * FROM wikipedia.com/l_hash
 */
static _hash_index_t
_hash_getindex
            (const peach_hash_t * hash, 
            const char * key, 
            uint32_t key_length)
{
    unsigned int index;
    uint64_t i;

    for (i = 0, index = 0; i < key_length; i++) {
        index += key[i];
        index += (index << 10);
        index ^= (index >> 6);
    }

    index += (index << 3);
    index ^= (index >> 11);
    index += (index << 15);

    return index % hash->size;
}

static int
_key_are_equal
            (_hash_entry_t * entry, 
            const char * key, 
            uint32_t key_length)
{
    return entry->key_length == key_length 
                && memcmp(entry->key, key, key_length) == 0;
}

static void
_copy_key
            (_hash_entry_t * entry, 
            const char * key, 
            uint32_t key_length)
{
    assert(entry->key == 0);

    entry->key = malloc(sizeof(*entry->key) * key_length);
    memcpy(entry->key, key, sizeof(*entry->key) * key_length);
    entry->key_length = key_length;
}

