rm -rf dist
cp -r public dist

languages=("tok" "en" "ru")
main_language="tok"

for lang in ${languages[@]}; do
  mkdir dist/$lang
  for file in $(find src -type f); do
    python3 ./translate.py $file dist/$lang/${file#src/} $lang $main_language ${languages[@]}
  done
done


for file in dist/**/*.*; do
  python3 ./ucsur.py $file $file
done

mv dist/$main_language/* dist
