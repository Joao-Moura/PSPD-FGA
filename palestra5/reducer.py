#!/usr/bin/env python
from operator import itemgetter
import sys


palavra_atual = None
qtd_palavra_atual = 0

for linha in sys.stdin:
    # Retira trailing whitespace da linha
    linha = linha.strip()
    # Separa a linha em palavras
    palavra, qtd_palavra = linha.split(' ', 1)

    try:
        # Validação para conversão de string para int
        qtd_palavra = int(qtd_palavra)
    except ValueError:
        continue

    # this IF-switch only works because Hadoop sorts map output
    # by key (here: word) before it is passed to the reducer
    if palavra_atual == palavra:
        qtd_palavra_atual += qtd_palavra
    else:
        if palavra_atual:
            print(f'{palavra_atual} {qtd_palavra_atual}')
        qtd_palavra_atual = qtd_palavra
        palavra_atual = palavra

if palavra_atual == palavra:
    print(f'{palavra_atual} {qtd_palavra_atual}')
