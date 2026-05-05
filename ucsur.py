import sys
import subprocess

def sitelen_ucsur(s):
    return subprocess.run(
        ["sitelen-ucsur"],
        input=s,
        capture_output=True,
        text=True
    ).stdout

if len(sys.argv) != 3:
    print("o kepeken nasin ni: python3 compile.py <input> <output>")

try:
    src = open(sys.argv[1]).read()
except UnicodeDecodeError:
    exit()

output = ""

cursor = 0
is_ucsur = False
ucsur_str = ''

while cursor < len(src):
    if not is_ucsur:
        if src[cursor] == 'u' and src[cursor + 1] == '{':
            cursor += 1
            is_ucsur = True
            ucsur_str = ''
        else:
            output += src[cursor]
    else:
        if src[cursor] == '}':
            output += sitelen_ucsur(ucsur_str)
            is_ucsur = False
        else:
            ucsur_str += src[cursor]

    cursor += 1

open(sys.argv[2], "w").write(output)
