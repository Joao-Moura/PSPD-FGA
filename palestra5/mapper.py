#!/usr/bin/env python
import sys


for linha in sys.stdin:
    # Retira trailing whitespace da linha
    linha = linha.strip()
    # Separa a linha em palavras
    palavras = linha.split()

    for palavra in palavras:
        print(f'{palavra} 1')
