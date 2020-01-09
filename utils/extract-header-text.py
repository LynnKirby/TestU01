#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby
#
# This script generates a Markdown file from specially marked-up headers. The
# parser is currently very fragile and expects correct input otherwise it'll
# break. The document structure it expects is:
#
#     /*
#      * License header block. This gets turned into an HTML comment.
#      */
#
#     #ifndef INCLUDE_GUARD_H
#     #define INCLUDE_GUARD_H
#
#     [main document]
#
#     #endif
#
# Within the main document, block comments starting with `/**` indicate the
# start of a documentation section. The contents are printed verbatim.
# Code in-between documentation sections is turned into Markdown code blocks.
#
# FIXME: This initial version is very hacky and needs to be cleaned up.

import argparse
from pathlib import Path
import sys

# States
CODE = 0
LICENSE_COMMENT = 1
DOC_COMMENT = 2

def main() -> int:
    parser = argparse.ArgumentParser(
        description='Extract documentation from header comments.')
    parser.add_argument('input', help='input file')
    parser.add_argument('-o',
        help='output file (default: stdout)', metavar='outfile')
    args = parser.parse_args()

    if args.o is not None:
        out = Path(args.o).open(mode='w')
    else:
        out = sys.stdout

    line_count = 0
    state = CODE
    seen_license_comment = False
    hidden = True
    buffer = []

    def flush_buffer(last_chunk=False):
        if len(buffer) == 0:
            return

        # Delete all leading blank lines
        while len(buffer) > 0:
            if buffer[0].strip() == '':
                del buffer[0]
            else:
                break

        # Delete all trailing blank lines
        while len(buffer) > 0:
            if buffer[-1].strip() == '':
                del buffer[-1]
            else:
                break

        # Delete the include guard #endif plus any new trailing blank lines
        if last_chunk:
            if state != CODE or buffer[-1].strip() != '#endif':
                sys.stderr.write(
                    f'{args.input}: error: could not find header #endif\n')
                sys.exit(1)
            del buffer[-1]

            while len(buffer) > 0:
                if buffer[-1].strip() == '':
                    del buffer[-1]
                else:
                    break

        # Write the chunk prologue. Either code block or HTML comment start.
        if state == CODE and not hidden:
            out.write('```c')
        elif state == LICENSE_COMMENT:
            out.write('<!--')
        out.write('\n')

        # Write the chunk.
        for line in buffer:
            out.write(line.rstrip())
            out.write('\n')

        # Write the chunk epilogue. Either a code block or HTML comment end.
        if state == CODE and not hidden:
            out.write('```')
        elif state == LICENSE_COMMENT:
            out.write('-->')
        out.write('\n')

        buffer.clear()

    for line in Path(args.input).open():
        line_count += 1
        strip_line = line.strip()

        if state == CODE:
            if strip_line.startswith('/**'):
                flush_buffer()
                state = DOC_COMMENT
                hidden = False
            elif strip_line.startswith('/*'):
                flush_buffer()
                if seen_license_comment:
                    state = REGULAR_COMMENT
                else:
                    state = LICENSE_COMMENT
            elif not hidden:
                buffer.append(line)

        elif state in (LICENSE_COMMENT, DOC_COMMENT):
            if strip_line.startswith('* '):
                buffer.append(strip_line[2:])
            elif strip_line.startswith('*/'):
                flush_buffer()
                state = CODE
            elif strip_line == '*':
                buffer.append('')
            else:
                sys.stderr.write(
                    f'{args.input}:{line_count}: error: invalid syntax\n')
                return 1

    if state in (DOC_COMMENT, LICENSE_COMMENT):
        sys.stderr.write(f'{args.input}:{line_count}: error: unclosed comment\n')
        return 1

    flush_buffer(last_chunk=True)
    return 0


if __name__ == '__main__':
    sys.exit(main())
