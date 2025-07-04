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
* **Árvore AVL:** Árvores binárias altamente balanceada. O balanceamento é realizado por meio de rotações.
* **Árvore Rubro-Negra:** Árvores binárias de busca auto-balanceadas que utilizam um esquema de cores (vermelho/preto) e regras específicas para manter o balanceamento, garantindo que o caminho mais longo de qualquer nó raiz a uma folha não seja mais que duas vezes o comprimento do caminho mais curto.
* **Árvore B (Ordem 1, 5, 10):** Árvores de múltiplos filhos com divisão de nós.

### Resultados
Abaixo estão os gráficos que representam o número médio de operações de balanceamento realizadas conforme o tamanho da entrada. O eixo Y está em escala logarítmica para evidenciar o crescimento assintótico.
#### Inserções: 
![image](https://github.com/user-attachments/assets/82194c50-8816-420d-9462-9e9500b89b07)
#### Remoções:
![image](https://github.com/user-attachments/assets/d86173eb-8e98-493b-b10b-a6fa13717646)



## Discussão dos Resultados
A análise do gráfico "Comparação de Operações nas Árvores" revela padrões distintos e esperados de desempenho entre as estruturas:

* **Comportamento Logarítmico:** Todas as estruturas de árvores balanceadas demonstram um crescimento logarítmico no número de operações à medida que o tamanho da entrada aumenta. Isso é evidenciado pela forma quase linear das curvas no gráfico com escala logarítmica no eixo Y, confirmando a complexidade teórica de $O(\log N)$ para operações nessas estruturas.

* **Impacto da Ordem na Árvore B:**
    * A **Árvore B (Ordem 1):**, que se assemelha a uma árvore binária de busca simples, mostra o maior número de operações entre as Árvores B. Seu desempenho é mais próximo das Árvores AVL e Rubro-Negras. Isso ocorre porque cada nó pode conter apenas uma chave, maximizando a altura da árvore e o número de travessias.
    * À medida que a ordem da Árvore B aumenta para **5 e 10**, há uma diminuição acentuada no número de operações. A ordem 10, em particular, demonstra a melhor performance geral entre as árvores B testadas, validando a otimização de acesso a dados que essa estrutura oferece para ambientes com custos elevados de leitura/escrita de nós (como em armazenamento em disco).

* **AVL e Rubro-Negra:**
    * As Árvores AVL e Rubro-Negras, embora garantam a complexidade $O(\log N)$, tendem a realizar um número maior de operações de balanceamento (rotações) e de manipulação de nós em comparação com as Árvores B de ordem superior para os mesmos tamanhos de entrada. Isso se deve à necessidade de manter um balanceamento mais estrito em cada nó, que pode desencadear uma série de rotações. As linhas de "Inserções", "Remoções" e "Rotações" para AVL e Rubro-Negra estão consistentemente mais elevadas que as das Árvores B de ordens maiores.

* **Inserção vs. Remoção:**
    * Para todas as estruturas, a operação de remoção geralmente apresenta um custo ligeiramente superior à inserção. Isso pode ser atribuído à maior complexidade envolvida na remoção, que frequentemente exige a busca por um predecessor ou sucessor e um rebalanceamento mais complexo para manter as propriedades da árvore.

---

#### Conclusão
O projeto foi desenvolvido para comparar a eficiência das operações em diferentes estruturas de árvores balanceadas.

As implementações consideram o número real de operações realizadas, refletindo o custo dos balanceamentos.

Os resultados validam as complexidades teóricas e destacam a vantagem das Árvores B com ordens maiores para cenários com grandes volumes de dados. 

A escolha da estrutura de árvore ideal, depende do contexto de aplicação, mas a Árvore B, especialmente de ordem 10, se afirma como uma solução mais indicada para armazenamento e recuperação eficiente em larga escala.

---

### Execução do projeto
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
O script gerar_grafico.py lê os dados dos arquivos .txt e produz o arquivo grafico.png, que é o gráfico apresentado neste README.md.

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

