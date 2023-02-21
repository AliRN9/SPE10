import scipy.sparse as sp
import numpy as np
import scipy.io as io
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import sys

name = sys.argv[1]

def main(name):
    A_PATH = '../data/A.mtx'
    B_PATH = '../data/b.txt'
    SHAPE_X = 60 
    SHAPE_Y = 220

    A = pd.read_csv(A_PATH, sep=' ', names=['1', '2', '3'])
    b = pd.read_csv(B_PATH).to_numpy()

    A = A.to_numpy()
    row = A[:,0]
    col = A[:,1]
    value = A[:,2]
    matrix = sp.coo_matrix((value, (row, col)), shape=(SHAPE_X*SHAPE_Y, SHAPE_X*SHAPE_Y)).toarray()
    solution = sp.linalg.spsolve(matrix, b);
    np.savetxt('solution.txt', solution[:, None])


    sol = solution.reshape((220,60))
    plt.figure(figsize=(30,10))

    plt.title("Solution of the equation div(k * ∇p) = 0\n", fontsize=40)
    ax = sns.heatmap(data=sol.T,square=True)
    ax.set_aspect("equal")
    ax.set_ylabel('X axis', fontsize=24)
    ax.set_xlabel('Y axis', fontsize=24)
    ax.set_xticks(list(range(0, 221, 10)))
    ax.set_xticklabels(list(range(220, -1, -10)))
    ax.set_yticks(list(range(0, 61, 10)))
    ax.set_yticklabels(list(range(0, 61, 10)))

    plt.savefig(f"../data/{name}.png")

if __name__ == "__main__":
    main(name)
