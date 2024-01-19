
ADDONS =
CFLAGS = -fno-stack-protector -no-pie -o vuln

all: overflow

overflow: vuln.c vuln
	@gcc $(CFLAGS) vuln.c

inspect: vuln-inspect.c vuln
	@gcc $(CFLAGS) $(ADDONS) vuln-inspect.c

clean:
	@rm -f vuln