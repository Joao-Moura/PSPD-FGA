import pika


connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
canal = connection.channel()

canal.queue_declare(queue='fila_rpc')

def fib(n):
    if n in [0, 1]:
        return n
    else:
        return fib(n-1) + fib(n-2)

def on_request(canal, metodo, propriedades, corpo):
    n = int(corpo)
    response = fib(n)

    canal.basic_publish(
        exchange='', routing_key=propriedades.reply_to,
        properties=pika.BasicProperties(
            correlation_id=propriedades.correlation_id),
        body=str(response)
    )

canal.basic_qos(prefetch_count=1)
canal.basic_consume(queue='fila_rpc', on_message_callback=on_request)

print('[*] Esperando mensagens. CTRL+C para sair')
canal.start_consuming()
