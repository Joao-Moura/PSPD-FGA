# Compilando arquivos

Caso alguma modificação seja feita no código fonte, é necessário recompilar o programa com o mpicc.

```bash
$ mpicc [nome_programa.c] -o [nome_executável]
```

# Executando os binários

Para tanto, deve-se utilizar o executável mpiexec de acordo com o ambiente instalado na sua máquina.

```bash
# Execução padrão do arquivo
$ mpiexec -np [numero_de_processos] ./[nome_do_binario]

# Calculando o tempo de execução (exclusivo para
# os arquivos ptp_client e ptpa_client)
$ time mpiexec -np [numero_de_processos] ./[nome_do_binario]

# Executando com uma entrada em arquivo
# ao invéz da entrada padrão de teclado
$ mpiexec -np [numero_de_processos] ./[nome_do_binario] < entrada.in
```

# Algumas limitações dos programas criados

Por ser uma palestra, todos os programas possuem limitações em relação ao número de processos que devem ser executados (não possuem validações e foram feito para um número "estático" de processos e fluxos).

- ptp_client e ptpa_client devem ser executados com **4** processos.
- comunicacao não possui um limite, porém deve-se estar atendo pois o número de linhas é equivalente ao número de processos iniciados.
- grupos deve ser executados com **4** processos, entretanto, é possível executar com mais processos sendo necessário atualizar os grupos. (ps.: esses processos não terão utilidade, visto que, o código já possível uma definição fixa do fluxo que deve ser seguindo para 4 processos)
