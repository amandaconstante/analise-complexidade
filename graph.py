import pandas as pd
import matplotlib.pyplot as plt

def plot_insercoes():
    plt.figure(figsize=(10, 6))
    plt.title("Esforço Inserção")
    plt.xlabel("Tamanho do Conjunto de Dados")
    plt.ylabel("Número de Operações de Balanceamento")
    plt.yscale("log")

    # AVL
    df_avl = pd.read_csv("resultados_avl.txt")
    plt.plot(df_avl["Tamanho"], df_avl["Rotacoes"], label="AVL", color="blue", marker='o')

    # Rubro-Negra
    df_rn = pd.read_csv("resultados_rubro_negra.txt")
    plt.plot(df_rn["Tamanho"], df_rn["Rotacoes"], label="Rubro-Negra", color="red", marker='o')

    # Árvore B
    df_b = pd.read_csv("resultados_arvore_b.txt")
    cores = {1: "green", 5: "orange", 10: "purple"}
    for ordem in [1, 5, 10]:
        df_b_ordem = df_b[df_b["Ordem"] == ordem]
        plt.plot(df_b_ordem["Tamanho"], df_b_ordem["Balanceamentos"],
                 label=f"Árvore B (ordem {ordem})", color=cores[ordem], marker='o')

    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("grafico_insercoes.png")
    plt.close()

def plot_remocoes():
    plt.figure(figsize=(10, 6))
    plt.title("Esforço de Remoção")
    plt.xlabel("Tamanho do Conjunto de Dados")
    plt.ylabel("Número de Operações de Balanceamento")
    plt.yscale("log")

    # AVL
    df_avl = pd.read_csv("resultados_avl.txt")
    plt.plot(df_avl["Tamanho"], df_avl["Remocoes"], label="AVL", color="blue", marker='o')

    # Rubro-Negra
    df_rn = pd.read_csv("resultados_rubro_negra.txt")
    if "Remocoes" in df_rn.columns and df_rn["Remocoes"].sum() > 0:
        plt.plot(df_rn["Tamanho"], df_rn["Remocoes"], label="Rubro-Negra", color="red", marker='o')

    # Árvore B
    df_b = pd.read_csv("resultados_arvore_b.txt")
    cores = {1: "green", 5: "orange", 10: "purple"}
    for ordem in [1, 5, 10]:
        df_b_ordem = df_b[df_b["Ordem"] == ordem]
        plt.plot(df_b_ordem["Tamanho"], df_b_ordem["Balanceamentos"],
                 label=f"Árvore B (ordem {ordem})", color=cores[ordem], marker='o')

    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("grafico_remocoes.png")
    plt.close()

plot_insercoes()
plot_remocoes()
