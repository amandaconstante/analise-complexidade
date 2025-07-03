import os
import pandas as pd
import matplotlib.pyplot as plt

arquivos = {
    "resultados_avl.txt": "AVL",
    "resultados_rubro_negra.txt": "Rubro Negra",
    "resultados_arvore_b.txt": "Árvore B"
}

metricas = ["Insercoes", "Remocoes", "Rotacoes"]

plt.figure(figsize=(12, 7))

arquivos_lidos = 0

for arquivo, label in arquivos.items():
    if not os.path.isfile(arquivo):
        print(f"[AVISO] Arquivo '{arquivo}' não encontrado. Ignorando.")
        continue

    df = pd.read_csv(arquivo)

    for metrica in metricas:
        if metrica not in df.columns:
            print(f"[AVISO] Coluna '{metrica}' ausente em '{arquivo}'. Preenchendo com 0.")
            df[metrica] = 0

    arquivos_lidos += 1

    if label == "Árvore B":
        # Filtra cada ordem separadamente
        ordens = df["Ordem"].unique()
        for ordem in ordens:
            df_ordem = df[df["Ordem"] == ordem]
            for metrica in metricas:
                plt.plot(df_ordem["Tamanho"], df_ordem[metrica], marker='o',
                         label=f"{label} (ordem {ordem}) - {metrica}")
    else:
        for metrica in metricas:
            plt.plot(df["Tamanho"], df[metrica], marker='o', label=f"{label} - {metrica}")

if arquivos_lidos == 0:
    print("Nenhum arquivo válido foi carregado. Verifique os arquivos e seus formatos.")
else:
    plt.title("Comparação de Operações nas Árvores")
    plt.xlabel("Tamanho da Entrada")
    plt.ylabel("Número de Operações (escala logarítmica)")
    plt.yscale("log")  
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    try:
        plt.savefig("grafico.png")
        print("[SUCESSO] Gráfico salvo como 'grafico.png'")
    except:
        print("[ERRO] Não foi possível salvar o gráfico.")