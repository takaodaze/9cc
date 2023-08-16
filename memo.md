call 命令
1. call の次の命令をスタックにプッシュ
2. call の引数として与えられたアドレスにジャンプ

ret 命令
1. スタックしているアドレスを１つポップ
2. そのアドレスにジャンプ

docker run --rm -v .:/9cc -w /9cc compilerbook make test

docker run --rm -it -v .:/9cc -w /9cc compilerbook
docker run -it --rm -v .:/9cc -w /9cc --name 9cc compilerbook /bin/bash

docker run -d -it --rm -v .:/9cc -w /9cc --name 9cc compilerbook
