/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Derick Rethans
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "timelib.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	timelib_time     *b = NULL, *e = NULL;
	timelib_rel_time *p = NULL;
	int               r = 0;
	int               i, errors_found;
	timelib_error_container *errors;

	timelib_strtointerval(argv[1], strlen(argv[1]), &b, &e, &p, &r, &errors);
	if (errors->warning_count) {
		printf("W=%d ", errors->warning_count);
	}
	if (errors->error_count) {
		printf("E=%d ", errors->error_count);
	}
	printf("\n");
	if (b) {
		printf("B ");
		timelib_dump_date(b, 1);
		timelib_time_dtor(b);
	}
	if (e) {
		printf("E ");
		timelib_dump_date(e, 1);
		timelib_time_dtor(e);
	}
	if (p) {
		printf("P ");
		timelib_dump_rel_time(p);
		timelib_rel_time_dtor(p);
	}
	if (r) {
		printf("Recurrences: %d\n", r);
	}

	if (errors->warning_count) {
		printf("Warnings found while parsing '%s'\n", argv[1]);
		for (i = 0; i < errors->warning_count; i++) {
			printf("W %s @ pos %d (char=[%c])\n", errors->warning_messages[i].message, errors->warning_messages[i].position, errors->warning_messages[i].character);
		}
	}
	if (errors->error_count) {
		printf("Errors found while parsing '%s'\n", argv[1]);
		for (i = 0; i < errors->error_count; i++) {
			printf("E %s @ pos %d (char=[%c])\n", errors->error_messages[i].message, errors->error_messages[i].position, errors->error_messages[i].character);
		}
	}

	errors_found = errors->error_count ? 1 : 0;
	timelib_error_container_dtor(errors);
	return errors_found;
}
