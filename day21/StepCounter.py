import enum
import sys
import operator

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


UP = (-1, 0)
DOWN = (1, 0)
LEFT = (0, -1)
RIGHT = (0, 1)


def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    gardern_map = leggi_file(nome_file)

    print(gardern_map)

    gardern_grid = []

    [gardern_grid.append(list(row)) for row in gardern_map.split("\n") if row]

    print(gardern_grid)

    # key=number of steps value=position
    center = find_center(gardern_grid)
    paths_positions_map = {}
    paths_positions_map[0] = set([center])
    number_max_step = 64
    movements = [UP, DOWN, LEFT, RIGHT]
    number_of_step = 0

    while number_of_step < number_max_step:
        print(
            f"Step number {number_of_step} of {number_max_step}. Number of Element { len(paths_positions_map[number_of_step]) } "
        )
        paths_positions = paths_positions_map[number_of_step]
        if paths_positions is None:
            print(
                f"Error. The step {number_of_step} is not present in the map -> {paths_positions_map}"
            )
            exit(-1)

        number_of_step += 1
        next_path_position = set()

        for position in paths_positions:
            for move in movements:
                next_position = tuple(map(operator.add, position, move))

                if next_position[0] < 0 or next_position[0] >= len(gardern_grid):
                    continue

                if next_position[1] < 0 or next_position[1] >= len(gardern_grid[0]):
                    continue

                if gardern_grid[next_position[0]][next_position[1]] == "#":
                    continue

                next_path_position.add(next_position)

        paths_positions_map[number_of_step] = next_path_position

    stampa(paths_positions_map[number_of_step], gardern_grid)

    print(f"garden plots you can reach are {len(paths_positions_map[number_of_step])}")


def matrix_deep_copy(gardern_grid):
    gardern_grid_copy = [
        [0 for _ in range(len(gardern_grid))] for _ in range(len(gardern_grid[0]))
    ]
    for row_index, row_list in enumerate(gardern_grid):
        for col_index, element in enumerate(row_list):
            gardern_grid_copy[row_index][col_index] = element
    return gardern_grid_copy


def stampa(paths_positions, gardern_grid):
    gardern_grid_copy = matrix_deep_copy(gardern_grid)
    # print(paths_positions_map[number_of_step])
    for element in paths_positions:
        gardern_grid_copy[element[0]][element[1]] = "0"

    for row_index, row_list in enumerate(gardern_grid_copy):
        for col_index, element in enumerate(row_list):
            print(element, end="")
        print()


if __name__ == "__main__":
    main()
