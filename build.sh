rm -rf docs
cp -r public docs

for file in $(find -type f -name "*.html"); do
  python3 ./layout.py $file docs/${file#./src/} src/layout.html
done


languages=("tok" "en" "ru")
main_language="tok"

for file in $(find docs -type f -name "*.html"); do
  for lang in ${languages[@]}; do
    mkdir -p docs/$lang
    python3 ./translate.py $file docs/$lang/${file#docs/} $lang $main_language ${languages[@]}
  done
done


for file in docs/**/*.*; do
  python3 ./ucsur.py $file $file
done

mv docs/$main_language/* docs
rm docs/$main_language -r
