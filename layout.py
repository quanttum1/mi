import sys

source_file = sys.argv[1]
output_file = sys.argv[2]
layout_file = sys.argv[3]

layout_file = layout_file.removeprefix("./")
source_file = source_file.removeprefix("./")

if source_file == layout_file: exit()

src = open(source_file).read()

if "%LAYOUT%" in src:
    src = src.replace("%LAYOUT%", "")
    layout = open(layout_file).read()
    layout = layout.replace("%CONTENT%", src)
else:
    layout = src

open(output_file, "w").write(layout)
