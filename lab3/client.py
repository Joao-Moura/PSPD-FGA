import json
from math import sqrt
import pika
import sys
import threading
import uuid


# Objeto simples para armazenar o retorno
class MinEMaxValor:
    menor = -1
    maior = -1

    def set_valores(self, menor, maior):
        self.menor = menor
        self.maior = maior

    def __str__(self):
        return f'Menor: {self.menor}, maior: {self.maior}'


class VecRpcClient(object):

    def __init__(self):
        # Cria conexão
        self.connection = pika.BlockingConnection(
            pika.ConnectionParameters(host='localhost'))
        self.canal = self.connection.channel()

        # Cria um canal exclusivo para a comunicação (request) -> assíncrono
        self.canal.queue_declare(queue='fila_rpc')

        # Cria um canal exclusivo para a comunicação (response)
        # Worker -> Cliente
        resultado = self.canal.queue_declare(queue='', exclusive=True)
        self.nome_fila = resultado.method.queue

        self.canal.basic_consume(
            queue=self.nome_fila,
            on_message_callback=self.on_response,
            auto_ack=True
        )

    def on_response(self, canal, metodo, propriedades, corpo):
        # Realiza checagem para evitar que responses
        # de Workers cheguem nos Clientes errados
        if self.corr_id == propriedades.correlation_id:
            self.resposta = corpo

    def call(self, n, vec, resps):
        self.resposta = None
        self.corr_id = str(uuid.uuid4())

        # Realiza a publicação da mensagem na fila do Worker (request)
        print('Enviando valores para o worker...')
        self.canal.basic_publish(
            exchange='',
            routing_key='fila_rpc',
            properties=pika.BasicProperties(
                reply_to=self.nome_fila,
                correlation_id=self.corr_id,
            ),
            # Serialização das informações em JSON
            body=json.dumps({'len': n, 'values': vec})
        )

        # Entra em loop infinito enquanto não receber uma resposta
        while self.resposta is None:
            self.connection.process_data_events()

        # Finaliza conexão
        self.connection.close()
        # Salva valores
        resps.set_valores(**json.loads(self.resposta))


# Função responsável pela criação da comunicação
# e recebimento da resposta do worker
def thread_func(inicio, final, vec, resps):
    vec_rpc = VecRpcClient()
    vec_rpc.call(final-inicio, vec, resps)


if __name__ == "__main__":
    # Validações de chamada do programa
    if len(sys.argv) < 3:
        raise AttributeError(f'Chamada correta: python {sys.argv[0]} num_workers/threads tam_vetor')

    # Atribuição dos valores
    qtd_workers = int(sys.argv[1]) if len(sys.argv) > 1 else 1
    n = int(sys.argv[2])
    total_size = (sys.getsizeof(float) * n)

    # Validação de memória, pois o python não
    # tem um controle sobre o uso (principalmente listas)
    if total_size > 8589934592 and not (len(sys.argv) > 3 and sys.argv[3] == '-f'):
        print(
            'Esse vetor possívelmente não caberá na memória do computador.\n' \
            f'Tamanho calculado para {n} elementos: {total_size / 1073741824:.2f} GiB.\n' \
            'Continuar ? (S/n)'
        )
        resp = input()
        if resp == 'n':
            exit(0)

    print("Preparando valores...")
    tam_por_worker = n // qtd_workers
    # Validação das limitações do RabbitMQ sobre
    # o tamanho máximo das filas: 134217728 bytes
    if tam_por_worker > 10000000:
        raise AttributeError(f'Necessário mais workers para processar a entrada de {n} elementos.')

    # Geração do vetor e inicialização da lista de threads
    vec = [sqrt((x - n/2)**2) for x in range(n)]
    threads = list()

    print("Enviando valores")
    for worker in range(qtd_workers):
        inicio = worker * tam_por_worker
        final = inicio + tam_por_worker
        if worker + 1 >= qtd_workers:
            final = inicio + tam_por_worker + (n % qtd_workers)

        # Criação das threads e alocação dos espaços para as respostas
        resps = MinEMaxValor()
        thread = threading.Thread(target=thread_func, args=(inicio, final, vec[inicio:final], resps))
        threads.append((thread, resps))
        thread.start()

    # Cálculo do menor e maior valor
    # dentre as respostas das threads
    maior = float('-inf')
    menor = float('inf')
    for thread, resps in threads:
        thread.join()
        if resps.menor < menor:
            menor = resps.menor
        if resps.maior > maior:
            maior = resps.maior
        
    print(f"Menor valor: {menor}, Maior valor: {maior}")
