from __future__ import annotations
from pathlib import Path
from matplotlib import pyplot as plt
from matplotlib.colors import LinearSegmentedColormap
from matplotlib.patches import Rectangle
import numpy as np

# For better latex font
plt.rcParams['text.usetex'] = True

CMAP = LinearSegmentedColormap.from_list(
    'custom',
    [
        (0.0, 'white'),
        (0.5, '#e6d0d1'),
        (1.0, '#9e5457')
    ]
)

def plot(ax: plt.Axes, grid: np.ndarray) -> None:
    nx, ny = grid.shape

    light = 0.5 * grid
    tiled = np.block([
        [light, light, light],
        [light, grid, light],
        [light, light, light],
    ])

    rect = Rectangle(xy=(nx - 0.5, ny - 0.5), width=nx, height=ny, linewidth=1, edgecolor='black', facecolor='none', linestyle=':')

    ax.imshow(X=tiled, cmap=CMAP, vmin=0, vmax=1)
    ax.add_patch(rect)
    ax.set_xlim([nx // 2 - 0.5, tiled.shape[0] - nx // 2 - 0.5])
    ax.set_ylim([ny // 2 - 0.5, tiled.shape[1] - ny // 2 - 0.5])
    ax.set_axis_off()

def main() -> None:
    _, axes = plt.subplots(nrows=2, ncols=4, constrained_layout=True, figsize=(6.4, 3.2))

    directory = Path(__file__).parent

    for i, folder in enumerate(['4', '8', '16', '32']):
        for j in range(2):
            grid = np.loadtxt(fname=directory / folder / f'{j + 1}.csv', delimiter=',')
            plot(ax=axes[j, i], grid=grid)

    path = Path(__file__).parent.resolve() / 'teaser.svg'
    plt.savefig(path, format='svg', dpi=300)
    plt.show()

if __name__ == '__main__':
    main()
