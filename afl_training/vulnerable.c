#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define INPUTSIZE 100

int process(char *input)
{
	char *out;
	char *rest;
	int len;
	if (strncmp(input, "u ", 2) == 0)
	{ // upper case command
		char *rest;
		len = strtol(input + 2, &rest, 10); // how many characters of the string to upper-case
		rest += 1;							// skip the first char (should be a space)
		out = malloc(len + strlen(input));  // could be shorter, but play it safe
		if (len > (int)strlen(input))
		{
			printf("Specified length %d was larger than the input!\n", len);
			return 1;
		}
		else if (out == NULL)
		{
			printf("Failed to allocate memory\n");
			return 1;
		}
		for (int i = 0; i != len; i++)
		{
			out[i] = rest[i] - 32; // only handles ASCII
		}
		out[len] = 0;
		strcat(out, rest + len); // append the remaining text
		printf("%s", out);
		free(out);
	}
	else if (strncmp(input, "head ", 5) == 0)
	{ // head command
		if (strlen(input) > 6)
		{
			len = strtol(input + 4, &rest, 10);
			rest += 1;		  // skip the first char (should be a space)
			rest[len] = '\0'; // truncate string at specified offset
			printf("%s\n", rest);
		}
		else
		{
			fprintf(stderr, "head input was too small\n");
		}
	}
	else if (strcmp(input, "surprise!\n") == 0)
	{
		// easter egg!
		*(char *)1 = 2;
	}
	else
	{
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char *usage = "Usage: %s\n"
				  "Text utility - accepts commands and data on stdin and prints results to stdout.\n"
				  "\tInput             | Output\n"
				  "\t------------------+-----------------------\n"
				  "\tu <N> <string>    | Uppercased version of the first <N> bytes of <string>.\n"
				  "\thead <N> <string> | The first <N> bytes of <string>.\n";
	char input[INPUTSIZE] = {0};

	// Slurp input
	if (read(STDIN_FILENO, input, INPUTSIZE) < 0)
	{
		fprintf(stderr, "Couldn't read stdin.\n");
	}

	int ret = process(input);
	if (ret)
	{
		fprintf(stderr, usage, argv[0]);
	};
	return ret;
}

// MIT License.

// Copyright 2016, 2017 Thales UK Ltd
// Copyright 2019 Michael Macnair

// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.