
# make sure in correct working directory
cwd=$(dirname $BASH_SOURCE)
cd $cwd

flag=$(cat flag.txt)

# select one random image
orgimg=$(find original -name *.jpeg -o -name *.jpg -o -name *.png|shuf -n 1)
orgimg=$(basename $orgimg)

# output image path
mkdir -p memes
flagimg=memes/$orgimg

# copy non-flag images
cp original/* -t memes
rm memes/$orgimg

# create new image with flag in comment
exiftool                \
    -comment=$flag      \
    -out     $flagimg   \
    original/$orgimg    \
    > /dev/null

if [ $? -ne 0 ]; then
    echo "exiftool error := $? for '$orgimg'"
    exit 1
fi

echo "inserted flag into '$flagimg'"
echo

./solve.sh

# move out of src/
mv memes ..

cd - > /dev/null
