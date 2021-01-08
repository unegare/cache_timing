#!/usr/bin/env bash

#set -x

exec 9> /dev/cpu_dma_latency
echo -ne '\000\000\000\000' >&9

modprobe msr

PREF=$(perl -e "open(M,'<','/dev/cpu/0/msr') and seek(M,0x1a4,0) and read(M,\$_,8) and print unpack('Q', \$_) or exit(1)")
perl -e "open(M,'>','/dev/cpu/0/msr') and seek(M,0x1a4,0) and exit(8 != syswrite(M,pack('Q',$PREF | 0xf)))"

restore_pref() {
  perl -e "open(M,'>','/dev/cpu/0/msr') and seek(M,0x1a4,0) and exit(syswrite(M,pack('Q',$PREF & ~0xf)))"
}

trap restore_pref EXIT

if [ -z ${L1+x} ]; then
	L1=32768
fi
if [ -z ${L3+x} ]; then
	L3=$((8*2**20))
fi

TARGET=prog

make -s clean

for ((it=L1/2; it <= L3; it = (it<<1) )); do
	make -s CFLAGS="-DARR_LEN=$it" TARGET="$TARGET" && \
	taskset -c 0 ./${TARGET}
	make -s clean
done

make -s CFLAGS="-DARR_LEN=$((L3*3/2))" TARGET="$TARGET" && taskset -c 0 ./${TARGET}
make -s clean
