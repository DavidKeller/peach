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

#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <peach.h>

#define PEACH_MODULE_EXPECTED_COUNT 20
#define PEACH_MODULE_ERROR_COUNT_DELTA 10

struct _module_loader_t
{
    peach_stack_t * loaded_modules;
};

typedef struct 
{
    void * handler;
    const peach_module_functions_t * functions;
    const peach_module_id_t * id;
    const peach_module_id_t * dependencies;
}
_module_t;


static void
_unload_module
            (_module_t * module);

static int
_dependencies_not_respected
            (const peach_stack_t * loaded_modules,
            const _module_t * module);

static int
_match_module_id
            (const _module_t * module,
            va_list arguments);

peach_module_loader_t *
peach_module_loader_init(void)
{
    peach_module_loader_t * module_loader;

    module_loader = malloc(sizeof(*module_loader));
    assert(module_loader != 0);

    module_loader->loaded_modules = peach_stack_init(PEACH_MODULE_EXPECTED_COUNT,
                PEACH_MODULE_ERROR_COUNT_DELTA);

    return module_loader;
}

void
peach_module_loader_destroy
            (peach_module_loader_t * module_loader)
{
    assert(module_loader != 0);

    peach_stack_destroy(module_loader->loaded_modules, 
                (peach_stack_clean_t)_unload_module);

    free(module_loader);
}

const char *
peach_module_load
            (peach_module_loader_t * module_loader,
            const char * path) 
{
    _module_t * module;
    uint32_t * module_api_version;

    assert(module_loader != 0);
    assert(path != 0);

    module = malloc(sizeof(*module));
    assert(module != 0);

    /* Load the dynamic lib */
    if ((module->handler = dlopen(path, RTLD_NOW | RTLD_GLOBAL)) == 0) {
        peach_log_err("Module: could not load module at '%s': '%s'.\n",
                    path, dlerror());

        goto clean;
    }

    /* Try to get the module API version of the dynamic lib */
    if ((module_api_version = dlsym(module->handler, "__peach_module_api_version"))
                == 0 || *module_api_version != PEACH_MODULE_API_VERSION)
        goto wrong_api;

    /* Get the boostrap functions of the dynamic lib */
    if ((module->functions = dlsym(module->handler, "__peach_module_functions")) 
                == 0) 
        goto wrong_api;

    /* Get the module id of the dynamic lib */
    if ((module->id = dlsym(module->handler, "__peach_module_id")) == 0) 
        goto wrong_api;

    /* Check the module dependencies */
    if ((module->dependencies = dlsym(module->handler, 
                "__l_module_dependencies")) != 0 
                && _dependencies_not_respected(module_loader->loaded_modules,
                module))
        goto unload_module;
  
    /* Init the module */
    if ((*module->functions->init)() != 0) {
        peach_log_err("Module: '%s' init function failed.\n", 
                    module->id->name);
        goto unload_module;
    }

    peach_stack_push(module_loader->loaded_modules, module);

    peach_log_debug(1, "Module: '%s' loaded.\n", module->id->name);

    return module->id->name;

wrong_api:
    peach_log_err("Module: could not initialize module at '%s', current"
                " MODULE API version is '%d'.\n", path, PEACH_MODULE_API_VERSION);

unload_module:
    dlclose(module->handler);

clean:
    free(module);
    return 0;
}

static void
_unload_module
            (_module_t * module)
{
    if ((*module->functions->exit)() != 0)
        peach_log_err("Module: '%s' exit function failed.\n",
                    module->id->name);

    peach_log_debug(1, "Module: '%s' unloaded.\n", module->id->name);

    dlclose(module->handler);

    free(module);
}

static int
_dependencies_not_respected
            (const peach_stack_t * loaded_modules,
            const _module_t * module)
{
    int dependencies_not_respected;
    const peach_module_id_t * dependency;

    dependency = module->dependencies;

    for (dependency = module->dependencies, dependencies_not_respected = 0;
                dependency->name != 0; dependency ++) {
        
        if (!peach_stack_foreach(loaded_modules, 
                    (peach_stack_predicate_t)_match_module_id, dependency)) {

            peach_log_err("Module: '%s' module needs '%s' version '%d'.\n",
                        module->id->name, dependency->name, 
                        dependency->version);

            dependencies_not_respected = 1;
        }
    }

    return dependencies_not_respected;
}

static int
_match_module_id
            (const _module_t * module,
            va_list arguments)
{
    int match;
    const peach_module_id_t * dependency;

    dependency = va_arg(arguments, const peach_module_id_t *);
    match = 0;

    if (module->id->version == dependency->version
            && strcmp(module->id->name, dependency->name) == 0)

        match = 1;

    return match;
}
