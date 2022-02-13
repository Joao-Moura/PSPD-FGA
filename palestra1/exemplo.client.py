import logging

import grpc
import exemplo_pb2
import exemplo_pb2_grpc


def le_entrada():
    print("Insira os dois operandos:")
    x = int(input())
    y = int(input())
    return {
        "operandoUm": x,
        "operandoDois": y
    }


def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = exemplo_pb2_grpc.CalculadoraStub(channel)
        response = stub.CalculaOperandos(exemplo_pb2.OperandosRequest(**le_entrada()))
        print(
            f"Soma = {response.soma}, Subtração = {response.subtracao}, "
            f"Divisão = {response.divicao} e Multiplicação = {response.divicao}"
        )


if __name__ == '__main__':
    logging.basicConfig()
    run()
