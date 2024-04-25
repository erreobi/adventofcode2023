from functools import partial
import sys
import re


print("FileName: ", sys.argv[1])


def leggi_file(nome_file):
    with open(nome_file, "r") as file:
        contenuto = file.read()
    return contenuto


def stampa_matrice(matrice):
    for riga in matrice:
        print("".join(riga))


def greater(x, y):
    return x > y


def lower(x, y):
    return x < y


def always_true(x):
    return True


# perator = [partial(gr, y=200), partial(low, y=200)]
# print(operator[0](1000))


workflows = {}
part_ratings = []


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
        "(?P<category>\\w+)(?P<operator>(<|>))(?P<rating>\\d+):(?P<next_rule>\\w+)",
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
                rule_dict["operator"] = partial(always_true)
                rule_dict["next_rule"] = rule
            else:
                match_pattern = pattern.match(rule)
                rule_dict["category"] = match_pattern.group("category")

                if match_pattern.group("operator") == ">":
                    rule_dict["operator"] = partial(
                        greater, y=int(match_pattern.group("rating"))
                    )
                else:
                    rule_dict["operator"] = partial(
                        lower, y=int(match_pattern.group("rating"))
                    )
                rule_dict["next_rule"] = match_pattern.group("next_rule")

            rule_list.append(rule_dict)

        workflows[rule_name] = rule_list

    print(f"Rule {workflows}")

    print()
    print()

    ratings = [rating for rating in righe[1].split("\n")]
    print(ratings)
    print()
    for rating in ratings:
        matches = re.finditer("((?P<part>\\w)\\=(?P<rate>\\d+)(,){0,1})", rating)
        parts_element = {}

        for match in matches:
            rate = match.group("rate")
            part = match.group("part")
            print(f"{part} = {rate}")
            parts_element[part] = int(rate)

        part_ratings.append(parts_element)

    print(f"Parts: {part_ratings}\n")
    print()

    all_part_sum = 0
    for part_rating in part_ratings:
        print(f"\tPart Input: {part_rating}", end=" ")
        rule_to_apply = "in"
        while rule_to_apply != "A" and rule_to_apply != "R":
            # print(f"\t\tApplying the rule: {rule_to_apply}")
            print(f"-> {rule_to_apply}", end=" ")

            rule_list = workflows[rule_to_apply]
            # print(f"\t\tThe rule is: {rule_list}")
            for rule in rule_list:
                # print(f"The Rule Element: {rule}")
                rule_category = rule["category"]
                # print(f"\t\t\tCondition category: {rule_category}")
                if rule_category != "":
                    rule_category_rate = part_rating[rule_category]
                else:
                    rule_category_rate = 0
                # print(f"\t\t\tCondition rating: {rule_category_rate}")
                # print(f"\t\t\tApply to {rule_category} = {rule_category_rate}")
                if rule["operator"](rule_category_rate):
                    rule_to_apply = rule["next_rule"]
                    # print("\t\t\t\tOperation passed.")
                    break
                # else:
                # print("\t\t\t\tOperation NOT passed")

            if rule_to_apply == "A":
                sum = (
                    part_rating["x"]
                    + part_rating["m"]
                    + part_rating["a"]
                    + part_rating["s"]
                )
                all_part_sum = all_part_sum + sum
                print(f"-> A {sum}")

            if rule_to_apply == "R":
                print("-> R")

    print(f"RESULT: {all_part_sum}")


if __name__ == "__main__":
    main()
