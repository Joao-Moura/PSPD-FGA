from concurrent import futures
import logging

import grpc
import exemplo_pb2
import exemplo_pb2_grpc


class Calculadora (exemplo_pb2_grpc.CalculadoraServicer):

    def CalculaOperandos(self, request, context):
        x = request.operandoUm
        y = request.operandoDois

        return exemplo_pb2.ResultadoResponse(
            soma= (x+y), subtracao=(x-y),
            multiplicacao=(x*y), divicao=(x/y)
        )


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    exemplo_pb2_grpc.add_CalculadoraServicer_to_server(
        Calculadora(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()
