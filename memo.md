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

進捗
https://www.sigbus.info/compilerbook#%E3%82%B9%E3%83%86%E3%83%83%E3%83%972%E5%8A%A0%E6%B8%9B%E7%AE%97%E3%81%AE%E3%81%A7%E3%81%8D%E3%82%8B%E3%82%B3%E3%83%B3%E3%83%91%E3%82%A4%E3%83%A9%E3%81%AE%E4%BD%9C%E6%88%90