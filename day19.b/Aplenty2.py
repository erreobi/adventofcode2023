import sys
import re
from copy import deepcopy


print("FileName: ", sys.argv[1])


def leggi_file(nome_file):
    with open(nome_file, "r") as file:
        contenuto = file.read()
    return contenuto


def stampa_matrice(matrice):
    for riga in matrice:
        print("".join(riga))


# give x(MIN,MAX) and y, they split the range following those rules
# x > y -> x = (y+1, MAX) x^ = (MIN, y)
# x < y -> x = (MIN, y-1) x^ = (y, MAX)
# CHECK -> if y is in (MIN, MAX)
# Example
#  x=(1,4000)
#  x > 1000 -> x = (1001,4000) x^ = (1,1000)
#  x < 1000 -> x = (1, 999) x^ (1000, 4000)
#
def greater(x, y):
    min = x[0]
    max = x[1]

    res = (y + 1, max)
    res_opposite = (min, y)

    return (res, res_opposite)


def lower(x, y):
    min = x[0]
    max = x[1]

    res = (min, y - 1)
    res_opposite = (y, max)

    return (res, res_opposite)


workflows = {}
part_ratings = []


def recursiveFindings(part_status: dict) -> int:
    rule_to_apply = part_status["rule"]

    if rule_to_apply == "R":
        return 0

    if rule_to_apply == "A":
        combination = (part_status["x"][1] - part_status["x"][0]) + 1
        combination = combination * ((part_status["m"][1] - part_status["m"][0]) + 1)
        combination = combination * ((part_status["a"][1] - part_status["a"][0]) + 1)
        combination = combination * ((part_status["s"][1] - part_status["s"][0]) + 1)

        return combination

    combination = 0
    rules = workflows[rule_to_apply]
    true_part_status = deepcopy(part_status)

    for rule in rules:
        category = rule["category"]

        # Fallback
        if category == "":
            true_part_status["rule"] = rule["next_rule"]
            true_part_status["path"] += "->" + rule["next_rule"]
            combination += recursiveFindings(deepcopy(true_part_status))
        else:
            category_range = true_part_status[category]
            applicabile_rule_range = []
            if rule["operator"] == ">":
                applicabile_rule_range = greater(category_range, rule["rating"])
            else:
                applicabile_rule_range = lower(category_range, rule["rating"])

            new_rue_part_status = deepcopy(true_part_status)
            new_rue_part_status["rule"] = rule["next_rule"]
            true_part_status["path"] += "->" + rule["next_rule"]
            new_rue_part_status[category] = applicabile_rule_range[0]
            combination += recursiveFindings(deepcopy(new_rue_part_status))

            ##the nest rule have to consider the previous rule.
            true_part_status[category] = applicabile_rule_range[1]

    return combination


def main():
    global workflows
    global part_ratings
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)

    righe = testo.strip().split(
        "\n\n"
    )  # Dividi le matrici usando le linee vuote come separatore

    workflows_list = [workflow for workflow in righe[0].split("\n")]
    print(workflows_list)

    # it will parse something like: bk{a>1796:gql,m<1358:zmd,m>1825:A,A}
    pattern = re.compile(
        "((?P<category>\\w+)(?P<operator>(<|>))(?P<rating>\\d+))?:(?P<next_rule>\\w+)",
        re.VERBOSE,
    )

    for workflow in workflows_list:
        workflow = workflow.replace("}", "")
        statements = workflow.split("{")
        rule_name = statements[0]
        rule_list = []

        rules_string_array = [rule for rule in statements[1].split(",")]
        for index, rule in enumerate(rules_string_array):
            rule_dict = {}
            if index == (len(rules_string_array) - 1):
                rule_dict["category"] = ""
                rule_dict["operator"] = ""
                rule_dict["next_rule"] = rule
            else:
                match_pattern = pattern.match(rule)
                rule_dict["category"] = match_pattern.group("category")
                rule_dict["next_rule"] = match_pattern.group("next_rule")

                if match_pattern.group("operator") == ">":
                    rule_dict["operator"] = ">"
                    rule_dict["rating"] = int(match_pattern.group("rating"))

                else:
                    rule_dict["operator"] = "<"
                    rule_dict["rating"] = int(match_pattern.group("rating"))

            rule_list.append(rule_dict)

        workflows[rule_name] = rule_list

    print(f"Rule {workflows}")

    initial_setup = {}
    initial_setup["x"] = (1, 4000)
    initial_setup["m"] = (1, 4000)
    initial_setup["a"] = (1, 4000)
    initial_setup["s"] = (1, 4000)
    initial_setup["rule"] = "in"
    initial_setup["path"] = "in"

    combination = recursiveFindings(initial_setup)

    print(f"Combination: {combination}")


if __name__ == "__main__":
    main()
