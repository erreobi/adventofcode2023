import sys

ON = True
OFF = False
LOW = "low"
HIGH = "high"

print("FileName: ", sys.argv[1])


def leggi_file(nome_file):
    with open(nome_file, "r") as file:
        contenuto = file.read()
    return contenuto


class Module:
    def __init__(self, name="", destination_modules=None) -> None:
        self.name = name
        self.status = OFF
        self.destination_modules = []
        if destination_modules is not None:
            self.destination_modules.extend(destination_modules)
        self.input_modules = {}
        self.type = ""

    def add_input_module(self, module):
        if module is not None:
            # print(self.input_modules)
            # print(module)
            self.input_modules[module] = LOW

    def send(self, pulse, origin):
        return []

    def __str__(self) -> str:
        return (
            f"{self.input_modules}->{self.type}{self.name}->{self.destination_modules}"
        )


class Broadcaster(Module):
    def __init__(self, name="", destination_modules=None) -> None:
        super().__init__(name, destination_modules)
        self.type = ""

    def send(self, pulse, origin):
        commands = []

        for dest_mod in self.destination_modules:
            commands.append([self.name, pulse, dest_mod])

        return commands


class FlipFlop(Module):
    def __init__(self, name="", destination_modules=None) -> None:
        super().__init__(name, destination_modules)
        self.type = "%"

    def send(self, pulse, origin):
        if pulse == HIGH:
            return []

        self.status = not self.status
        pulse_to_send = LOW
        if self.status is ON:
            pulse_to_send = HIGH

        commands = []

        for dest_mod in self.destination_modules:
            commands.append([self.name, pulse_to_send, dest_mod])

        return commands


class Conjunction(Module):
    def __init__(self, name="", destination_modules=None) -> None:
        super().__init__(name, destination_modules)
        self.type = "&"

    def send(self, pulse, origin):
        self.input_modules[origin] = pulse

        pulse_to_send_boolean = True
        for input_mod in self.input_modules:
            pulse_to_send_boolean = (
                pulse_to_send_boolean and self.input_modules[input_mod] is HIGH
            )

        pulse_to_send = HIGH
        if pulse_to_send_boolean is True:
            pulse_to_send = LOW

        commands = []

        for dest_mod in self.destination_modules:
            commands.append([self.name, pulse_to_send, dest_mod])

        return commands


def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    module_configuration = leggi_file(nome_file)

    configuration_map = {}

    pulse_list = module_configuration.split("\n")
    print(pulse_list)
    for pulse_command in pulse_list:
        if pulse_command != "":
            pulse_cmd = pulse_command.split(" -> ")
            sender = pulse_cmd[0]
            receivers = pulse_cmd[1].split(", ")
            print(f"Sender: {sender}")
            print(f"Receiver: {receivers}")

            if sender.startswith("broadcaster"):
                broadcaster = Broadcaster(name=sender, destination_modules=receivers)
                configuration_map[sender] = broadcaster
            elif sender.startswith("%"):
                configuration_map[sender.strip("%")] = FlipFlop(
                    name=sender.strip("%"), destination_modules=receivers
                )
            elif sender.startswith("&"):
                configuration_map[sender.strip("&")] = Conjunction(
                    name=sender.strip("&"), destination_modules=receivers
                )

    for module in list(configuration_map.keys()):
        for dest_module in configuration_map[module].destination_modules:
            if dest_module not in configuration_map:
                configuration_map[dest_module] = Module(
                    name=dest_module, destination_modules=[]
                )
            configuration_map[dest_module].add_input_module(
                configuration_map[module].name
            )

    print("---")
    [print(configuration_map[module]) for module in configuration_map]
    print("----")
    first_conf = [list(str(configuration_map[module])) for module in configuration_map]

    minimal_low_RX = 1000
    counter_high_pulses = 0
    counter_low_pulses = 0
    press_button = 0
    # for press_button in range(1000000):
    while True:
        # it is the first command
        command_list = [["button", LOW, "broadcaster"]]
        # print()
        for command in command_list:
            # print(f"Command: {command[0]}->{command[1]}->{command[2]}")
            module = configuration_map[command[2]]
            next_commands = module.send(command[1], command[0])

            if command[2] == "rx" and command[1] is LOW:
                # ciccio = press_button - minimal_low_RX
                # if ciccio < minimal_low_RX:
                # minimal_low_RX = ciccio

                print(f"RX->{command}->{press_button}")
                break

            # if command[1] is HIGH:
            # counter_high_pulses += 1
            # else:
            # counter_low_pulses += 1

            # print(f"    Next Command {next_commands}")
            command_list.extend(next_commands)

        # final_conf = [
        # list(str(configuration_map[module])) for module in configuration_map
        # ]

        # if final_conf == first_conf:
        # print("EQUAAAAAAAL")
        press_button += 1

    print(f"Pressed {press_button}")
    print(f"Number High Pulses: {counter_high_pulses}")
    print(f"Number Low Pulses: {counter_low_pulses}")
    print(
        f"Total Signal : {minimal_low_RX}  -> {counter_low_pulses * counter_high_pulses}"
    )


if __name__ == "__main__":
    main()
