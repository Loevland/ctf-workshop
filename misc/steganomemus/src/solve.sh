
echo "TESTING FLAG EXTRACTION ON..."
for img in $(find memes -name *.jpeg -o -name *.jpg -o -name *.png); do
    echo "$(basename $img): $(identify -verbose $img|grep TD{.*})"
done

