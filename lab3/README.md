# Rodando o RPC através do _broker_ RabbitMQ

## 1. Inicie uma instância do RabbitMQ

```bash
# Inicie o RabbitMQ (comando retirado da documentação)
$ docker run -it --rm --name rabbitmq -p 5672:5672 -p 15672:15672 rabbitmq:3.9-management
```

## 2. Inicie o Client
### 2.1 Assíncrono
É possível iniciar o client sem ter iniciado nenhum dos workers, para isso execute:

```bash
# Vale a pena ressaltar, que pode-se iniciar um número
# superior de threads que o de workers planejado, entretanto
# o RabbitMQ irá redistribuir as mensagens para os workers
# que estiverem livres.
$ python client.py [num_workers/threads] [tam_vetor] [-f para forçar execução]
```

### 2.2 Síncrono 
É possível também iniciar o client depois na instânciação de todos os workers, nesse cenário, a mensagem será imediatamente processada:

```bash
# Da mesma forma que o processo assíncrono, caso não existam
# workers rodando equivalente a quantidade inserida, o RabbitMQ
# irá redistribuir as mensagens para aqueles que estiverem livres.
$ python client.py [num_workers/threads] [tam_vetor] [-f para forçar execução]
```

## 3. Inicie os Workers

```bash
$ python worker.py
```

## 4. Limitações encontradas
Durante a resolução, duas limitações em relação ao tamanho do vetor foram encontradas, sendo elas:
- Não é possível (para o meu computador de 8GiB de RAM) suportar um vetor acima de 50.000.000 posições
- O RabbitMQ limita o valor máximo de elementos que uma fila pode armazenar. Para suprir essa limitação, e necessário iniciar o programa com um número de workers/threads maior
