import sys
import re

ON="on"
OFF="off"
LOW="low"
HIGH="high"

print("FileName: ", sys.argv[1])

def leggi_file(nome_file):
    with open(nome_file, "r") as file:
        contenuto = file.read()
    return contenuto

class Module:

    def __init__(self, name="", destination_modules=None) -> None:
            self.name=name
            self.status=OFF
            self.destination_modules=[]
            self.destination_modules.append(destination_modules)
            self.input_modules=[]
            self.type=""

    def add_input_module(self, module):
        self.input_modules.append(module);

    def send(self, pulse):
        return []

    def __str__(self) -> str:
        return f"{self.input_modules}->{self.type}{self.name}->{self.destination_modules}"

class Broadcaster(Module):
    def __init__(self, name="", destination_modules=None) -> None:
        super().__init__(name, destination_modules)
        self.type=""

    def send(self, pulse):
        commands = []

        for dest_mod in self.destination_modules:
            commands.append({LOW,dest_mod})

        return commands




class FlipFlop(Module):
    def __init__(self, name="", destination_modules=None) -> None:
        super().__init__(name, destination_modules)
        self.type="%"

class Conjunction(Module):
    def __init__(self, name="", destination_modules=None) -> None:
        super().__init__(name, destination_modules)
        self.type="&"

def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    module_configuration = leggi_file(nome_file)

    configuration_map = {}

    pulse_list = module_configuration.split("\n")
    print(pulse_list)
    for pulse_command in pulse_list:
        if (pulse_command is not ""):
            pulse_cmd = pulse_command.split(" -> ");
            sender=pulse_cmd[0]
            receivers=pulse_cmd[1].split(", ")
            print(f"Sender: {sender}")
            print(f"Receiver: {receivers}")

            if sender.startswith("broadcaster"):
                broadcaster = Broadcaster(name=sender, destination_modules=receivers)
                configuration_map[sender]=broadcaster
            elif sender.startswith("%"):
                configuration_map[sender.strip("%")]=FlipFlop(name=sender.strip("%"), destination_modules=receivers)
            elif sender.startswith("&"):
                configuration_map[sender.strip("&")]=Conjunction(name=sender.strip("&"), destination_modules=receivers)

    for module in list(configuration_map.keys()):
        for dest_module in configuration_map[module].destination_modules:
            if dest_module not in configuration_map:
                configuration_map[dest_module] = Module(name=dest_module, destination_modules=[])
            configuration_map[dest_module].add_input_module({configuration_map[module].name, LOW})

    [print(configuration_map[module]) for module in configuration_map]

    #it is the first command
    command_list = [[LOW,"broadcaster"]]

    for command in command_list:
        module = configuration_map[command[1]]
        module.send(command[0])



if __name__ == "__main__":
    main()
