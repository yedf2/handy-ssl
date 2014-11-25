install
====

this project is part of handy.
because license is different, so this project is seperated.
first you install the openssl-devel. then make handy

usage
====

for use of openssl server and openssl client

example
====

./ssl-svr 443

./ssl-cli

内置的openssl工具
====

ssl服务器
echo abcd | openssl s_server -accept 2009 -key server.pem -cert server.pem

ssl客户端
openssl s_client -connect localhost:2009
