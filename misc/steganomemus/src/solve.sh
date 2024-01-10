
# make sure in correct working directory
cwd=$(dirname $BASH_SOURCE)
cd $cwd

echo "TESTING FLAG EXTRACTION ON..."
for img in $(find memes -name *.jpeg -o -name *.jpg -o -name *.png); do
    echo "$(basename $img): $(identify -verbose $img|grep TD{.*})"
done

cd - > /dev/null
