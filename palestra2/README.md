# Rodando o RPC através do _broker_ RabbitMQ

```bash
# Inicie o RabbitMQ (comando retirado da documentação)
$ docker run -it --rm --name rabbitmq -p 5672:5672 -p 15672:15672 rabbitmq:3.9-management

# Devido a arquitetura feita, é necessário iniciar
# ao menos uma vez o worker para criação da fila.
# Após isso, a arquitetura se tornada totalmente assíncrona
$ python worker.py

# Por fim, rode o Cliente e envie o valor para se calcular fibonacci
$ python client.py
```
