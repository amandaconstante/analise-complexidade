# Análise de Complexidade de Árvores Balanceadas 
### (AVL, Rubro-Negra e B)
#### _Trabalho final da disciplina de Projeto de Arquivos_
### Objetivo
Este projeto tem como objetivo analisar a complexidade algorítmica das operações de inserção e remoção (considerando balanceamentos) em três estruturas de dados:

* Árvore AVL

* Árvore Rubro-Negra

* Árvore B (com ordens 1, 5 e 10)

#### Metodologia
Foram gerados conjuntos de dados com tamanhos variando de 1 a 10.000 elementos.

As chaves foram geradas aleatoriamente (caso médio), utilizando a função rand() da linguagem C.

Cada experimento foi repetido 10 vezes, e os resultados foram calculados com base na média das execuções.

Foram contadas as seguintes operações:

* Inserções realizadas

* Remoções realizadas

* Operações de balanceamento (como rotações ou divisões de nós)

### Estruturas Avaliadas:
* AVL
- Árvores binárias com balanceamento por rotação
* Rubro-Negra
- Árvores binárias balanceadas por cores
* B (ordem 1, 5, 10)
- Árvores de múltiplos filhos com divisão de nós

### Resultados
Foram gerados dois gráficos de linha:

Gráfico de Inserções

Gráfico de Remoções

O eixo X representa o tamanho dos conjuntos de dados (de 1 a 10.000).

O eixo Y representa o número médio de operações realizadas, em escala logarítmica.

Cada gráfico contém 5 curvas:

- AVL

- Rubro-Negra

- Árvore B com ordem 1

- Árvore B com ordem 5

- Árvore B com ordem 10

### Execução
Os experimentos foram implementados em C, com um script Python auxiliar para gerar os gráficos.

* Compilação
```
  bash
  Copiar
  Editar
  gcc avl.c -o avl
  gcc rubro_negra.c -o rubro_negra
  gcc arvore_b.c -o arvore_b
```

* Execução
``` 
  bash
  Copiar
  Editar
  ./avl
  ./rubro_negra
  ./arvore_b
``` 
Esses comandos geram arquivos `.txt` contendo os resultados médios por estrutura.

* Geração dos gráficos
```
python3 gerar_grafico.py
```

O script irá gerar o arquivo grafico.png com os gráficos finais para o relatório.

* Estrutura de Arquivos
```
.
├── avl.c
├── rubro_negra.c
├── arvore_b.c
├── gerar_grafico.py
├── resultados_avl.txt
├── resultados_rubro_negra.txt
├── resultados_arvore_b.txt
├── grafico.png
└── README.md
```

#### Conclusão
O projeto foi desenvolvido para comparar a eficiência das operações em diferentes estruturas de árvores balanceadas.

As implementações consideram o número real de operações realizadas, refletindo o custo dos balanceamentos.

A árvore B demonstrou melhor desempenho em termos de número de rotações, especialmente nas ordens maiores, sendo portanto, mais eficiente para grandes volumes de dados.
