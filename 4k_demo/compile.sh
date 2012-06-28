rm *.o
rm 4k_intro
rm *.gz
echo "gcc -Os -fomit-frame-pointer -c main.c"
gcc -Os -fomit-frame-pointer -c main.c
echo "ld -dynamic-linker /lib/ld-linux.so.2 main.o /usr/lib/libSDL.so /usr/lib/libGL.so -o 4k_intro"
ld -dynamic-linker /lib/ld-linux.so.2 main.o /usr/lib/libSDL.so /usr/lib/libGL.so -o 4k_intro
ORIGINAL="$(du -b main.o |cut -c -5)"
echo "Original size $ORIGINAL"

SIZE1="$(du -b 4k_intro |cut -c -5)"
echo "strip -s -R .comment -R .gnu.version 4k_intro"
strip -s -R .comment -R .gnu.version 4k_intro
SIZE2="$(du -b 4k_intro |cut -c -5)"
SUM=$(($SIZE1 - $SIZE2))
echo "$SUM bytes less"
echo "sstrip 4k_intro"
sstrip 4k_intro
SIZE3="$(du -b 4k_intro |cut -c -5)"
SUM=$(($SIZE1 - $SIZE3))
echo "$SUM bytes less"
echo "gzip -cn9 4k_intro > 4k_intro.gz"
gzip -cn9 4k_intro > 4k_intro.gz
SIZE4="$(du -b 4k_intro.gz |cut -c -4)"
SUM=$(($SIZE1 - $SIZE4))
echo "$SUM bytes less"

echo ""
echo "Original size: $ORIGINAL"
echo "Final size: $SIZE4"
