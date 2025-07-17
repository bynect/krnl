#!/bin/env bash

function usage {
    printf 'usage: %s {img | iso} [path]\n' $(basename "$0") 1>&2
    exit 1
}

QEMU='qemu-system-i386 -d cpu_reset'
MONITOR='-monitor stdio'

if [ $# -eq 1 ]
then
    KRNLIMG='bin/krnl.img'
    KRNLISO='bin/krnl.iso'
elif [ $# -eq 2 ]
then
    KRNLIMG="$2"
    KRNLISO="$2"
else
    usage
fi

case "$1" in
    img)
        $QEMU $MONITOR -drive format=raw,file=$KRNLIMG
        ;;
    iso)
        $QEMU $MONITOR -cdrom $KRNLISO
        ;;
    *)
        usage
        ;;
esac
