import sys

target_lang = sys.argv[3]
main_lang = sys.argv[4]
languages = sys.argv[5:]

src = open(sys.argv[1]).read()

src = src.replace('%LANG%', target_lang)

lang_or_blank = ''
if target_lang != main_lang:
    lang_or_blank = target_lang
src = src.replace('%LANG_OR_BLANK%', lang_or_blank)

cursor = 0
candidate = ''
candidates = languages.copy()
output = ''
current_language = ''
recursion = None

while cursor < len(src):
    if not current_language:
        if src[cursor] == '{':
            if len(candidates) == 1:
                current_language = candidates[0]
                recursion = 1
            else:
                output += candidate
                candidate = ''
                candidates = languages.copy()
                output += '{'
        else:
            candidate += src[cursor]

        candidates = [i for i in candidates if i.startswith(candidate)]

        if not candidates:
            output += candidate
            candidate = ''
            candidates = languages.copy()
    else:
        if src[cursor] == '}':
            recursion -= 1
            if not recursion:
                current_language = ''
                candidate = ''
                candidates = languages.copy()
            else:
                if current_language == target_lang: output += src[cursor]
        elif src[cursor] == '{':
            recursion += 1
            if current_language == target_lang: output += src[cursor]
        else:
            if current_language == target_lang:
                output += src[cursor]
    cursor += 1

open(sys.argv[2], 'w').write(output)
