#line 1 "_config_reader_scanner.rl"
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

#line 161 "_config_reader_scanner.rl"



#line 37 "_config_reader_scanner.c"
static const char _config_parser_scanner_actions[] = {
	0, 1, 1, 1, 3, 1, 4, 1, 
	18, 1, 19, 1, 20, 1, 21, 2, 
	0, 1, 2, 0, 19, 2, 1, 8, 
	2, 1, 17, 2, 2, 1, 2, 5, 
	1, 3, 0, 1, 8, 3, 2, 1, 
	9, 3, 2, 1, 10, 3, 2, 1, 
	11, 3, 2, 1, 12, 3, 2, 1, 
	13, 3, 2, 1, 14, 3, 2, 1, 
	15, 3, 2, 1, 16, 3, 5, 1, 
	6, 4, 5, 2, 1, 7
};

static const char _config_parser_scanner_key_offsets[] = {
	0, 3, 7, 10, 13, 15, 18, 20, 
	23, 42, 43, 43, 46, 47, 49
};

static const char _config_parser_scanner_trans_keys[] = {
	10, 34, 92, 10, 13, 34, 92, 10, 
	34, 92, 10, 34, 92, 10, 42, 10, 
	13, 42, 10, 42, 10, 42, 47, 10, 
	34, 35, 44, 46, 47, 59, 61, 91, 
	93, 95, 123, 125, 48, 57, 65, 90, 
	97, 122, 13, 10, 34, 92, 10, 42, 
	47, 95, 48, 57, 65, 90, 97, 122, 
	0
};

static const char _config_parser_scanner_single_lengths[] = {
	3, 4, 3, 3, 2, 3, 2, 3, 
	13, 1, 0, 3, 1, 2, 1
};

static const char _config_parser_scanner_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	3, 0, 0, 0, 0, 0, 3
};

static const char _config_parser_scanner_index_offsets[] = {
	0, 4, 9, 13, 17, 20, 24, 27, 
	31, 48, 50, 51, 55, 57, 60
};

static const char _config_parser_scanner_trans_targs[] = {
	1, 8, 3, 0, 1, 2, 8, 3, 
	0, 1, 8, 3, 0, 1, 11, 3, 
	0, 5, 7, 4, 5, 6, 7, 4, 
	5, 7, 4, 5, 7, 8, 4, 9, 
	11, 12, 8, 8, 13, 8, 8, 8, 
	8, 14, 8, 8, 14, 14, 14, 8, 
	10, 8, 8, 1, 8, 3, 0, 8, 
	12, 4, 12, 8, 14, 14, 14, 14, 
	8, 8, 8, 8, 8, 8, 8, 8, 
	8, 8, 8, 8, 8, 8, 8, 0
};

static const char _config_parser_scanner_trans_actions[] = {
	1, 21, 1, 1, 15, 15, 33, 15, 
	15, 15, 33, 15, 15, 1, 69, 1, 
	1, 1, 1, 1, 15, 15, 15, 15, 
	15, 15, 15, 1, 1, 24, 1, 1, 
	73, 1, 45, 65, 30, 41, 37, 49, 
	53, 27, 57, 61, 27, 27, 27, 24, 
	1, 18, 18, 1, 21, 1, 1, 9, 
	1, 1, 1, 9, 1, 1, 1, 1, 
	7, 13, 13, 13, 13, 11, 11, 11, 
	11, 18, 18, 13, 9, 9, 7, 0
};

static const char _config_parser_scanner_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	3, 0, 0, 0, 0, 0, 0
};

static const char _config_parser_scanner_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	5, 0, 0, 0, 0, 0, 0
};

static const char _config_parser_scanner_eof_trans[] = {
	76, 76, 76, 76, 73, 73, 73, 73, 
	0, 75, 75, 76, 78, 78, 79
};

static const int config_parser_scanner_start = 8;
static const int config_parser_scanner_first_final = 8;
static const int config_parser_scanner_error = -1;

static const int config_parser_scanner_en_main = 8;

#line 164 "_config_reader_scanner.rl"

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

    
#line 164 "_config_reader_scanner.c"
	{
	( scanner->scanner.status) = config_parser_scanner_start;
	( scanner->token.start) = 0;
	( scanner->token.end) = 0;
	( scanner->scanner.act) = 0;
	}
#line 198 "_config_reader_scanner.rl"

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
        
#line 189 "_config_reader_scanner.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( ( scanner->buffer.current_position) == ( scanner->buffer.position_until_refill) )
		goto _test_eof;
_resume:
	_acts = _config_parser_scanner_actions + _config_parser_scanner_from_state_actions[( scanner->scanner.status)];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 4:
#line 1 "_config_reader_scanner.rl"
	{( scanner->token.start) = ( scanner->buffer.current_position);}
	break;
#line 208 "_config_reader_scanner.c"
		}
	}

	_keys = _config_parser_scanner_trans_keys + _config_parser_scanner_key_offsets[( scanner->scanner.status)];
	_trans = _config_parser_scanner_index_offsets[( scanner->scanner.status)];

	_klen = _config_parser_scanner_single_lengths[( scanner->scanner.status)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*( scanner->buffer.current_position)) < *_mid )
				_upper = _mid - 1;
			else if ( (*( scanner->buffer.current_position)) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _config_parser_scanner_range_lengths[( scanner->scanner.status)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*( scanner->buffer.current_position)) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*( scanner->buffer.current_position)) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	( scanner->scanner.status) = _config_parser_scanner_trans_targs[_trans];

	if ( _config_parser_scanner_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _config_parser_scanner_actions + _config_parser_scanner_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 45 "_config_reader_scanner.rl"
	{
        scanner->position.line ++;
        scanner->position.column = 1;
    }
	break;
	case 1:
#line 51 "_config_reader_scanner.rl"
	{
        scanner->position.column ++;
    }
	break;
	case 2:
#line 56 "_config_reader_scanner.rl"
	{
        scanner->position.token_start.line = scanner->position.line;
        scanner->position.token_start.column = scanner->position.column;
    }
	break;
	case 5:
#line 1 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;}
	break;
	case 6:
#line 75 "_config_reader_scanner.rl"
	{( scanner->scanner.act) = 1;}
	break;
	case 7:
#line 159 "_config_reader_scanner.rl"
	{( scanner->scanner.act) = 11;}
	break;
	case 8:
#line 75 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_TEXT, 
                        _token_data(scanner->token.start + 1, 
                        scanner->token.end - scanner->token.start - 2,
                        scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 9:
#line 95 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_EQUAL,
                        _token_data(0, 0, scanner->position.token_start.line, 
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 10:
#line 103 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
        peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_SEMICOLON,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 11:
#line 111 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_COLON, 
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 12:
#line 119 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_SQUAREBRACKETL,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 13:
#line 127 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_SQUAREBRACKETR,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 14:
#line 136 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_BRACKETL,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 15:
#line 144 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_BRACKETR,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 16:
#line 152 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_DOT,
                        _token_data(0, 0, scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 17:
#line 159 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position)+1;{ }}
	break;
	case 18:
#line 85 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position);( scanner->buffer.current_position)--;{
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_PATH, 
                        _token_data(scanner->token.start,
                        scanner->token.end - scanner->token.start, 
                        scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }}
	break;
	case 19:
#line 159 "_config_reader_scanner.rl"
	{( scanner->token.end) = ( scanner->buffer.current_position);( scanner->buffer.current_position)--;{ }}
	break;
	case 20:
#line 159 "_config_reader_scanner.rl"
	{{( scanner->buffer.current_position) = ((( scanner->token.end)))-1;}{ }}
	break;
	case 21:
#line 1 "_config_reader_scanner.rl"
	{	switch( ( scanner->scanner.act) ) {
	case 1:
	{{( scanner->buffer.current_position) = ((( scanner->token.end)))-1;}
            peach_config_reader_parser(parser, PEACH_CONFIG_READER_PARSER_TEXT, 
                        _token_data(scanner->token.start + 1, 
                        scanner->token.end - scanner->token.start - 2,
                        scanner->position.token_start.line,
                        scanner->position.token_start.column),
                        &config_tree);
        }
	break;
	case 11:
	{{( scanner->buffer.current_position) = ((( scanner->token.end)))-1;} }
	break;
	}
	}
	break;
#line 430 "_config_reader_scanner.c"
		}
	}

_again:
	_acts = _config_parser_scanner_actions + _config_parser_scanner_to_state_actions[( scanner->scanner.status)];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 3:
#line 1 "_config_reader_scanner.rl"
	{( scanner->token.start) = 0;}
	break;
#line 443 "_config_reader_scanner.c"
		}
	}

	if ( ++( scanner->buffer.current_position) != ( scanner->buffer.position_until_refill) )
		goto _resume;
	_test_eof: {}
	if ( ( scanner->buffer.current_position) == ( scanner->buffer.end_of_file) )
	{
	if ( _config_parser_scanner_eof_trans[( scanner->scanner.status)] > 0 ) {
		_trans = _config_parser_scanner_eof_trans[( scanner->scanner.status)] - 1;
		goto _eof_trans;
	}
	}

	}
#line 215 "_config_reader_scanner.rl"
    }

    /* Send the End Of File token to the parser */
    peach_config_reader_parser(parser, 0, 0, &config_tree);


    return config_tree;
}
