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


UP = (-1, 0)
DOWN = (1, 0)
LEFT = (0, -1)
RIGHT = (0, 1)
PLAN_ZERO = (0, 0)


def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    gardern_map = leggi_file(nome_file)

    print(gardern_map)

    gardern_grid = []

    [gardern_grid.append(list(row)) for row in gardern_map.split("\n") if row]

    print(gardern_grid)

    # key=number of steps value=position
    center = find_center(gardern_grid)

    # paths_positions_map contain all the position it can reach at each step. At step 0 it start from the S.
    paths_positions_map = {}
    # Each element has the starting coordina, the plan when it is moving and how many time it passed in the same position.
    path_spatial_coordinate = (center,) + (PLAN_ZERO,) + (1,)
    paths_positions_map[0] = set([path_spatial_coordinate])

    # number_max_step contain the max number of steps.
    number_max_step = 50

    # movements contain all the possible move for each steps.
    movements = [UP, DOWN, LEFT, RIGHT]

    number_of_current_step = 0

    while number_of_current_step < number_max_step:
        print(
            f"Step number {number_of_current_step} of {number_max_step}. Number of Element { len(paths_positions_map[number_of_current_step]) } "
        )

        paths_positions = paths_positions_map[number_of_current_step]
        if paths_positions is None:
            print(
                f"Error. The step {number_of_current_step} is not present in the map -> {paths_positions_map}"
            )
            exit(-1)

        number_of_current_step += 1
        next_path_position = set()
        check_coordinate = set()

        for position in paths_positions:
            row, col = position[0]
            plan_row, plan_col = position[1]
            multiplier = position[2]
            # print(
            #     f"considering {row} row and {col} coloumn for the plan {plan_row},{plan_col} with multiplier {multiplier}"
            # )
            for move in movements:
                new_row = row + move[0]
                new_col = col + move[1]
                new_plan_row = plan_row
                new_plan_col = plan_col
                new_multiplier = multiplier

                if new_row < 0:
                    # print("Toward UP Plan")
                    new_plan_row = plan_row + UP[0]
                    new_plan_col = plan_col + UP[1]
                    new_row = len(gardern_grid) - 1
                elif new_row >= len(gardern_grid):
                    # print("Toward DOWN Plan")
                    new_plan_row = plan_row + DOWN[0]
                    new_plan_col = plan_col + DOWN[1]
                    new_row = 0
                if new_col < 0:
                    # print("Toward LEFT Plan")
                    new_plan_row = plan_row + LEFT[0]
                    new_plan_col = plan_col + LEFT[1]
                    new_col = len(gardern_grid[0]) - 1
                elif new_col >= len(gardern_grid[0]):
                    # print("Toward RIGHT Plan")
                    new_plan_row = plan_row + RIGHT[0]
                    new_plan_col = plan_col + RIGHT[1]
                    new_col = 0

                # print(
                # f"NEW position {new_row} row and {new_col} coloumn for the plan {new_plan_row},{new_plan_col}"
                # )

                if gardern_grid[new_row][new_col] == "#":
                    continue

                if (new_row, new_col) in check_coordinate:
                    # print(f"Passing Over {len(check_coordinate)}")
                    new_multiplier += 1
                    dummy = 1
                else:
                    check_coordinate.add((new_row, new_col))

                next_spatial_position = (
                    (new_row, new_col),
                    (new_plan_row, new_plan_col),
                    new_multiplier,
                )

                print(f"{next_spatial_position}")

                next_path_position.add(next_spatial_position)

        paths_positions_map[number_of_current_step] = next_path_position

    # stampa(paths_positions_map[number_of_current_step], gardern_grid)

    print(
        f"garden plots you can reach are {len(paths_positions_map[number_of_current_step])}"
    )


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
    # print(paths_positions_map[number_of_current_step])
    for element in paths_positions:
        gardern_grid_copy[element[0]][element[1]] = "0"

    for row_index, row_list in enumerate(gardern_grid_copy):
        for col_index, element in enumerate(row_list):
            print(element, end="")
        print()


if __name__ == "__main__":
    main()
