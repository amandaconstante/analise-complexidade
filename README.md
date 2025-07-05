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
![image](https://github.com/user-attachments/assets/bb518761-9d64-4fb8-a638-5a584f654d17)



#### Remoções:
![image](https://github.com/user-attachments/assets/179de2cd-74ca-4835-a847-081dcdaa5362)




## Discussão dos Resultados
A análise dos gráficos de "Esforço de Inserção" e "Esforço de Remoção" revela padrões distintos e esperados de desempenho entre as estruturas de árvores balanceadas:

* **Comportamento Logarítmico:** Todas as estruturas de árvores balanceadas demonstram um crescimento logarítmico no número de operações à medida que o tamanho da entrada aumenta. Isso é evidenciado pela forma quase linear das curvas no gráfico com escala logarítmica no eixo Y, confirmando a complexidade teórica de $O(\log N)$ para operações nessas estruturas.

* **Impacto da Ordem na Árvore B:**
    * A **Árvore B (Ordem 1)**: Observa-se que a Árvore B de ordem 1, que se assemelha a uma árvore binária de busca simples, apresenta o maior número de operações entre as variações da Árvore B. Seu desempenho é notavelmente mais próximo das Árvores AVL e Rubro-Negras em ambas as operações (inserção e remoção). Isso ocorre porque, com apenas uma chave por nó, a altura da árvore é maximizada, exigindo mais travessias.
    * **Árvore B (Ordem 5 e 10):** À medida que a ordem da Árvore B aumenta para 5 e, mais pronunciadamente, para 10, há uma diminuição acentuada no número de operações. A linha roxa (Ordem 10) consistentemente exibe o menor número de operações em ambos os gráficos, demonstrando a melhor performance geral entre as árvores B testadas. Esta otimização é devido à capacidade de armazenar múltiplos elementos por nó, o que resulta em árvores mais "achatadas" e com menor altura. Consequentemente, menos acessos a nós são necessários para encontrar ou manipular uma chave, mesmo que a operação interna de um nó seja ligeiramente mais complexa.

* **AVL e Rubro-Negra:**
    As Árvores AVL e Rubro-Negras, embora garantam a complexidade $O(\log N)$, tendem a realizar um número maior de operações de balanceamento (rotações) e de manipulação de nós em comparação com as Árvores B de ordem superior (5 e 10) para os mesmos tamanhos de entrada. Isso se deve à necessidade de manter um balanceamento mais estrito em cada nó, o que pode desencadear uma série de rotações. As linhas azuis (AVL) e vermelhas (Rubro-Negra) estão consistentemente mais elevadas que as das Árvores B de ordens maiores em ambos os gráficos. A Árvore AVL, em particular, mostra um número ligeiramente maior de operações em alguns pontos de inserção e remoção em comparação com a Rubro-Negra.

* **Inserção vs. Remoção:**
    Comparando os dois gráficos, é possível observar que, para todas as estruturas, a operação de remoção geralmente apresenta um custo ligeiramente superior ou comparável à inserção. Isso pode ser atribuído à maior complexidade envolvida na remoção, que frequentemente exige a busca por um predecessor ou sucessor para manter a integridade da árvore, além de um rebalanceamento mais complexo para restabelecer as propriedades da árvore balanceada.

---

#### Conclusão
O projeto foi desenvolvido para comparar a eficiência das operações em diferentes estruturas de árvores balanceadas.

As implementações consideram o número real de operações realizadas, refletindo o custo dos balanceamentos.

Os resultados validam as complexidades teóricas e destacam a vantagem das Árvores B com ordens maiores para cenários com grandes volumes de dados. 

A Árvore B, especialmente a de ordem 10, se afirma como uma solução mais indicada para sistemas que exigem alta performance em operações de armazenamento e recuperação eficiente em larga escala. A escolha da estrutura de árvore ideal, no entanto, depende do contexto de aplicação e dos requisitos de desempenho.

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
python3 graph.py
```
O script `graph.py` lê os dados dos arquivos .txt e os gráficos apresentados neste README.md.
