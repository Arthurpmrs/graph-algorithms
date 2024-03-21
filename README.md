# Projeto de Teoria dos Grafos

Implementação dos algoritmos de Prim, Kruskal, Dijkstra, Kosaraju e Bellman-Ford em C++, como requisito avaliativo da matéria de Teoria dos Grafos.

Professor: [Dr. Rian Gabriel Santos Pinheiro](https://ic.ufal.br/professor/rian/)

Equipe:

-   Arthur Pontes de Miranda Ramos Soares
-   Beatriz Rodrigues Cavalcante

## Observações

Para compilar cada um dos algoritmos, navegue até sua pasta e execute `make nome_do_algoritmo`.

```bash
cd kruskal
make kruskal

cd prim
make prim

cd dijkstra
make dijkstra

cd kosaraju
make kosaraju

cd bellman
make bellman
```

Para executar os testes originais do Professor, copie os binários (`*.bin`) de cada pasta e cole na pasta `Bat1`. Em seguida, execute o script de teste.

```bash
bash Bat1.sh
```

## 5º Algoritmo - Bellman-Ford

O 5º algoritmo escolhido foi o algoritmo de Bellman-Ford, que soluciona o problema do caminho mínimo quando o grafo aceita arestas negativas. Os 20 casos de teste pedidos estão presentes na pasta `bellman/instances`. Já os resultados esperados para cada um dos casos estão presentes na pasta `bellman/results`. As entradas foram geradas de forma aleatória e os resultados foram obtidas executando as entradas em um código externo.

> [!important]
> Para obter os resultados de cada um dos casos teste, consideramos que o vértice inicial seria sempre o 1. Portanto, no script de teste sempre executamos o algoritmo com `-i 1`.

Para executar os casos teste de forma automática, navegue até a pasta `bellman/` e execute o arquivo `teste.sh`.

```bash
bash teste.sh
```
