call 命令
1. call の次の命令をスタックにプッシュ
2. call の引数として与えられたアドレスにジャンプ

ret 命令
1. スタックしているアドレスを１つポップ
2. そのアドレスにジャンプ

x86
x86は1978年にintelが開発した32bitプロセッサ用の命令セット

x86-64
AMD社が開発したx86を64bitプロセッサ用に拡張したの命令セット

docker run --rm -v .:/9cc -w /9cc compilerbook make test

docker run --rm -it -v .:/9cc -w /9cc compilerbook
docker run -it --rm -v .:/9cc -w /9cc --name 9cc compilerbook /bin/bash

docker run -d -it --rm -v .:/9cc -w /9cc --name 9cc compilerbook