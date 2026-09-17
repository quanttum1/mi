gcc ./src/cx2c.c -o ./cache/cx2c
./cache/cx2c ./src/main.cx ./cache/main_built.c
cp ./src/da.h ./src/str_appendf.c ./cache/
gcc ./cache/main_built.c -o ./cache/build
./cache/build
