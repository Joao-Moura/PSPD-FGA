# Laboratório 1 PSPD (RPC)
## Letra A
### Compilando para a arquitetura com um _worker_ e sem _threads_

```bash
$ cd letra_a/

## Compile para utilizar em sua máquina
$ make
```

### Rodando
- Utilizando 2 terminais para e exeução do server e do client

```bash
## No primeiro terminal iniciar o servidor
$ ./lab1_a_server

## No segundo terminal iniciar o client
## ./lab1_a_client [HOST] [TAM_VETOR]
$ ./lab1_a_client 127.0.0.1 10
```

- Utilizando apenas 1 terminal para e exeução do server e do client

```bash
## Abra o servidor em background
## Para fechar o server é necessário dar um kill no processo
$ ./lab1_a_server &

## Realizer a chamada pelo client
## ./lab1_a_client [HOST] [TAM_VETOR]
$ ./lab1_a_client 127.0.0.1 10
```

## Letra B
### Compilando para a arquitetura com dois _workers_ e sem _threads_

```bash
$ cd letra_b/

## Compile para utilizar em sua máquina
$ make

## Inicie um docker para o segundo worker
## Esse comando já irá abrir o server dentro do docker
## Recomendado utilizar '-p' para nomear o container
$ docker-compose -p maquina_1 up --build
```

### Rodando
- Utilizando 3 terminais para e execução do server e do client

```bash
## No primeiro terminal iniciar o servidor
$ ./lab1_b_server

## Utilize o seguinte comando para
## pegar o ip do docker em execução
## docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' [NOME CONTAINER]_rpcserver_1
$ docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' maquina_1_rpcserver_1

## No segundo terminal iniciar o client
## ./lab1_b_client [QTD_HOSTS] [HOST1 ... HOSTN] [TAM_VETOR]
$ ./lab1_b_client 2 127.0.0.1 127.23.0.2 10000
```

## Letra B Extra 1
### Compilando para a arquitetura com vários _workers_ e sem _threads_

```bash
$ cd letra_b/

## Compile para utilizar em sua máquina
$ make

## Inicie um docker para a quantidade de workers desejada
## Esse comando já irá abrir o server dentro do docker
## Recomendado utilizar '-p' para nomear o container
$ docker-compose -p maquina_1 up --build
```

### Rodando
- Utilizando 4+ terminais para e execução do server e do client

```bash
## No primeiro terminal iniciar o servidor
$ ./lab1_b_server

## Utilize o seguinte comando para
## pegar o ip do docker em execução
## docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' [NOME CONTAINER]_rpcserver_1
$ docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' maquina_1_rpcserver_1

## No segundo terminal iniciar o client
## ./lab1_b_client [QTD_HOSTS] [HOST1 ... HOSTN] [TAM_VETOR]
$ ./lab1_b_client 2 127.0.0.1 127.23.0.2 10000
```

## Letra B Extra 2 (Extra com Threads)
- Atenção porque essa arquitetura exige bastante do processador visto que utiliza _threads_
- TODO: permitir a arquitetura ciclar, utilizando menos _threads_ pelos _workers_ que estiverem parados

### Compilando para a arquitetura com vários _workers_ e várias _threads_

```bash
$ cd extra_com_threads/

## Compile para utilizar em sua máquina
$ make

## Inicie um docker para a quantidade de workers desejada
## Esse comando já irá abrir o server dentro do docker
## Recomendado utilizar '-p' para nomear o container
$ docker-compose -p maquina_1 up --build
```

### Rodando
- Utilizando 4+ terminais para e execução do server e do client

```bash
## No primeiro terminal iniciar o servidor
$ ./lab1_b_server

## Utilize o seguinte comando para
## pegar o ip do docker em execução
## docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' [NOME CONTAINER]_rpcserver_1
$ docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' maquina_1_rpcserver_1

## No segundo terminal iniciar o client
## ./lab1_b_client [QTD_HOSTS] [HOST1 ... HOSTN] [TAM_VETOR]
$ ./lab1_b_client 2 127.0.0.1 127.23.0.2 10000
```

## Medição de desempenho
- TODO: Adicionar script automatizado para realizar a medição
- Através da medição manual e que fosse suportada pelo meu computador, foram obtidos os seguintes resultados para uma entrada de 1.000.000.000 posições

```bash
./letra_a/lab1_a_client 127.0.0.1 1000000000  11,97s user 4,80s system 69% cpu 24,235 total (killed)
./letra_b/lab1_b_client 2 127.0.0.1 172.23.0.2 1000000000 10,82s user 2,09s system 65% cpu 19,791 total
./letra_b/lab1_b_client 3 127.0.0.1 172.23.0.2 172.24.0.2 1000000000 10,77s user 2,01s system 63% cpu 20,248 total
./extra_com_threads/lab1_b_client 3 127.0.0.1 172.23.0.2 172.24.0.2 1000000000 17,73s user 5,14s system 197% cpu 11,566 total
./extra_com_threads/lab1_b_client 4 127.0.0.1 172.23.0.2 172.24.0.2 172.25.0.2 1000000000 19,61s user 6,59s system 229% cpu 11,390 total
```

## Observações
- Dockerfile, docker-compose e demais códigos podem e devem ser melhorados
- Makefile possui duas versões. A versão .docker é voltada para distribuições debian-based, enquando a versão normal foi feita para sistemas arch
- Os TODO's destacados nesse README foram adicionados como uma forma de evolução ao programa
