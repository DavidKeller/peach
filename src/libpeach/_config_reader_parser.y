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

%name "peach_config_reader_parser"
%extra_argument { peach_config_reader_parser_node_t ** config_tree }

%token_prefix PEACH_CONFIG_READER_PARSER_
%token_type { peach_config_reader_parser_token_data_t * }
%token_destructor
{
    if ($$ != 0) {
        if ($$->string != 0)
            free($$->string);

        free($$);
    }
}

%type string { peach_string_list_t * }
%destructor string
{
    peach_string_list_destroy($$);
}

%type path { peach_string_list_t * }
%destructor path
{
    peach_string_list_destroy($$);
}

%type values { peach_list_t * }
%destructor values
{
    peach_list_destroy($$, (peach_list_clean_t)free);
}

%type pairs { peach_config_reader_parser_node_t * }
%destructor pairs
{
    peach_config_reader_parser_node_destroy($$);
}

%type node { peach_config_reader_parser_node_t * }
%destructor node
{
    if ($$ != 0)
        peach_config_reader_parser_node_destroy($$);
}


%right
    EQUAL
    DOT
    COLON
    BRACKETL
    SQUAREBRACKETL
    .

%left
    PATH
    TEXT
    SEMICOLON
    BRACKETR
    SQUAREBRACKETR
    .


%start_symbol start

%parse_failure
{
    *config_tree = 0;
}

%syntax_error
{
    const char * token_type;

    switch (TOKEN_ID) {
    case PEACH_CONFIG_READER_PARSER_EQUAL:
        token_type = "'='";
        break;
    case PEACH_CONFIG_READER_PARSER_DOT:
        token_type = "'.'";
        break;
    case PEACH_CONFIG_READER_PARSER_COLON:
        token_type = "','";
        break;
    case PEACH_CONFIG_READER_PARSER_BRACKETL:
        token_type = "'{'";
        break;
    case PEACH_CONFIG_READER_PARSER_BRACKETR:
        token_type = "'}'";
        break;
    case PEACH_CONFIG_READER_PARSER_SQUAREBRACKETL:
        token_type = "'['";
        break;
    case PEACH_CONFIG_READER_PARSER_SQUAREBRACKETR:
        token_type = "']'";
        break;
    case PEACH_CONFIG_READER_PARSER_SEMICOLON:
        token_type = "';'";
        break;
    case PEACH_CONFIG_READER_PARSER_PATH:
        token_type = "variable";
        break;
    case PEACH_CONFIG_READER_PARSER_TEXT:
        token_type = "value";
        break;
    }

    peach_log_err("Configuration error: syntax error line:%llu column:%llu: "
                "unexpected %s.\n", TOKEN->line, TOKEN->column, token_type);
}

start ::= node(root) .
{
    *config_tree = root;
}

node(root) ::= error .
{
    root = 0;
}

node(root) ::= path(path) EQUAL values(values) SEMICOLON .
{
    root = peach_config_reader_parser_node_add_child(0, 
                peach_string_list_merge(path, 1),
                peach_config_reader_parser_node_values_pairs_add(0, 0, values));
}

node(root) ::= path(path) EQUAL SQUAREBRACKETL pairs(pairs) SQUAREBRACKETR .
{
    root = peach_config_reader_parser_node_add_child(0, 
                peach_string_list_merge(path, 1),
                pairs);
}

node(root) ::= path(path) BRACKETL node(child) BRACKETR .
{
    if (child != 0) {
        path = peach_string_list_push(path, strdup("."));

        root = peach_config_reader_parser_node_add_child(0, 
                    peach_string_list_merge(path, 1), child);
    } else {
        peach_string_list_destroy(path);

        root = 0;
    }
}

node(root) ::= node(sibbling) error .
{
    root = sibbling;
}

node(root) ::= node(sibbling) path(path) EQUAL values(values) SEMICOLON .
{
    root = peach_config_reader_parser_node_add_child(sibbling, 
                peach_string_list_merge(path, 1), 
                peach_config_reader_parser_node_values_pairs_add(0, 0, values));
}

node(root) ::= node(sibbling) path(path) EQUAL SQUAREBRACKETL pairs(pairs) SQUAREBRACKETR .
{
    root = peach_config_reader_parser_node_add_child(sibbling, 
                peach_string_list_merge(path, 1), pairs);
}

node(root) ::= node(sibbling) path(path) BRACKETL node(child) BRACKETR .
{
    if (child != 0) {
        path = peach_string_list_push(path, strdup("."));

        root = peach_config_reader_parser_node_add_child(sibbling, 
                peach_string_list_merge(path, 1), child);
    } else {
        peach_string_list_destroy(path);

        root = sibbling;
    }
}

path(updated_path) ::= PATH(from_scanner) .
{
    updated_path = peach_string_list_push(peach_string_list_create(),
                from_scanner->string);
    
    free(from_scanner);
}

path(updated_path) ::= path(path) DOT PATH(from_scanner) .
{
    path = peach_string_list_push(path, strdup("."));

    updated_path = peach_string_list_push(path, from_scanner->string);

    free(from_scanner);
}

values(values) ::= string(value) .
{
    values = peach_list_init();
    peach_list_push_bottom(values, peach_string_list_merge(value, 1)); 
}

values(updated_values) ::= values(values) COLON string(value) .
{
    peach_list_push_bottom(values, peach_string_list_merge(value, 1));

    updated_values = values;
}

pairs(updated_pairs) ::= PATH(from_scanner) values(values) SEMICOLON .
{
    updated_pairs = peach_config_reader_parser_node_values_pairs_add(0, 
                from_scanner->string, values);

    free(from_scanner);
}

pairs(updated_pairs) ::= pairs(pairs) PATH(from_scanner) values(values) SEMICOLON .
{
    updated_pairs = peach_config_reader_parser_node_values_pairs_add(pairs, 
                from_scanner->string, values);

    free(from_scanner);
}

string(string_list) ::= TEXT(from_scanner) .
{
    string_list = peach_string_list_push(peach_string_list_create(), from_scanner->string);

    free(from_scanner);
}

string(updated_string_list) ::= string(string_list) TEXT(from_scanner) .
{
    updated_string_list = peach_string_list_push(string_list, from_scanner->string);

    free(from_scanner);
}


%include
{
#ifndef IN_PEACH_CONFIG_READER_PARSER_C
    #error This file must be inclued by peach_config_reader_parser.c
#endif
}
