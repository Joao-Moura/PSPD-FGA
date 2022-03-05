import json
import pika


# Cria conexão
connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
canal = connection.channel()

# Cria um canal exclusivo para a comunicação (request)
# Cliente -> Worker
canal.queue_declare(queue='fila_rpc')

def find_values(values):
    maior = float('-inf')
    menor = float('inf')
    
    for value in values:
        if value < menor:
            menor = value
        if value > maior:
            maior = value

    return menor, maior

def on_request(canal, metodo, propriedades, corpo):
    vec = json.loads(corpo)
    print(f'Estrutura recebida de tamanho {vec["len"]}')
    response = find_values(vec['values'])
    print(f'Menor valor encontrado: {response[0]}, maior valor encontrado: {response[1]}')

    # Publica mensagem no canal exclusivo do cliente
    # através propriedade reply_to settada no Client
    canal.basic_publish(
        exchange='', routing_key=propriedades.reply_to,
        properties=pika.BasicProperties(
            correlation_id=propriedades.correlation_id),
        # Desserialização das informações do JSON
        body=json.dumps({
            'menor': response[0],
            'maior': response[1]
        })
    )
    canal.basic_ack(delivery_tag=metodo.delivery_tag)

# Utiliza a divisão justa de tarefas
canal.basic_qos(prefetch_count=1)
canal.basic_consume(queue='fila_rpc', on_message_callback=on_request)

print('[*] Esperando mensagens. CTRL+C para sair')
canal.start_consuming()
