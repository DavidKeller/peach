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

#ifndef IN_PEACH_CONFIG_READER_SCANNER_C
    #error This file must be inclued by peach_config_reader_scanner.c
#endif

%%{
    machine config_parser_scanner;

    alphtype char;

    variable p scanner->buffer.current_position;
    variable pe scanner->buffer.position_until_refill;
    variable eof scanner->buffer.end_of_file;
    variable ts scanner->token.start;
    variable te scanner->token.end;
    variable cs scanner->scanner.status;
    variable act scanner->scanner.act;

    action inc_line
    {
        scanner->position.line ++;
        scanner->position.column = 1;
    }

    action inc_column
    {
        scanner->position.column ++;
    }

    action save_token_position
    {
        scanner->position.token_start.line = scanner->position.line;
        scanner->position.token_start.column = scanner->position.column;
    }

    newline = '\n' ('\r'?) %inc_line;
    text = any | newline;
    c_comment = '/*' (text* -- '*/') '*/';
    cpp_comment = ('//' | '#')any* -- newline;
    comment = c_comment | cpp_comment;
    path = (alnum | '_')+;
    delimiter = '\"';
    escape = '\\';
    value = delimiter ((text - delimiter) | (escape delimiter))* delimiter;

    main := 
    |*
        value >save_token_position $inc_column => 
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_TEXT, 
                        _token_data(scanner->token.start + 1, 
                        scanner->token.end - scanner->token.start - 2,
                        scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };

        path >save_token_position $inc_column =>
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_PATH, 
                        _token_data(scanner->token.start,
                        scanner->token.end - scanner->token.start, 
                        scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };

        '=' >save_token_position $inc_column =>
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_EQUAL,
                        _token_data(0, 0, scanner->position.token_start.line, 
                        scanner->position.token_start.column),
                        &config_tree);
        };

        ';' >save_token_position $inc_column =>
        {
        peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_SEMICOLON,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };

        ',' >save_token_position $inc_column =>
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_COLON, 
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };
        
        '[' >save_token_position $inc_column =>
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_SQUAREBRACKETL,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };

        ']' >save_token_position $inc_column =>
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_SQUAREBRACKETR,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };


        '{' >save_token_position $inc_column =>
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_BRACKETL,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };

        '}' >save_token_position $inc_column =>
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_BRACKETR,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };

        '.' >save_token_position $inc_column =>
        {
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_DOT,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        };

        (comment | text) $inc_column => { };
    *|;
}%%

%%write data;

peach_config_reader_scanner_t *
peach_config_reader_scanner_init
            (int config_file,
            uint32_t buffer_size)
{
    peach_config_reader_scanner_t * scanner;

    assert(config_file != 0);

    /* Allocate space for the scanner working data */
    scanner = malloc(sizeof(*scanner));
    assert(scanner != 0);

    /* Allocte space for the scanner buffer */
    scanner->buffer.start = malloc(sizeof(*scanner->buffer.start) 
                * buffer_size);
    assert(scanner->buffer.start != 0);
    scanner->buffer.size = buffer_size;

    /* Init all the pointers to the end of the scanner buffer
     * to force the scanner to ask for data at the first call */
    scanner->buffer.current_position 
                = scanner->buffer.position_until_refill
                = scanner->buffer.start;
    scanner->buffer.end_of_file = 0;

    /* Start at the first line */
    scanner->position.line = 1;
    scanner->position.column = 1;

    scanner->config_file = config_file;

    %%write init;

    return scanner;
}


peach_config_reader_parser_node_t *
peach_config_reader_scanner
            (peach_config_reader_scanner_t * scanner,
            void * parser)
{
    peach_config_reader_parser_node_t * config_tree;

    config_tree = 0;
    while (scanner->buffer.current_position 
                != scanner->buffer.position_until_refill 
                || _fill_buffer(scanner) > 0) {
        %%write exec;
    }

    /* Send the End Of File token to the parser */
    peach_config_reader_parser(parser, 0, 0, &config_tree);


    return config_tree;
}
