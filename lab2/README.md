# Compilando os códigos do lab2

## 1 _Worker_ e 1 _Client_

```bash
# Entre na pasta letra_a/
$ cd letra_a/

# Execute o comando make para compilar o servidor e o cliente
# obs.: esse comando irar gerar o server tcps e o client tcpc
$ make

# Inicie o server no seguinte formato
# ./tcps [ip_servidor] [porta_servidor]
$ ./tcps 127.0.0.1 1234

# Inicie o client no seguinte formato
# ./tcpc [ip_server] [porta_server] [tamanho_vetor]
$ ./tcpc 127.0.0.1 1234 1000000
```

## Múltiplos _Workers_ e 1 _Client_

```bash
# Entre na pasta letra_a/
$ cd letra_a/

# Execute o comando make para compilar o servidor e o cliente
# obs.: esse comando irar gerar o server tcps e o client tcpc
$ make

# Inicie o(s) server(s) no seguinte formato
# ./tcps [ip_servidor] [porta_servidor]
$ ./tcps 127.0.0.1 1234

# Inicie o client no seguinte formato
# ./tcpc [quantidade_servers] <[ip_server] [porta_server]> [tamanho_vetor]
$ ./tcpc 3 127.0.0.1 1234 127.0.0.1 1235 127.0.0.1 1236 1000000
```

## Medição de desempenho
- Utilizando a medição manual através da função time disponibilizada nos sistemas UNIX, para uma entrada padrão de 1.000.000.000 e considerando um único computador com uma CPU de 8 núcleos, obtiveram-se os seguintes resultados:

```bash
# 2 Workers:
./tcpc 2 127.0.0.1 1234 127.0.0.1 1233 1000000000                              2,28s user 1,95s system 84% cpu 4,978 total

# 4 Workers:
./tcpc 4 127.0.0.1 1234 127.0.0.1 1233 127.0.0.1 1231 127.0.0.1 1232           2,33s user 1,90s system 86% cpu 4,904 total

# 6 Workers:
./tcpc 6 127.0.0.1 1234 127.0.0.1 1233 127.0.0.1 1231 127.0.0.1 1232 127.0.0.  2,20s user 1,98s system 86% cpu 4,847 total

# 8 Workers:
./tcpc 8 127.0.0.1 1234 127.0.0.1 1233 127.0.0.1 1231 127.0.0.1 1232 127.0.0.  2,21s user 2,05s system 87% cpu 4,898 total

# 10 Workers:
./tcpc 10 127.0.0.1 1234 127.0.0.1 1233 127.0.0.1 1231 127.0.0.1 1232  1235    2,25s user 2,04s system 86% cpu 4,939 total
```
