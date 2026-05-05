rm -rf docs
cp -r public docs

languages=("tok" "en" "ru")
main_language="tok"

for lang in ${languages[@]}; do
  mkdir docs/$lang
  for file in $(find src -type f); do
    python3 ./translate.py $file docs/$lang/${file#src/} $lang $main_language ${languages[@]}
  done
done


for file in docs/**/*.*; do
  python3 ./ucsur.py $file $file
done

mv docs/$main_language/* docs
