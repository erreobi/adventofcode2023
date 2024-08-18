import sys

print("FileName: ", sys.argv[1])


def leggi_file(nome_file):
    with open(nome_file, "r") as file:
        contenuto = file.read()
    return contenuto


CENTER = "S"


def find_center(gardern_grid):
    for row_index, row in enumerate(gardern_grid):
        for col_index, garden_element in enumerate(row):
            if garden_element == "S":
                return (row_index, col_index)


def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    gardern_map = leggi_file(nome_file)

    print(gardern_map)

    gardern_grid = []

    [gardern_grid.append(list(row)) for row in gardern_map.split("\n") if row]

    print(gardern_grid)

    paths_positions = []
    paths_positions.append(find_center(gardern_grid))

    UP = (-1, 0)
    DOWN = (1, 0)
    LEFT = (0, -1)
    RIGHT = (0, 1)

    for position in paths_positions:
        if position[0] < 0 or position[0] >= len(gardern_grid):
            continue

        if position[1] < 0 or position[1] >= len(gardern_grid[0]):
            continue


if __name__ == "__main__":
    main()
