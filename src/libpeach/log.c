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

#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <peach.h>

#define DATE_STRING_LENGTH (sizeof("1999/01/01 00:00:00 * ") - 1)

void
peach_log_print
            (FILE * stream, 
            ...)
{
    va_list arguments;
    time_t current_time_epoch;
    struct tm current_time;
    char * provided_format;
    char * format;

    va_start(arguments, stream);

    provided_format = va_arg(arguments, char *);

    format = malloc(DATE_STRING_LENGTH + strlen(provided_format) + 1);
    assert(format != 0);

    time(&current_time_epoch);
    localtime_r(&current_time_epoch, &current_time);

    snprintf(format, DATE_STRING_LENGTH + 1,  
                "%4d/%02d/%02d %02d:%02d:%02d * ",
                current_time.tm_year + 1900,
                current_time.tm_mon,
                current_time.tm_mday,
                current_time.tm_hour,
                current_time.tm_min,
                current_time.tm_sec);

    strncpy(format + DATE_STRING_LENGTH, provided_format, 
                strlen(provided_format) + 1);

    vfprintf(stream, format, arguments);

    free(format);

    va_end(arguments);
}
