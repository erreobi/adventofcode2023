from pprint import isreadable
import sys
import copy

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
    paths_positions_map = []
    # Each element has the starting coordinate, the plan when it is moving and how many time it passed in the same position.
    nextposition = {}
    nextposition[center] = set((PLAN_ZERO,))
    paths_positions_map.append(nextposition)
    print(f"Starting from: {paths_positions_map}")

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
        next_path_position = {}

        # paths_position is a map of spatial coordinate. The keys are the coordinate and valure is the number of times
        # you can passed over that coordinate
        for position in paths_positions:
            row, col = position
            print(f"Type of {position} is {type(position)}")

            # print(
            #     f"considering {row} row and {col} coloumn for the plan {paths_positions[position]}"
            # )
            for move in movements:
                new_row = row + move[0]
                new_col = col + move[1]

                list_plan_in_that_position = paths_positions[position]
                # print(
                #     f"{row},{col} -> {len(paths_positions[position])} - {new_row,new_col} "
                # )

                if (
                    new_row < 0
                    or new_row >= len(gardern_grid)
                    or new_col < 0
                    or new_col >= len(gardern_grid[0])
                ):
                    print("\tNEW PLAN")
                    plan_movement = UP
                    if new_row < 0:
                        # print("Toward UP Plan")
                        plan_movement = UP
                        new_row = len(gardern_grid) - 1
                    elif new_row >= len(gardern_grid):
                        # print("Toward DOWN Plan")
                        plan_movement = DOWN
                        new_row = 0
                    if new_col < 0:
                        # print("Toward LEFT Plan")
                        plan_movement = LEFT
                        new_col = len(gardern_grid[0]) - 1
                    elif new_col >= len(gardern_grid[0]):
                        # print("Toward RIGHT Plan")
                        plan_movement = RIGHT
                        new_col = 0

                    new_list_plan_in_that_position = None

                    print(
                        f"Looking for {(new_row,new_col)} that is type {type((new_row,new_col))}"
                    )

                    if (new_row, new_col) in paths_positions:
                        new_list_plan_in_that_position = copy.deepcopy(
                            paths_positions[(new_row, new_col)]
                        )
                    else:
                        print(paths_positions)
                        print(new_row, new_col)

                    # print(f"\t{new_list_plan_in_that_position}")
                    if new_list_plan_in_that_position is None:
                        new_list_plan_in_that_position = set()

                    if gardern_grid[new_row][new_col] == "#":
                        continue

                    for plan in list_plan_in_that_position:
                        print(f"\t\t Adding new plan from {plan}")
                        new_plan_row, new_plan_col = plan

                        new_plan_row += plan_movement[0]
                        new_plan_col += plan_movement[1]

                        new_list_plan_in_that_position.add((new_plan_row, new_plan_col))

                    print(f"Adding Plan for {len(new_list_plan_in_that_position)}")
                    next_spatial_position = (new_row, new_col)

                    next_path_position[next_spatial_position] = (
                        new_list_plan_in_that_position
                    )

                else:
                    # print("SAME PLAN")

                    if gardern_grid[new_row][new_col] == "#":
                        continue

                    next_spatial_position = (new_row, new_col)

                    next_path_position[next_spatial_position] = (
                        list_plan_in_that_position
                    )

        paths_positions_map.append(next_path_position)

    # stampa(paths_positions_map[number_of_current_step], gardern_grid)

    last_step_position = paths_positions_map[number_of_current_step]
    tot = 0
    for element in last_step_position:
        print(f"TOT: {tot} -> {element} {len(last_step_position[element])}")
        tot += len(last_step_position[element])

    print(f"garden plots you can reach are {tot}")


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
